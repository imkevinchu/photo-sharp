#include <stdio.h>
#include "pixel.c"

struct ImageArr{
    int h;
    int w;
    struct pixel *imgPixelData;
};

struct ImageArr *newImageArr(int height, int width, struct pixel *pixelData){
    struct ImageArr* img = malloc( sizeof(struct ImageArr) + (height*width*sizeof(int)));
    img -> h = height;
    img -> w = width;
    img -> imgPixelData = pixelData;

    return img;

}

void printImageArrayData(struct ImageArr *m) {

    int imgSize = m->h*m->w;
    for (int i = 0; i<imgSize; i++){
        if(i%m->w==0)printf("\n");
        printPix(m->imgPixelData);
    }
    printf("\n");
}



/*
int main(){

    int h = 10;
    int w = 10;
    struct pixel* tmp;
    for(int i=0; i<100; i++){

        struct pixel *p = Pixel(1,2,3);
        tmp = p;
        tmp++;

    }
    struct ImageArr* m = newImageArr(h, w, tmp); 
    printImageArrayData(m);

    return 0;

}
*/



