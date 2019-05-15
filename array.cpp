#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "array.hpp"

using namespace std;

template <typename T, typename name>
class arr 
{
    public:

    vector<T> name;

    int indexArr(int index)
    {
        return name.at(index);
    }

    void removeArr(int index)
    {
        name.erase(index);

    }

    void setArr(int index, T object)
    {
        name[index] = object;
    }

    int sizeArr()
    {
        return name.size();
    }


};