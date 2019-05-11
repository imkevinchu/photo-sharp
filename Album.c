#include <stdio.h>
#include <stdlib.h>
#include "ImageStack.h"
#include "Album.h"

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

//Remove the last element from Album a
void removeLast(struct Album *a){
    
    if(a->top > 0){
        freeImageStack(a->images[a->top-1]);
        a->top -= 1;
    }

}

//Free all memory associated with Album a
void freeAlbum(struct Album *a){

    for(int i = 0; i< a->top; i++){
        removeLast(a);
    }
    free(a);
}

void addToAlbum(struct Album *a, struct ImageStack *ims){

    checkAndResize(a);
    a->images[a->top] = ims;
    a->top++;

}

int AlbumSize(struct Album *a){

    return a->size;

}

struct ImageStack *GetImage(struct Album *a, int idx){

    return a->images[idx];

}


/*
int main(){

    struct Album *a = newAlbum();

    return 0;
}
*/ 
