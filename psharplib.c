#include "imageArr.c"



struct ImageArr *Image(int h, int w){
    //currently not working

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
    //currently not working
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
    //currently not working as intended. mirrors 2nd half of image to 1st half.
    for(int i=0; i<w/2; ++i){
        struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel));
        p = &arr[i];
        arr[i] = arr[w - 1 - i];
        arr[w- 1 - i] = *p;
    }

}

struct ImageArr* reflect(struct ImageArr *m){
    //currently not working
 
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
/*

    **** O(n^4) -> not tractable on large image files ****

void DConv(struct ImageArr *in, struct ImageArr *mask, struct ImageArr *out){

    long i,j,m,n,idx,jdx;
    int ms1,ms2,ms3,ms4,im1,im2,im3,im4,val1,val2,val3,val4;
    struct pixel *tmp;

    for(i=0; i<in->h; ++i)
        for(j=0; j< in->w; ++j){
            val1 = val2 = val3 = val4 = 0;
            for(m=0; m<mask->h; ++m)
                for(n =0; n<mask->w; ++n){
                    ms1 = mask->imgPixelData[m*mask->h+n]->red;
                    ms2 = mask->imgPixelData[m*mask->h+n]->green;
                    ms3 = mask->imgPixelData[m*mask->h+n]->blue;
                    ms4 = mask->imgPixelData[m*mask->h+n]->alpha;
                idx = i-m;
                jdx = j-n;
                if(idx >=0 && jdx >=0){
                    im1 = in->imgPixelData[idx*in->h+jdx]->red;
                    im2 = in->imgPixelData[idx*in->h+jdx]->green;
                    im3 = in->imgPixelData[idx*in->h+jdx]->blue;
                    im4 = in->imgPixelData[idx*in->h+jdx]->alpha;
                }
                val1 += ms1*im1;
                val2 += ms2*im2;
                val3 += ms3*im3;
                val4 += ms4*im4;

                }
            if(val1 > 255) val1 = 255;
            if(val2 > 255) val2 = 255;
            if(val3 > 255) val3 = 255;
            if(val4 > 255) val4 = 255;
            if(val1 < 0) val1 = 0;
            if(val2 < 0) val2 = 0;
            if(val3 < 0) val3 = 0;
            if(val4 < 0) val4 = 0;
            printf("VAL1: %d\n", val1);
            printf("VAL2: %d\n", val1);
            printf("VAL3: %d\n", val1);
            printf("VAL4: %d\n", val1);
            tmp->red = out->imgPixelData[i*out->h+j]->red;
            tmp->green = out->imgPixelData[i*out->h+j]->green;
            tmp->blue = out->imgPixelData[i*out->h+j]->blue;
            tmp->blue = out->imgPixelData[i*out->h+j]->alpha;
            tmp->red = (int)val1;
            tmp->green = (int)val2;
            tmp->blue = (int)val3;
            tmp->alpha = (int)val4;
        }
}
*/

struct ImageArr* addNoise(struct ImageArr *Im, float var, float mean){
//http://adaptiveart.eecs.umich.edu/2011/wp-content/uploads/2011/09/The-pocket-handbook-of-image-processing-algorithms-in-C.pdf
    /// NEEDS WORK -- SEG FAULTING // 
    int x,y,z,r;
    int cur = 0;
    float noise, theta;
    for(y =0; y < Im->h; y++){
        for(x = 0; x < Im->w; x++){
            
                r = rand()%32767;
        
                noise = sqrt(-2 * var * log(1.0-(float)r/32767.1));
                r = rand()%32767;
                theta = (float)r*1.9175345E-4 - 3.14159265;
                noise = noise * cos(theta);
                noise = noise + mean;
                if(noise > 255)
                noise = 255;
                if (noise < 0)
                noise = 0;
                printf("%f\n", noise);
                cur = rand()%3;
                if (cur == 0){ 
                    Im->imgPixelData[x+(long)y*Im->w]->red = (int)(noise +.5); 
                    
                }
                else if (cur == 1) {
                    Im->imgPixelData[x+(long)y*Im->w]->green = (int)(noise +.5);
                   
                }
                else if (cur == 2) {
                    Im->imgPixelData[x+(long)y*Im->w]->blue = (int)(noise +.5);
                 
                }
                else if (cur == 3){
                    Im->imgPixelData[x+(long)y*Im->w]->alpha = (int)(noise +.5);
                }
       
        
        //printf("%d\n",y);
    
    }
    }
    return Im;

}



int main() {
 
    struct ImageArr *img;
    struct ImageArr *img2;
    struct ImageArr *img3;
    img = open("testsaturate2.jpg");
    img2 = open("tree.jpg");
    img3 = open("reflected.jpg");
    //img = Image(400,400);
    //flip(img);
    //reflect(img);
    //testSatPixel(img, 150);
    //img = addNoise( img, 10000, 100);
    //save("noise.jpg", img);
    DConv(img,img2,img3);
    //struct pixel *p;
    //p = setPix(255,255,255,100);
    save("dc.jpg", img3);  
    //free(img);
}
