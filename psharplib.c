#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pixel.h"
#include "ImageStack.h"
#include "Album.h"
#include "psharplib.h"

float Min(float a, float b) {
	return a <= b ? a : b;
}

float Max(float a, float b) {
	return a >= b ? a : b;
}

struct ImageLayer* Contrast(struct ImageLayer* img, int level){

    struct ImageLayer *dest = newImageLayer(img->h, img->w);

    double factor = (259 * (((float)level + 255))/(255 * (259 - (float)level)));

    for(int i =0; i< img->w*img->h; i++){
        int rv = img->imgPixelData[i]->red;
        int gv = img->imgPixelData[i]->green;
        int bv = img->imgPixelData[i]->blue;
        double r = factor * (rv - (.5 * rv)) + (.5 * rv);
        double g = factor * (gv - (.5 * gv)) + (.5 * gv);
        double b = factor * (bv - (.5 * bv)) + (.5 * bv);
        if (r>255) r = 255;
        if (g>255) g = 255;
        if (b>255) b = 255;

        // tuned a bit so it doesn't completely blow out highlights
        if (r > 245 && g > 245 & b >= 245){
                g = (int)g*0.98;
                b = (int)r*0.98;
                r = (int)r*0.98;
        }
        dest->imgPixelData[i]->red = (int)r;
        dest->imgPixelData[i]->green = (int)g;
        dest->imgPixelData[i]->blue = (int)b;

    }

    return dest;

}
struct ImageLayer* Saturate(struct ImageLayer* img, int l){
// adapted from https://alienryderflex.com/saturation.html

    struct ImageLayer *dest = newImageLayer(img->h, img->w);
    double level = (double)l/100;
    float Pr = .299;
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

        dest->imgPixelData[i]->red = r;
        dest->imgPixelData[i]->green = g;
        dest->imgPixelData[i]->blue = b;
    }
    return dest;

}

struct ImageLayer* Rotate90(struct ImageLayer *img){

    int idx = 0;

    struct ImageLayer *dest = newImageLayer(img->w, img->h);

    for(int i= img->w-1; i >= 0; i--){
        for(int j = 0; j < img->h ; j++){

            dest->imgPixelData[idx]->red = img->imgPixelData[j*(img->w) + i]->red;
            dest->imgPixelData[idx]->green = img->imgPixelData[j*(img->w) + i]->green;
            dest->imgPixelData[idx]->blue = img->imgPixelData[j*(img->w) + i]->blue;
            dest->imgPixelData[idx]->alpha = img->imgPixelData[j*(img->w) + i]->alpha;
            idx++;

        }
    }

    return dest;
}


struct ImageLayer* ReflectY(struct ImageLayer *m){
    int h = m->h;
    int w = m->w;
    struct ImageLayer *dest = newImageLayer(m->h, m->w);
    int idx = 0;
    for(int i = h-1; i > 0; i--){
        for(int j = 0 ; j < w ; j++){

            int toChange = i*w-1 +j;
            dest->imgPixelData[idx]->red = m->imgPixelData[toChange] -> red;
            dest->imgPixelData[idx]->green = m->imgPixelData[toChange] -> green;
            dest->imgPixelData[idx]->blue = m->imgPixelData[toChange] -> blue;
            dest->imgPixelData[idx]->alpha = m->imgPixelData[toChange] -> alpha;
            idx++;
        }
    }
    return dest;
}


struct ImageLayer* ReflectX(struct ImageLayer *m){
    int h = m->h;
    int w = m->w;
    struct ImageLayer *dest = newImageLayer(m->h, m->w);
    int idx = 0;
    for(int i = 1; i < h; i++){
        for(int j = 0 ; j < w ; j++){

            int toChange = i*w -j;
            dest->imgPixelData[idx]->red = m->imgPixelData[toChange] -> red;
            dest->imgPixelData[idx]->green = m->imgPixelData[toChange] -> green;
            dest->imgPixelData[idx]->blue = m->imgPixelData[toChange] -> blue;
            dest->imgPixelData[idx]->alpha = m->imgPixelData[toChange] -> alpha;
            idx++;
        }
    }
    return dest;
}


/***********************************
 *  values for var between 0-1000
 *  values for mean between 0-100
***********************************/
struct ImageLayer *addNoise(struct ImageLayer *Im, float var, float mean){
// addNoise() adapted from algorithm below, which applies gaussian noise to B&W images
// http://adaptiveart.eecs.umich.edu/2011/wp-content/uploads/2011/09/The-pocket-handbook-of-image-processing-algorithms-in-C.pdf
    int x,y,z,r;
    int cur = 0;
    int idx = 0;
    float noise, theta;
    struct ImageLayer *dest = newImageLayer(Im->h, Im->w);
    for(y =0; y < Im->h; y++){
        for(x = 0; x < Im->w; x++){

                r = rand()%32767;
                noise = sqrt(-2 * var * log(1.0-(float)r/32767.1));
                r = rand()%32767;
                theta = r*1.9175345E-4 - 3.14159265;
                noise = noise * cos(theta);
                noise = noise + mean;

                if(noise > 255) noise = 255; // normalizing extreme values
                if (noise < 0) noise = 0;

                cur = rand()%3;

                //copying over original image data
                dest->imgPixelData[idx]->red = Im->imgPixelData[idx]->red;
                dest->imgPixelData[idx]->green = Im->imgPixelData[idx]->green;
                dest->imgPixelData[idx]->blue = Im->imgPixelData[idx]->blue;
                dest->imgPixelData[idx]->alpha = Im->imgPixelData[idx]->alpha;

                //applying gaussian noise
                if (cur == 0){
                    dest->imgPixelData[x+(long)y*Im->w]->red = (unsigned char)(noise +.5);
                }
                else if (cur == 1) {
                    dest->imgPixelData[x+(long)y*Im->w]->green = (unsigned char)(noise +.5);
                }
                else if (cur == 2) {
                    dest->imgPixelData[x+(long)y*Im->w]->blue = (unsigned char)(noise +.5);
                }
                else if (cur == 3){
                    dest->imgPixelData[x+(long)y*Im->w]->alpha = (unsigned char)(noise +.5);
                }

                idx++;
        }
    }
    return dest;
}

struct ImageLayer *Tint(struct ImageLayer *img, int level){

    struct ImageLayer *dest = newImageLayer(img->h, img->w);
    for(int i =0; i< img->h*img->w; i++){

            dest->imgPixelData[i]->red = img->imgPixelData[i]->red;
            if (!(img->imgPixelData[i]->green + level > 255))
                dest->imgPixelData[i]->green = img->imgPixelData[i]->green + level;
            else
                dest->imgPixelData[i]->green = img->imgPixelData[i]->green;
                dest->imgPixelData[i]->blue = img->imgPixelData[i]->blue;
                dest->imgPixelData[i]->alpha= img->imgPixelData[i]->alpha;

    }

    return dest;

}

struct ImageLayer *Crop(struct ImageLayer *img, float pct){

    float cropPct = pct/100;
    int maxH = img->h * cropPct;
    int maxW = img->w * cropPct;
    int h_off = (img->h - maxH)/2;
    int w_off = (img->w - maxW)/2;

    struct ImageLayer *dest = newImageLayer(maxH, maxW);

    int idx = 0;

    for (int i = h_off ; i < maxH + h_off; i++ ){
        for(int j = w_off; j< maxW + w_off; j++){
            dest->imgPixelData[idx]->red = img->imgPixelData[i*img->w + j]->red;
            dest->imgPixelData[idx]->green = img->imgPixelData[i * img->w + j]->green;
            dest->imgPixelData[idx]->blue = img->imgPixelData[i * img->w + j]->blue;
            dest->imgPixelData[idx]->alpha = img->imgPixelData[i * img->w + j]->alpha;
            idx++;
        }
    }

    return dest;

}

struct ImageLayer *Kelvin(struct ImageLayer *img, float K){
    // level refers to blend strength, and is inversely related to how
    // much of the color will appear on the image.
    // ** rbg from temp algorithm adapted from Tanner Heller **
    // added code to blend the aquired kelvin value with each pixel's RGB channels.
    if (K>40000)K=40000;
    if (K<1000)K=1000;

    double k = K/100;
    double temp;
    int r,g,b;
    double strength =  .999; //(double)level/110;
    //double ln_minus_60 = log(k-60)
    struct ImageLayer *dest = newImageLayer(img->h, img->w);


    for(int i =0; i< img->w*img->h; i++){

        if (k <= 66){
            r = 255;
        }
        else{
            temp = k-60;
            temp = 329.698727446 * pow(temp, -0.1332047592);
            r = (int)temp;
            if(r > 255) r = 255;
            else if(r < 0 ) r = 0;
            //else
            dest->imgPixelData[i]->red = img->imgPixelData[i]->red * strength + r*(1-strength) ;
        }
        if (k<=66){
            temp = k;
            temp = 99.4708025861 * log(temp) - 161.1195681661;
            g = (int)temp;
            if(g > 255) g = 255;
            if(g < 0 ) g = 0;
            //else
            dest->imgPixelData[i]->green = img->imgPixelData[i]->green * strength + g*(1-strength) ;
        }
        else{
            temp = k - 60;
            temp = 288.1221695283 * pow(temp, -0.0755148492);
            g = (int)temp;
            if(g > 255) g = 255;
            if(g < 0 ) g = 0;
            //else img->imgPixelData[i]->green =
            dest->imgPixelData[i]->green = img->imgPixelData[i]->green * strength + g*(1-strength)  ;
        }
        if (k >= 66){
            b = 255;
        }
        else if ( k <= 19){
            b = 0;
        }
        else{
            temp = k-10;
            temp = 138.5177312231 * log(temp) - 305.0447927307;
            b = (int)temp;
            if(b > 255) b = 255;
            if(b < 0 ) b= 0;
            //else img->imgPixelData[i]->blue =
            dest->imgPixelData[i]->green = img->imgPixelData[i]->blue * strength + b*(1-strength) ;
        }
    }

    return dest;
}
// ***********************
// amt is the amount to increase or decrease the brightness intensity
// ***********************
struct ImageLayer *Brightness(struct ImageLayer *img, int amt){

		struct ImageLayer *dest = newImageLayer(img->h, img->w);

		for(int i =0; i < img->h*img->w; i++) {
			dest->imgPixelData[i]->red = img->imgPixelData[i]->red + amt < 255 ? img->imgPixelData[i]->red + amt : 255;
			dest->imgPixelData[i]->blue = img->imgPixelData[i]->blue + amt < 255 ? img->imgPixelData[i]->blue + amt : 255;
			dest->imgPixelData[i]->green = img->imgPixelData[i]->green + amt < 255 ? img->imgPixelData[i]->green + amt : 255;
			dest->imgPixelData[i]->alpha = img->imgPixelData[i]->alpha;
		}

		return dest;
}

// ***********************
// c is the character that represents the color image : g - green, b - blue, r -red
// ***********************
struct ImageLayer *RGBImage(struct ImageLayer *img, int value){

		struct ImageLayer *dest = newImageLayer(img->h, img->w);

		if (value == 1) {

			for(int i =0; i < img->h*img->w; i++) {
				dest->imgPixelData[i]->red = img->imgPixelData[i]->red;
				dest->imgPixelData[i]->blue = 0;
				dest->imgPixelData[i]->green = 0;
				dest->imgPixelData[i]->alpha = img->imgPixelData[i]->alpha;
			}
			return dest;
		}
		else if (value == 2) {

			for(int i =0; i < img->h*img->w; i++) {
				dest->imgPixelData[i]->red = 0;
				dest->imgPixelData[i]->blue = 0;
				dest->imgPixelData[i]->green = img->imgPixelData[i]->green;
				dest->imgPixelData[i]->alpha = img->imgPixelData[i]->alpha;
			}
			return dest;

		}
		else if (value == 3) {

			for(int i =0; i < img->h*img->w; i++) {
				dest->imgPixelData[i]->red = 0;
				dest->imgPixelData[i]->blue = img->imgPixelData[i]->blue;
				dest->imgPixelData[i]->green = 0;
				dest->imgPixelData[i]->alpha = img->imgPixelData[i]->alpha;
			}
			return dest;

		}
		else {
			return img;
		}
}

//  **********************
//  RGB / HSL CONVERSIONS
//  adapted for our data structures from
//  https://www.programmingalgorithms.com/algorithm/hsl-to-rgb?lang=C
//  **********************
struct HSL *RGBToHSL(struct pixel* rgb) {
	struct HSL *hsl = (struct HSL *)malloc(sizeof(struct HSL));



	float r = (rgb->red / 255.0f);
	float g = (rgb->green / 255.0f);
	float b = (rgb->blue / 255.0f);

	float min = Min(Min(r, g), b);
	float max = Max(Max(r, g), b);
	float delta = max - min;

	hsl->L = (max + min) / 2;

	if (delta == 0)
	{
		hsl->H = 0;
		hsl->S = 0.0f;
	}
	else
	{
		hsl->S = (hsl->L <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

		float hue;

		if (r == max) hue = ((g - b) / 6) / delta;

		else if (g == max) hue = (1.0f / 3) + ((b - r) / 6) / delta;
		else hue = (2.0f / 3) + ((r - g) / 6) / delta;

		if (hue < 0)
			hue += 1;
		if (hue > 1)
			hue -= 1;
		hsl->H = (int)(hue * 365);
	}

	return hsl;
}


float HueToRGB(float v1, float v2, float vH)
{
	if (vH < 0)
		vH += 1;
	if (vH > 1)
		vH -= 1;
	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);
	if ((2 * vH) < 1)
		return v2;
	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);
	return v1;
}


struct pixel *HSLToRGB(struct HSL *hsl) {
	struct pixel *rgb = (struct pixel *)malloc(sizeof(struct pixel));
    int r,g,b;
    float avg;

    if (hsl->S > 1) hsl->S = 1;

	if (hsl->S == 0)
	{
		rgb->red = rgb->green = rgb->blue = hsl->L * 255;
	}
	else
	{
		float v1, v2;
		float hue = (float)hsl->H / 365;
		v2 = (hsl->L < 0.5) ? (hsl->L * (1 + hsl->S)) : ((hsl->L + hsl->S) - (hsl->L * hsl->S));
		v1 = 2 * hsl->L - v2;
		r = (int)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		g = (int)(255 * HueToRGB(v1, v2, hue));
		b = (int)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        rgb->red = r;
        rgb->green = g;
        rgb->blue = b;
	}
	return rgb;
}

/*******
        USAGE:
            factor:  value from 0-200;  < 100 indicates no change >
            hsl:  1,2,3 for hue, saturation, luminance, respectively; 0 to change all.
            channel:  1,2,3 for red,green,blue respectively; 0 to saturate all.
********/
struct ImageLayer* HSL(struct ImageLayer *m, int factor, int hsl, int channel){
        double f = (double)factor/100;
        struct ImageLayer *dest = newImageLayer(m->h, m->w);
        struct HSL *hsl_tmp = (struct HSL *)malloc(sizeof(struct HSL));
        struct pixel *rgb_tmp = (struct pixel *)malloc(sizeof(struct pixel));
        struct pixel **buf;
        buf = (struct pixel **)malloc(sizeof(struct pixel *) * (m->h * m->w));
        struct pixel *tmp;
        int r,g,b;


        for(int i = 0; i < m->h * m->w; i++){

            tmp = makePix();
            tmp->red = m->imgPixelData[i]->red;
            tmp->green = m->imgPixelData[i]->green;
            tmp->blue = m->imgPixelData[i]->blue;

            dest->imgPixelData[i]->red = m->imgPixelData[i]->red;
            dest->imgPixelData[i]->green = m->imgPixelData[i]->green;
            dest->imgPixelData[i]->blue = m->imgPixelData[i]->blue;

            hsl_tmp = RGBToHSL( tmp);


            if(hsl == 1) hsl_tmp->H *= f;          // change hue by a factor of f
            else if(hsl == 2) hsl_tmp->S *= f;     // change saturation by a factor of f
            else if(hsl == 3) hsl_tmp->L *= f;     // change luminance by a factor of f
            else if(hsl == 0){                     // change all hsl by a factor of f
                hsl_tmp->H *= f;
                hsl_tmp->S *= f;
                hsl_tmp->L *= f;
            }

            rgb_tmp = HSLToRGB(hsl_tmp);


            if(channel == 1) tmp->red = (rgb_tmp->red);                // only adjust red
            else if (channel == 2) tmp->green = (rgb_tmp->green);    // only adjust green
            else if (channel == 3) tmp->blue = (rgb_tmp->blue);       // only adjust blue
            else if (channel == 0) {                                      // adjust all r,g,b
                tmp->red = (rgb_tmp->red);
                tmp->green = (rgb_tmp->green);
                tmp->blue = (rgb_tmp->blue);
            }
            buf[i] = tmp;
        }
    dest->imgPixelData = buf;

    return dest;
}
void GradHSL(struct ImageGradient *grad, int factor, int hsl, int channel){

        double level = (double)factor/100;
        double f;
        if (grad->direction == 1) f = 1.0;
        else f = level;

        struct ImageGradient *dest = newGradFromGrad(grad);
        struct HSL *hsl_tmp = (struct HSL *)malloc(sizeof(struct HSL));
        struct pixel *rgb_tmp = (struct pixel *)malloc(sizeof(struct pixel));
        int r,g,b;

        for(int i = 0; i < grad->h * grad->w; i++){

            dest->imgPixelData[i]->red = grad->imgPixelData[i]->red;
            dest->imgPixelData[i]->green = grad->imgPixelData[i]->green;
            dest->imgPixelData[i]->blue = grad->imgPixelData[i]->blue;

            hsl_tmp = RGBToHSL( grad->imgPixelData[i]);

            if ( i % grad->w == 0){
                if(grad->direction == 1){
                    if(factor < 100){
                        f -= (1-level)/grad->h;
                    }
                    else{
                        f += (level-1)/(grad->h);
                    }
                }
                else{
                    if(factor < 100){}
                        f -= (level-1)/grad->h;

                }
                if(level == 1.0) f = 1.0;
            }

            if(hsl == 1) hsl_tmp->H *= f;          // change hue by a factor of f
            else if(hsl == 2) hsl_tmp->S *= f;     // change saturation by a factor of f
            else if(hsl == 3) hsl_tmp->L *= f;     // change luminance by a factor of f
            else if(hsl == 0){                     // change all hsl by a factor of f
                hsl_tmp->H *= f;
                hsl_tmp->S *= f;
                hsl_tmp->L *= f;
            }

            rgb_tmp = HSLToRGB(hsl_tmp);
            r = rgb_tmp->red;
            g = rgb_tmp->green;
            b = rgb_tmp->blue;


            if(channel == 1) dest->imgPixelData[i]->red = (rgb_tmp->red);                // only adjust red
            else if (channel == 2) dest->imgPixelData[i]->green = (rgb_tmp->green);    // only adjust green
            else if (channel == 3) dest->imgPixelData[i]->blue = (rgb_tmp->blue);       // only adjust blue
            else if (channel == 0) {                                                    // adjust all r,g,b
                dest->imgPixelData[i]->red = rgb_tmp->red;
                dest->imgPixelData[i]->green = rgb_tmp->green;
                dest->imgPixelData[i]->blue = rgb_tmp->blue;
            }
        }

}
void GradContrast(struct ImageGradient *grad, int level){

    struct ImageGradient *dest = newGradFromGrad(grad);
    double factor;
    double toScale = (259 * (((float)level + 255))/(255 * (259 - (float)level)));
    if(grad->direction==1) factor = 0;
    else factor = toScale;

    for(int i =0; i< grad->w*grad->h; i++){
        int rv = grad->imgPixelData[i]->red;
        int gv = grad->imgPixelData[i]->green;
        int bv = grad->imgPixelData[i]->blue;

        if ( i % grad->w == 0){
            if(grad->direction == 1){
                factor += toScale/grad->h;
            }
            else{
                factor -= toScale/grad->h;
            }
        }

        double r = factor * (rv - (.5 * rv)) + (.5 * rv);
        double g = factor * (gv - (.5 * gv)) + (.5 * gv);
        double b = factor * (bv - (.5 * bv)) + (.5 * bv);
        if (r>255) r = 255;
        if (g>255) g = 255;
        if (b>255) b = 255;
        if (r<0) r = 0;
        if (g<0) g = 0;
        if (b<0) b = 0;

        // tuned a bit so it doesn't completely blow out highlights
        if (r > 245 && g > 245 & b >= 245){
                g = g*0.98;
                b = b*0.98;
                r = r*0.98;
        }
        dest->imgPixelData[i]->red = (unsigned char)r;
        dest->imgPixelData[i]->green = (unsigned char)g;
        dest->imgPixelData[i]->blue = (unsigned char)b;

    }
    grad->imgPixelData = dest->imgPixelData;

}
void GradBrightness(struct ImageGradient *grad, int amt){

		struct ImageGradient *dest = newGradFromGrad(grad);
        
        double sofar;
        if(grad->direction == 1) sofar = 0;
        else sofar = amt;

		for(int i =0; i< grad->h*grad->w; i++) {
            if(i % grad->w == 0){
                if(grad->direction == 1){
                    sofar += (double)amt/grad->h;
                }
                else if (grad->direction == 0){
                    sofar -= (double)amt/grad->h;
                }
            }
            dest->imgPixelData[i]->red = grad->imgPixelData[i]->red + sofar < 255 ? grad->imgPixelData[i]->red + sofar : 255;
			dest->imgPixelData[i]->blue = grad->imgPixelData[i]->blue + sofar < 255 ? grad->imgPixelData[i]->blue + sofar : 255;
			dest->imgPixelData[i]->green = grad->imgPixelData[i]->green + sofar < 255 ? grad->imgPixelData[i]->green + sofar : 255;
			dest->imgPixelData[i]->alpha = grad->imgPixelData[i]->alpha;
		}

        grad->imgPixelData = dest->imgPixelData;
}

/*
int main() {

    struct ImageStack *img;
    struct ImageStack *img2;
    struct ImageStack *img3;

    img = open("d1.jpg");
    img2 = open("d1.jpg");
    img3 = open("d1.jpg");

    struct Album *a = newAlbum();
    addToAlbum(a, img);
    addToAlbum(a, img2);
    addToAlbum(a, img3);

    for(int i = 0; i<3; i++){
        a->images[i]->imgArray[a->images[i]->top - 1] = ReflectY(a->images[i]->imgArray[a->images[i]->top - 1]);
        if(i == 0)
            save ("ALBUM0.jpg", a->images[i]);
        else if(i == 1)
            save ("ALBUM1.jpg", a->images[i]);
        else if(i == 2)
            save ("ALBUM2.jpg", a->images[i]);
        else if(i == 3)
            save ("ALBUM3.jpg", a->images[i]);

    }

    addToAlbum(a, img5);
    addToAlbum(a, img6);
    addToAlbum(a, img7);
        for(int i = 0; i<7; i++){
        a->images[i]->imgArray[a->images[i]->top - 1] = ReflectY(a->images[i]->imgArray[a->images[i]->top - 1]);
        if(i == 0)
            save ("ALBUM0.jpg", a->images[i]);
        else if(i == 1)
            save ("ALBUM1.jpg", a->images[i]);
        else if(i == 2)
            save ("ALBUM2.jpg", a->images[i]);
        else if(i == 3)
            save ("ALBUM3.jpg", a->images[i]);
        else if(i == 4)
            save ("ALBUM4.jpg", a->images[i]);
        else if(i == 5)
            save ("ALBUM5.jpg", a->images[i]);
        else if(i == 6)
            save ("ALBUM6.jpg", a->images[i]);
        else if(i == 7)
            save ("ALBUM7.jpg", a->images[i]);


    }
    printf("%d\n", a->size);

    free(a);

    //save("d.jpg", img);
    //img2 = open("d2.jpg");
    //img3->imgArray[img3->top - 1] = newImageLayer(100,100);
    //save("blank.jpg", img);
    //img->imgArray[img->top - 1] = flip(img->imgArray[img->top - 1]);
    //save("flip.jpg", img);
    //img->imgArray[img->top - 1] = reflect(img->imgArray[img->top - 1]);
    // save("reflect.jpg", img);
    //img->imgArray[img->top - 1] = testSatPixel(img->imgArray[img->top - 1], 105);
    //save("testSatPixel.jpg", img);
    //img->imgArray[img->top - 1] = addNoise( img->imgArray[img->top - 1], 50, 0);
    //save("addNoise.jpg", img);
    //img->imgArray[img->top - 1] = Contrast(img->imgArray[img->top - 1], 80);
    //save("Contrast.jpg", img);
    //img->imgArray[img->top - 1] = Kelvin(img->imgArray[img->top - 1], 8000);
    //save("Kelvin8000.jpg", img);
    //img->imgArray[img->top - 1] = Rotate90(img->imgArray[img->top - 1]);
    //save("Rotate90.jpg", img);
    //img->imgArray[img->top-1] = HSL(img->imgArray[img->top -1], 150, 2, 2 ); // test sat green;
    //img->imgArray[img->top-1] = ReflectX(img->imgArray[img->top -1]);
    //save("testRefX.jpg", img);
    //img->imgArray[img->top-1] = ReflectY(ReflectX(img->imgArray[img->top -1]));
    //save("testRefYX.jpg", img);
    //save("noise.jpg", img);
    //DConv(img->imgArray[img->top - 1],img2->imgArray[img2->top - 1],img3->imgArray[img3->top - 1]);
    //struct pixel *p;
    //p = setPix(255,255,255,100);
    //save("test.jpg", img);
    //free(img);
    //free(img);
    return 0;
}
*/

/*
int main() {
    struct ImageStack *i;
    i = open("test3.jpg");
    struct ImageGradient *grad = newImageGradient(i, 0);
    GradBrightness(grad, 30);
    GradToLayer(i, grad);
    //i->imgArray[i->top-1] = HSL(i->imgArray[i->top-1], 150, 2, 1);
    //i->imgArray[i->top-1] = Saturate(i->imgArray[i->top-1], 105);
    save("grad0test.jpg", i);

}
*/
/*
int main() {

    struct ImageStack* img;

    img = open("test.jpg");
    int size;

    size = ImageSize(img);

    printf("Size: %d\n", size);

    int i;
    for(i = 0; i < size; i++) {
        PixelSaturate(getPixel(img, i), 0);
    }

    save("tesingme.jpg", img);

}
*/
