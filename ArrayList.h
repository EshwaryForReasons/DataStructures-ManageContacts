
#include <stdio.h>

template<typename T>
class ArrayList
{
public:

    void insert(T element)
    {
        //If we do not have space to add another element
        if(sizeof(T) * num_elements < size + sizeof(T))
            resize(num_elements + 1);

        data[num_elements] = element;
        num_elements++;
    }

    void clear()
    {
        free(data);
        num_elements = 0;
    }

    void remove(T) {}

    void resize(int new_capacity)
    {
        //Allocate new array with the new capacity
        if (T* new_data = new T[new_capacity])
        {
            //Copy old data to new array
            for(int i = 0; i < num_elements; ++i)
                new_data[i] = data[i];
            
            delete[] data;
            data = new_data;
            size = new_capacity * sizeof(T);
        }
    }

    T operator[](int pos) const
    {
        return data[pos];
    }

    T* get_data() const {return data;}
    int get_num_elements() const {return num_elements;}

private:

    //Represents the data stored in this array
    T* data;

    //Number of elements in the array 
    int num_elements = 0;
    //Current size of data
    int size = 0;
};