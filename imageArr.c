#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "pixel.c"
#include <string.h>
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct ImageArr{
    int h;
    int w;
    struct pixel **imgPixelData;
};

int save(char const *filename, struct ImageArr *img){

    struct pixel **data = img->imgPixelData;
    unsigned char *temp;

    int hi = img->h;
    int wi = img->w;

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

struct ImageArr *open(char *fileName){
    struct ImageArr* img = (struct ImageArr *)malloc(sizeof(struct ImageArr));

    int hi;
    int wi;
    int chan;

    unsigned char *data = stbi_load(fileName, &wi, &hi, &chan, 4);

    struct pixel* temp = makePix();
    int x = 0;

    img->h = hi;
    img->w = wi;

    int j = 0;

    struct pixel **buf;
    buf = (struct pixel **)malloc(sizeof(struct pixel *)*(wi * hi)); 

    img->imgPixelData = buf;

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
                 

            img->imgPixelData[x] = temp;
            x = x + 1;
      
            temp = makePix();
        }

        j++;
    }

    stbi_image_free(data);
    return img;

}

void printImageArr(struct ImageArr *m) {

    int imgSize = (m->h)*(m->w);

    int i;
    for (i = 0; i<imgSize; i++){

        printPix(m->imgPixelData[i]);
    }
    printf("\n");
}

/*
int main() {
 
    struct ImageArr *img;
    
    img = open("test.jpg");
    printImageArr(img);

    save("new.jpg", img); 
}
*/

