#include <stdio.h>
#include <stdlib.h>
#include "array2.h"


struct array *newArrayString() {
    printf("here i am\n");
    struct array *arr = (struct array *)malloc(sizeof(struct array *));

    char** buff;
    buff = (char **)malloc(sizeof(char *)*(20));

    arr->vals = buff;

    arr->size = 20;

    int i;
    for(i = 0; i < 20; i++)
    {
        arr->vals[i] = 0;
    }

    return arr;
}

char *getVal(struct array *a, int index) {
    printf("here\n");
    return(a->vals[index]);
}

void setVal(struct array *a, int index, char *newVal) {
    printf("%s\n", newVal);

    if(a->size >= index) {
        resize(a);
    }
    a->vals[index] = newVal;
}

void resize(struct array *a) {
    char** buff;
    buff = (char **)malloc(sizeof(char *)*((a->size) * 2));

    int i;
    for(i = 0; i < a->size; i++) {
        buff[i] = a->vals[i];
    }

    char **temp = a->vals;
    a->vals = buff;
    a->size = (a->size) * 2;
 
    int j;
    for(j = (a->size)/2; j < (a->size); j++)
    {
        a->vals[j] = 0;
    }
 


    free(temp);
}

/*
int main() {
    struct array *a = newArrayString();
  
    setVal(a, 1, "a");
    int i;
    for(i = 1; i <21; i++)
    {
        setVal(a, i, "a");
    }
}
*/
