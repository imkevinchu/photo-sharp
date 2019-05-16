//Define the Array class

#include <vector>

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


