//Define the Array class
#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
class arr 
{
    arr(std::string name);
        
    public:
    vector<T> array;

    int indexArr(int index);
    void removeArr(int index);
    void setArr(int index, T object);
    int sizeArr();

};

#endif 