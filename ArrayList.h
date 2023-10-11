
#pragma once

#include <stdio.h>

template<typename T>
class ArrayList
{
public:

    void insert(T element);
    void clear();
    void remove(int position);
    void resize(int new_capacity);
    void swap(T& a, T& b);

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

template<typename T>
void ArrayList<T>::insert(T element)
{
    //If we do not have space to add another element
    if(sizeof(T) * num_elements < size + sizeof(T))
        resize(num_elements + 1);

    data[num_elements] = element;
    num_elements++;
}

template<typename T>
void ArrayList<T>::clear()
{
    //Allocate new array with 0 capacity
    if (T* new_data = new T[0])
    {            
        delete[] data;
        data = new_data;
        size = 0;
        num_elements = 0;
    }
}

template<typename T>
void ArrayList<T>::remove(int position)
{
    //Make sure there is data at that position
    if(position < num_elements)
    {
        //Construct two arrays, one for all data before position and one for all data after position. Then join them into one array and update data
        if (T* new_data = new T[num_elements - 1])
        {
            //Copy old data to new arrays
            for(int i = 0; i < position; ++i)
                new_data[i] = data[i];
            
            for(int i = position + 1; i < num_elements; ++i)
                new_data[i - 1] = data[i];
            
            delete[] data;
            data = new_data;
            size = (num_elements--) * sizeof(T);
        }
    }
}

template<typename T>
void ArrayList<T>::resize(int new_capacity)
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

template<typename T>
void ArrayList<T>::swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}