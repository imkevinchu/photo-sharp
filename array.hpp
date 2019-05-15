//Define the Array class
#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

template <typename T>
class arr 
{

    public:

    std::vector<T> vector;

    int indexArr(int index);
    void removeArr(int index);
    void setArr(int index, T object);
    int sizeArr();

};

#endif 