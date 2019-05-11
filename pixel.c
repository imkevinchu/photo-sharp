#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pixel.h"

struct pixel *makePix() {
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel)); 
  return p;

}

struct pixel *setPix(int r, int g, int b, int a) {  
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel)); 

  p->red = (unsigned char)r;
  p->green = (unsigned char)g;
  p->blue = (unsigned char)b;
  p->alpha = (unsigned char)a;

  return p;

}

int RedPixel(struct pixel *p) {  

  p->red = 255;
  p->green = 0;
  p->blue = 0;
  p->alpha = 0;

  return 0;

}

int GreenPixel(struct pixel *p) {  

  p->red = 0;
  p->green = 255;
  p->blue = 0;
  p->alpha = 0;

  return 0;

}

int BluePixel(struct pixel *p) {  

  p->red = 0;
  p->green = 0;
  p->blue = 255;
  p->alpha = 0;

  return 0;

}

//Edit the saturation level of one pixel
int PixelSaturate(struct pixel* px, int l){

    double level = (double)l/100;
    float Pr = .299;
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
    px->alpha = px->alpha;
    return 0;

}

void SetRGB(struct pixel* p, int r, int g, int b, int a){
    p->red = r;
    p->green = g;
    p->blue = b;
    p->alpha = a;
}

void ModRGB(struct pixel* p, int redMod, int greenMod, int blueMod, int alphaMod){
    p->red += redMod;
    p->green += greenMod;
    p->blue += blueMod;
    p->alpha += alphaMod;
}

//Set individual pixel component values
void SetRed(struct pixel*p, int r){
    p->red = r;
}
void SetGreen(struct pixel*p, int g){
    p->green = g;
}
void SetBlue(struct pixel*p, int b){
    p->blue = b;
}
void SetAlpha(struct pixel*p, int a){
    p->alpha = a;
}

//Modify individual pixel component values
void modRed(struct pixel*p, int rmod){
    p->red += rmod;
}
void modGreen(struct pixel*p, int gmod){
    p->green += gmod;
}
void modBlue(struct pixel*p, int bmod){
    p->blue += bmod;
}
void modAlpha(struct pixel*p, int amod){
    p->alpha += amod;
}

void printPix(struct pixel *pix) {
  printf("Red: %d\n", pix->red);
  printf("Green: %d\n", pix->green);
  printf("Blue: %d\n", pix->blue);
  printf("Alpha: %d\n", pix->alpha);
}

/*#ifdef BUILD_TEST
int main() {
  struct pixel *p;
  p = setPix(12, 3, 4, 10);  
  printPix(p);
  return 0;
}
#endif*/
