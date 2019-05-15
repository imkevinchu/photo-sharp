#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

#include "array.hpp"
#include "pixel.h"
#include "ImageStack.h"

using namespace std;

template <typename T> 
T getItem(arr<T> *a, int index)
{
    return a->vec[index];
}

template <typename T>
int getSize(arr<T> *a)
{
    return a->vec.size();
}

template <typename T>
void setItem(arr<T> *a, T item, int index)
{
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

    size = ImageSize(img);

    printf("Size: %d\n", size);

    //struct arr 
    arr<int> Array;
    arr<struct ImageStack *>* array = newArrayImageStack();
    
    Array.vec.push_back(10);
    array->vec.push_back(img);
    cout << array->vec[0] << endl;
    size = ImageSize(array->vec[0]);

    printf("Size: %d\n", size);


    return 0;
}

/*
template <typename T>
arr<T>::arr(string name )
{
}

template <typename T>
vector<T> * arr<T>::pointer(vector<T> vector)
{
    return &vector;
}

template <typename T>
int arr<T>::indexArr(int index)
{
    return vector.at(index);
}

template <typename T>
void arr<T>::removeArr(int index)
{
    vector.erase(index);

}

template <typename T>
void arr<T>::setArr(int index, T object)
{
    vector[index] = object;
}

template <typename T>
int arr<T>::sizeArr()
{
    return vector.size();
}
*/