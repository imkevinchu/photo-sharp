#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "array.hpp"

using namespace std;

template <typename T>
arr<T>::arr(string name)
{
    array = vector<T> name;
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


