#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "array.hpp"
#include "pixel.h"

using namespace std;


int main()
{
    struct pixel *p;
    p = setPix(100,100,100,0);
    printPix(p);

    arr<int> Array;

    Array.vector.push_back(10);
    Array.setArr(0, 5);
    cout << Array.indexArr(0) << endl;


    return 0;
}
