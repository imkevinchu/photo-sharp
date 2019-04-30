#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "pixel.c"
#include <string.h>
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int save(char const *filename, int w, int h, int c, struct pixel **data){

    unsigned char *temp;
    
    temp = (unsigned char *)malloc(sizeof(int)*(w * h * c)); 

    printf("hi: %d wi: %d\n", h, w);

    int x = 0;

    printf("saving\n");
    for(int i = 0; i < w * h; i++)
    {
        temp[x++] = (unsigned char)data[i]->red;
        temp[x++] = (unsigned char)data[i]->green;
        temp[x++] = (unsigned char)data[i]->blue;
        temp[x++] = (unsigned char)data[i]->alpha;
    }

    return(stbi_write_jpg(filename, w, h, c, temp, 100));
}

struct ImageArr{
    int h;
    int w;
    struct pixel **imgPixelData;
};

struct ImageArr *newImageArr(char *fileName){
    struct ImageArr* img = (struct ImageArr *)malloc(sizeof(struct ImageArr));

    int hi;
    int wi;
    int chan;

    unsigned char *data = stbi_load(fileName, &wi, &hi, &chan, 4);

    struct pixel* temp = makePix();
    int x = 0;

    img->h = hi;
    img->w = wi;

    printf("channels: %d\n", chan);

    int j = 0;

    struct pixel **buf;
    buf = (struct pixel **)malloc(sizeof(struct pixel *)*(wi * hi)); 

    img->imgPixelData = buf;

    printf("height: %d, width: %d\n", hi, wi);

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

    printf("end of image create\n");
    stbi_image_free(data);
    return img;

}

void printImageArrayData(struct ImageArr *m) {

    printf("tryna print\n");


    int imgSize = (m->h)*(m->w);
    printf("Image size: %d\n", imgSize);


    int i;
    for (i = 0; i<imgSize; i++){
        printf("i: %d\n", i);

        printPix(m->imgPixelData[i]);
    }
    printf("\n");
}


int main() {
 
    struct ImageArr *img;
    
    img = newImageArr("test.jpg");

    save("new.jpg", img->w, img->h, 4, img->imgPixelData); 
}



