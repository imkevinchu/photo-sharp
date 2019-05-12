#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#include "ImageStack.h"
#include "psharplib.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//Defines ImageStack type -- which is used for the Photo# "Image" type.
//Also defines ImageLayer type, which is the type used for each layer in an
//ImageStack.

//Uses public domain headers "stb_image.h" and "stb_image_write.h". See those files
//for more details on their author.

// Defines the maximim number of versions to be stored in an ImageStack
#define STACKSIZE 5

//Return a pointer to a specific pixel in the top layer
//of an image stack -- used for iteration
struct pixel *getPixel(struct ImageStack *img, int index) {
    struct ImageLayer *topLay = img->imgArray[img->top - 1];

    return topLay->imgPixelData[index];
}

//Return the size of the top layer of an ImageStack
int ImageSize(struct ImageStack *img) {
    int size;
    struct ImageLayer *topLay = img->imgArray[img->top - 1];
    size = ((topLay->w) * (topLay->h));
    return(size);
}

//push a previously malloc-ed ImageLayer onto a previously malloc-ed ImageStack
void pushLayer(struct ImageStack *img, struct ImageLayer *lay) {
    
    img->imgArray[img->top] = lay;
    img->top++;
   
    if(img->top == STACKSIZE) {
        img->top = 0;
    }
} 

//pop the last ImageLayer off the ImageStack. Function will return the popped layer.
//NOTE: it is the responsibility of the calling function to free the popped layer. 
struct ImageLayer *popLayer(struct ImageStack *img) {

    struct ImageLayer *lay;
    lay = img->imgArray[img->top -1];
 
    if(img->top == 0) {
        if(img->imgArray[4] == NULL) {
            img->top = 0;
        } else {
            img->top = 4;
        }
    } else { 
        (img->top)--;
    }     
    return lay;
}

//Free an ImageLayer and all pixel structures associated with it    
void freeLayer(struct ImageLayer *lay) {

    for(int i = 0; i < (lay->h * lay->w); i++) {
        free(lay->imgPixelData[i]);
    }

    free(lay);

}

//Free all ImageLayers belonging to an ImageStack
void freeImageStack(struct ImageStack *stack){

    for (int i = 0; i < stack->top; i++){
        if(stack->imgArray[i] != NULL) {
            freeLayer(stack->imgArray[i]);
        }
    }
    free(stack);

}

void ImageRevert(struct ImageStack *im){

    freeLayer(popLayer(im));

}

//create a new Image layer of the requested dimensions
//to handle memory allocation in image editing functions
struct ImageLayer *newImageLayer(int hi, int wi) {
    
    struct ImageLayer *lay = (struct ImageLayer *)malloc(sizeof(struct ImageLayer));

    struct pixel* temp;
    int x = 0;

    lay->h = hi;
    lay->w = wi;

    int j = 0;

    struct pixel **buf;
    buf = (struct pixel **)malloc(sizeof(struct pixel *)*(wi * hi)); 

    lay->imgPixelData = buf;

    int next = 0;

    while(j < (hi * wi)) {
        temp = makePix();
        lay->imgPixelData[j] = temp;
        j++;

    }

    return lay;
} 

struct ImageGradient *newImageGradient(struct ImageLayer* lay, unsigned char dir){
    struct ImageGradient *grad = (struct ImageGradient *)malloc(sizeof(struct ImageGradient));
    struct pixel *temp;
    struct pixel **buf; 
    buf = (struct pixel **)malloc(sizeof(struct pixel *) * (lay->h * lay->w)); 
    grad->imgPixelData = buf;
    int j = 0;
    while(j < (lay->h*lay->w)) {
        temp = makePix();
        temp->red = lay->imgPixelData[j]->red;
        temp->green= lay->imgPixelData[j]->green;
        temp->blue = lay->imgPixelData[j]->blue;
        temp->alpha = lay->imgPixelData[j]->alpha;
        grad->imgPixelData[j] = temp;
        j++;

    }
    grad->direction = dir;
    grad->h = lay->h;
    grad->w = lay->w;
    
    return grad;
    
} 
struct ImageGradient *newGradFromGrad(struct ImageGradient* lay){
    struct ImageGradient *grad = (struct ImageGradient *)malloc(sizeof(struct ImageGradient));
    struct pixel *temp;
    struct pixel **buf; 
    buf = (struct pixel **)malloc(sizeof(struct pixel *) * (lay->h * lay->w)); 
    for (int i = 0 ; i < lay->h * lay->w; i++){
        buf[i] = lay->imgPixelData[i];
    }
    grad->direction = lay->direction;
    grad->imgPixelData = buf;
    grad->h = lay->h;
    grad->w = lay->w;
    
    return grad;
    
} 

struct ImageLayer *GradToLayer(struct ImageGradient *grad){
    struct ImageLayer *lay = (struct ImageLayer *)malloc(sizeof(struct ImageLayer));
    lay->h = grad->h;
    lay->w = grad->w;
    lay->imgPixelData = grad->imgPixelData;
    return lay;

}


//create new, empty, ImageStack
struct ImageStack *newImageStack() {

    struct ImageStack* img = (struct ImageStack *)malloc(sizeof(struct ImageStack));

    struct ImageLayer **buf;
    buf = (struct ImageLayer **)malloc(sizeof(struct ImageLayer *) * (STACKSIZE));

    img->imgArray = buf;
    img->top = 0;

    return img;
}

//save the top layer of an image to a designated file name
int save(char const *filename, struct ImageStack *img){
   
    int topLayer = img->top - 1;

    struct pixel **data = img->imgArray[topLayer]->imgPixelData;
    unsigned char *temp;

    int hi = img->imgArray[topLayer]->h;
    int wi = img->imgArray[topLayer]->w;

    temp = (unsigned char *)malloc(sizeof(int)*(wi * hi * 4)); 

    int x = 0;

    for(int i = 0; i < wi * hi; i++)
    {
        temp[x++] = (unsigned char)data[i]->red;
        temp[x++] = (unsigned char)data[i]->green;
        temp[x++] = (unsigned char)data[i]->blue;
        temp[x++] = (unsigned char)data[i]->alpha;
    }

    return(stbi_write_jpg(filename, wi, hi, 4, temp, 100));
}

//open a file and save to a new ImageLayer
struct ImageLayer *openFile(char *fileName){

    int hi;
    int wi;
    int chan;

    unsigned char *data = stbi_load(fileName, &wi, &hi, &chan, 4);

    struct ImageLayer *lay = newImageLayer(hi, wi);

    struct pixel* temp;
    int x = 0;

    lay->h = hi;
    lay->w = wi;

    int j = 0;

    int next = 0;

    while(j < (hi * wi * 4))
    {

        if(next == 0) {
            lay->imgPixelData[x]->red = (int)data[j];
            next = 1;
        } else if(next == 1) {
            lay->imgPixelData[x]->green = (int)data[j];
            next = 2;
        } else if(next == 2) {
            lay->imgPixelData[x]->blue = (int)data[j];
            next = 3;
        } else if(next == 3) {
            lay->imgPixelData[x]->alpha = (int)data[j];
            next = 0;

            x = x + 1;
        }

        j++;
    }

    stbi_image_free(data);
    return lay;

}

//Open a file and set the first layer of an ImageStack to this file. For now, we can initialize to opened file only
struct ImageStack *open(char *fileName) {

    struct ImageStack *img = newImageStack();

    struct ImageLayer *base;
    base = openFile(fileName);
    pushLayer(img, base);

    return img;

}

//Print the top layer of an ImageStack
void PrintImage(struct ImageStack *img) {

    int topLayer = img->top - 1;

    int imgSize = (img->imgArray[topLayer]->h)*(img->imgArray[topLayer]->w);

    int i;
    for (i = 0; i<imgSize; i++){

        printPix(img->imgArray[topLayer]->imgPixelData[i]);
    }
    printf("\n");
}

//Codegen interface functions
//Equivalent function calls which do the heavy lifting are in the psharplib.c file

void ImageContrast(struct ImageStack *img, int lev) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = Contrast(img->imgArray[topLevel], lev);

    pushLayer(img, lay);
}

void ImageSaturate(struct ImageStack *img, int lev) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = Saturate(img->imgArray[topLevel], lev);

    pushLayer(img, lay);
}

void ImageRotate90(struct ImageStack *img) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = Rotate90(img->imgArray[topLevel]);

    pushLayer(img, lay);
}

void ImageAddNoise(struct ImageStack *img, double var, double mean) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = addNoise(img->imgArray[topLevel], (float)var, (float)mean);

    pushLayer(img, lay);
}

void ImageKelvin(struct ImageStack *img, double lev) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = Kelvin(img->imgArray[topLevel], (float)lev);

    pushLayer(img, lay);
}

void ImageReflectY(struct ImageStack *img) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = ReflectY(img->imgArray[topLevel]);

    pushLayer(img, lay);
}

void ImageReflectX(struct ImageStack *img) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = ReflectX(img->imgArray[topLevel]);

    pushLayer(img, lay);
}

void ImageTint(struct ImageStack *img, int lev) {

    int topLevel = img->top - 1;

    struct ImageLayer *lay;
    lay = Tint(img->imgArray[topLevel], lev);

    pushLayer(img, lay);
}

void ImageCrop(struct ImageStack *img, double p) {

    int topLevel = img->top - 1;

    float f = (float)p;

    struct ImageLayer *lay;
    lay = Crop(img->imgArray[topLevel], f);

    pushLayer(img, lay);
}


void GradientContrast(struct ImageGradient *img, int lev) {

    struct ImageGradient *grad;
    GradContrast(grad, lev);

}

void GradientHSL(struct ImageGradient *img, int lev, int hsl, int channel){

    struct ImageGradient *grad;
    GradHSL(grad, lev, hsl, channel);
}



/*

int main() {
 
    struct ImageStack* img;
  
    img = open("test.jpg");
    int size;

    size = ImageSize(img);

    printf("Size: %d\n", size);
 

}
*/
