
#include <stdio.h>
#include <stdlib.h>

struct Album{

    short top;
    short size;
    struct ImageStack **images;

};

struct Album *newAlbum(){

    struct Album *a = (struct Album *)malloc(sizeof(struct Album));
    a->size = 5;
    a->top = 0;
    a->images = (struct ImageStack **)malloc(sizeof(struct ImageStack *) * a->size);


    return a;

}

void checkAndResize(struct Album *a){

    int newSize;
    int curSize = a->size;

    if (a->top == curSize -1){
        newSize = curSize * 2;    
        struct ImageStack **buf = (struct ImageStack **)malloc(sizeof(struct ImageStack *) * newSize);
        for(int i = 0; i<curSize; i++){
            buf[i] = a->images[i];
        }
        a->images = buf;
        a->size = newSize;
    }



}

void removeLast(struct Album *a){
    
    //freeImageStack(a->top-1);
    a->top -= 1;

}


void addToAlbum(struct Album *a, struct ImageStack *ims){

    checkAndResize(a);
    a->images[a->top] = ims;
    a->top++;

}


/*
int main(){

    struct Album *a = newAlbum();

    return 0;
}
*/ 