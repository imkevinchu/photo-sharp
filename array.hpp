//Define the Array class
#include <stdio.h>
#include <stdlib.h>
#include <vector>

template <typename T>
struct arr
{
    std::vector<T> array
};

// constructors

struct arr *makeArr();

int indexArr(struct arr *array);
int sizeArr(struct arr *array) ;
int setArr (struct arr *array);