#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

#include "array.hpp"
#include "pixel.h"
#include "ImageStack.h"
#include "psharplib.h"

using namespace std;

template <typename T> 
T getItem(arr<T> *a, int index)
{
    return a->vec.at(index);
}

template <typename T>
int getSize(arr<T> *a)
{
    return a->vec.size();
}

template <typename T>
void setItem(arr<T> *a, T item, int index)
{
    if (index == 0 && getSize(a) == 0)
    {
        a->vec.push_back(item);
    }
    else if (getSize(a) < index)
    {
        a->vec.resize(index+1);
        a->vec[index] = item;
    }
    else
        a->vec[index] = item;
}

struct arr<int> *newArrayInt()
{
    return new arr<int>;
}

struct arr<float> *newArrayFloat()
{
    return new arr<float>;
}

struct arr<bool> *newArrayBool()
{
    return new arr<bool>;
}

struct arr<std::string> *newArrayString()
{
    return new arr<std::string>;
}

struct arr<struct pixel* > *newArrayPixel()
{
    return new arr<struct pixel *>;
}
 
struct arr<struct ImageGradient *> *newArrayGradient()
{
    return new arr<struct ImageGradient *>;
}

struct arr<struct ImageStack *> *newArrayImageStack()
{
    return new arr<struct ImageStack *>;
}

struct arr<struct Album*> *newArrayAlbum()
{
    return new arr<struct Album *>;
}


int main()
{
    struct pixel * p;
    p = setPix(100,100,100,0);
    printPix(p);

    struct ImageStack* img;
  
    img = open("test.jpg");
    int size;

    //struct arr 
    arr<int> * Array = newArrayInt();
    arr<struct ImageStack *>* array = newArrayImageStack();
    
    
    //array->vec.push_back(img);
    //cout << array->vec[0] << endl;
    //size = ImageSize(array->vec[0]);

    //printf("Size: %d\n", size);

    cout << "arrayBefore" << getSize(array) << endl;
    
    setItem(array, img, 0);
    //Array->vec.resize(5);
    //setItem(Array, img, 3);
    cout << "arrayAfter" << getSize(array) << endl;

    cout << getItem(array, 0) << endl;

    return 0;
}