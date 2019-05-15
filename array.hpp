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
T getItem(arr<T> *a, int index);

template <typename T>
int getSize(arr<T> *a);

template <typename T>
void setItem(arr<T> *a, T item, int index);

struct arr<int> *newArrayInt();
struct arr<float> *newArrayFloat();
struct arr<bool> *newArrayBool();
struct arr<std::string> *newArrayString();
struct arr<struct pixel* > *newArrayPixel();
struct arr<struct ImageGradient *> *newArrayGradient();
struct arr<struct ImageStack *> *newArrayImageStack();
struct arr<struct Album*> *newArrayAlbum();


#endif 