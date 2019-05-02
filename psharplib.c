#include "imageArr.c"



struct ImageArr *Image(int h, int w){


    struct ImageArr* img = (struct ImageArr *)malloc(sizeof(struct ImageArr));
    struct pixel **buf;
    buf = (struct pixel **)malloc(sizeof(struct pixel *)*(w * h)); 
    img->imgPixelData = buf;
    
    for(int i =0; i< h*w; i++){
        
        struct pixel *p = setPix(255,255,255,50);
        img->imgPixelData[i] = p;
          
    }
    
    return img;
}



struct ImageArr* Contrast(struct ImageArr* img, int level){
    int factor = (259 * (level + 255)) / (255 * (259 - level));

    for(int i =0; i< img->w*img->h; i++){
        double r = factor * img->imgPixelData[i]->red;
        double g = factor * img->imgPixelData[i]->green;
        double b = factor * img->imgPixelData[i]->blue;
        if (r>255) r = 255;
        if (g>255) g = 255;
        if (b>255) b = 255;
        img->imgPixelData[i]->red = (int)r;
        img->imgPixelData[i]->green = (int)g;
        img->imgPixelData[i]->blue = (int)b;

    }

    return img;

}
struct ImageArr* Saturate(struct ImageArr* img, int l){
//https://alienryderflex.com/saturation.html
    double level = (double)l/100;
    float Pr = .229;
    float Pg = .587;
    float Pb = .114;
    double p;

    for(int i =0; i< img->w*img->h; i++){
        int r = img->imgPixelData[i]->red;
        int g = img->imgPixelData[i]->green;
        int b = img->imgPixelData[i]->blue;

        p = sqrt((r*r*Pr)+(g*g*Pg)+(b*b*Pb));
        r = p+(r-p)*level;
        if (r>255) r = 255;
        g = p+(g-p)*level;
        if (g>255) g = 255;
        b = p+(b-p)*level;
        if (b>255) b = 255;
        img->imgPixelData[i]->red = r;
        img->imgPixelData[i]->green = g;
        img->imgPixelData[i]->blue = b;
    }
    return img;

}

struct pixel* SaturatePixel(struct pixel* px, int l){
    double level = (double)l/100;
    float Pr = .229;
    float Pg = .587;
    float Pb = .114;
    double p;
    int r = px->red;
    int g = px->green;
    int b = px->blue;
    p = sqrt((r*r*Pr)+(g*g*Pg)+(b*b*Pb));
    r = p+(r-p)*level;
    if (r>255) r = 255;
    g = p+(g-p)*level;
    if (g>255) g = 255;
    b = p+(b-p)*level;
    if (b>255) b = 255;
    px->red = r;
    px->green = g;
    px->blue = b;
    return px;

}

struct ImageArr* testSatPixel(struct ImageArr *m, int l){

    int len = m->h*m->w;
    for(int i =0; i<len; i++){
        m->imgPixelData[i] = SaturatePixel(m->imgPixelData[i], l);
    }
    return m;

}

struct ImageArr* flip(struct ImageArr *m){
 
    int len = m->h * m->w;
    
    for(int i = 0; i<len/2; ++i){

        struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel));
        p = m->imgPixelData[i];
        m->imgPixelData[i] = m->imgPixelData[len - 1 - i];
        m->imgPixelData[len - 1 - i] = p;

    }
    return m;
}


void flipRow(struct pixel *arr, int w){

    for(int i=0; i<w/2; ++i){
        struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel));
        p = &arr[i];
        arr[i] = arr[w - 1 - i];
        arr[w- 1 - i] = *p;
    }

}

struct ImageArr* reflect(struct ImageArr *m){
 
    int h = m->h;
    int w = m->w;
    //int tmp = m->w;
    //m->w = m-> h;
    //m->h = tmp;
    
    for(int i = 0; i < h*w; i+=w){
        flipRow(m->imgPixelData[i], w);

    }
    return m;
}

struct ImageArr* addNoise(struct ImageArr *Im, float var, float mean){
    /// NEEDS WORK -- SEG FAULTING // 
    int x,y;
    float noise, theta;
    for(y =0; y< Im->h; y++){
        for(x = 0; x< Im->w; x++){
        noise = sqrt(-2 * var * log(1.0-(float)rand()/32767.1));
        theta = (float)rand()*1.917534E-4 - 3.14159265;
        noise = noise * cos(theta);
        noise = noise + mean;
        if(noise > 255)
            noise = 255;
        if (noise <0)
            noise = 0;


       // *(Im->imgPixelData+x+(long)y*Im->w) = (int)(noise +.5);       
        //printf("%d\n",y);
    }
    }
    return Im;

}



int main() {
 
    struct ImageArr *img;
    img = open("babboon.jpg");
    //img = Image(400,400);
    //printImageArr(img);
    //flip(img);
    //reflect(img);
    testSatPixel(img, 150);
    //addNoise(img, 800, 0);
    //save("noise.jpg", img);

    //struct pixel *p;
    //p = setPix(255,255,255,100);
    save("testsaturatepixel.jpg", img);  
    //free(img);
}
