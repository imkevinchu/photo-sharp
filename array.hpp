//Define the Array class
#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

/*
template <typename T>
class arr 
{

    public:
    std::vector<T> vector;

    arr(std::string name);
    int indexArr(int index);
    void removeArr(int index);
    void setArr(int index, T object);
    int sizeArr();
    vector<T> *pointer(vector<T> vector);

};
*/ 

template <typename T>
struct arr
{
    std::vector<T> vec;
    
};

template <typename T>
arr<T>* pointerStruct(struct arr<T> &a);


#endif 