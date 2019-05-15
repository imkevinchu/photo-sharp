//Define the Array class

template <typename T, typename name>
class arr 
{
    public:

    vector<T> name;

    int indexArr(int index);
    void removeArr(int index);
    void setArr(int index, T object);
    int sizeArr();

};