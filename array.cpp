#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

#include "array.hpp"

using namespace std;

template <typename T>
arr<T>* pointerStruct(struct arr<T> &a)
{
    return &a;
}

int main()
{
    /*
    struct pixel *p;
    p = setPix(100,100,100,0);
    printPix(p);

    struct ImageStack* img;
  
    img = open("test.jpg");
    int size;

    size = ImageSize(img);

    printf("Size: %d\n", size);
    */

    //struct arr 
    arr<int> Array;

    Array.vec.push_back(10);
    cout << pointerStruct(Array) << endl;

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