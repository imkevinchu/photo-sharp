#include <stdio.h>
#include <stdlib.h>
#include "pixel.c"
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//Defines ImageStack type -- which is used for the Photo# "Image" type.
//Also defines ImageLayer type, which is the type used for each layer in an
//ImageStack.

//Uses public doman headers "stb_image.h" and "stb_image_write.h". See those files
//for more details on their author.

struct ImageLayer {
    int h;
    int w;
    struct pixel **imgPixelData;
};

struct ImageStack {
    int top;
    struct ImageLayer **imgArray;
};

//push a previously malloc-ed ImageLayer onto a previously malloc-ed ImageStack
void pushLayer(struct ImageStack *img, struct ImageLayer *lay) {
    
    img->imgArray[img->top] = lay;
    img->top++;
   
    if(img->top == 5) {
        img->top = 0;
    }
} 

//create new, empty, ImageStack
struct ImageStack *newImageStack() {

    struct ImageStack* img = (struct ImageStack *)malloc(sizeof(struct ImageStack));

    struct ImageLayer **buf;
    buf = (struct ImageLayer **)malloc(sizeof(struct ImageLayer *)*(5));

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

    struct ImageLayer* lay = (struct ImageLayer *)malloc(sizeof(struct ImageLayer));

    int hi;
    int wi;
    int chan;

    unsigned char *data = stbi_load(fileName, &wi, &hi, &chan, 4);

    struct pixel* temp = makePix();
    int x = 0;

    lay->h = hi;
    lay->w = wi;

    int j = 0;

    struct pixel **buf;
    buf = (struct pixel **)malloc(sizeof(struct pixel *)*(wi * hi)); 

    lay->imgPixelData = buf;

    int next = 0;

    while(j < (hi * wi * 4))
    {

        if(next == 0) {
            temp->red = (int)data[j];
            next = 1;
        } else if(next == 1) {
            temp->green = (int)data[j];
            next = 2;
        } else if(next == 2) {
            temp->blue = (int)data[j];
            next = 3;
        } else if(next == 3) {
            temp->alpha = (int)data[j];
            next = 0;
                 

            lay->imgPixelData[x] = temp;
            x = x + 1;
      
            temp = makePix();
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
    base = openFile("test.jpg");
    pushLayer(img, base);

    return img;

}

//Print the top layer of an ImageStack
void printImage(struct ImageStack *img) {

    int topLayer = img->top - 1;

    int imgSize = (img->imgArray[topLayer]->h)*(img->imgArray[topLayer]->w);

    int i;
    for (i = 0; i<imgSize; i++){

        printPix(img->imgArray[topLayer]->imgPixelData[i]);
    }
    printf("\n");
}

/*
//test -- open a file, and save it to a new location
int main() {
 
    struct ImageStack* img;
  
    img = open("test.jpg");

    printImage(img);

    save("new.jpg", img); 
}
*/