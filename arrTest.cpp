#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>


#include "pixel.h"
#include "ImageStack.h"
#include "array.cpp"
using namespace std;


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
