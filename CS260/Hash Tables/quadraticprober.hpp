#ifndef QUAD_PROBE_H
#define QUAD_PROBE_H

#include "hashcodes.hpp"
#include <iostream>

template<typename T>
class QuadraticProbe
{
private:
    T* hashData;
    T dummy;
    int capacity;
    int size;
public:
    QuadraticProbe(int preferredSize = 0) : hashData(nullptr), capacity(7), size(0)
    {
        if(preferredSize == 0)
        {
            resize();
        }
    }
    void addItem(const T value)
    {
            //If the appension of one element will be greater than capaicty resize the array.
        if(size+1 > capacity/2)
        {
            resize();
        }
        
        int hashIndex = hashFunc(value);

        if(hashData[hashIndex] == dummy)
        {
            hashData[hashIndex] = value;
            size++; 
        }else
        {   
            bool found = false;
            for(int i = 0; i < capacity && found == false; i++)
            {
                int t = (hashIndex + (i*i)) % capacity;
                if(hashData[t] == dummy)
                {
                    hashData[t] = value;
                    size++;
                    found = true;
                }
            }
        }
    }
    bool findItem(const T value)
    {
        //Will select hash funciton of item, if the value at that location is not the value it will keep searching until encircled completely once, then it will return false if not found.
        int hashIndex = hashFunc(value);

        if(hashData[hashIndex] == value)
        {
            return true;
        }else
        {   
            for(int i = hashIndex; i < capacity; i++)
            {
                int t = (hashIndex + (i*i)) % capacity;
                if(hashData[t] == value)
                {
                    return true;
                }
            }
        }

        return false;
    
    }
    void removeItem(const T value)
    {
            //will use the find algorithm and then set that value to unknown if it does find other wise, it will just loop around and return.
        int hashIndex = hashFunc(value);
        bool encircledOnce = false;
        bool done = false;
        bool found = true;

        if(hashData[hashIndex] == value)
        {
            hashData[hashIndex] = dummy;
            size--;
        }else
        {   
            for(int i = hashIndex; i < capacity; i++)
            {
                int t = (hashIndex + (i*i)) % capacity;
                if(hashData[t] == value)
                {
                   hashData[t] = dummy;
                   size--;
                }
            }
        }

    }
    void resize()
    {
        //will resize the list to the next prime function.
        int storage = nextPrime(capacity*1.2);
        T* memBuffer = new T[storage]; 
        capacity = storage;

        for(int i = 0; i < capacity; i++)
        {
            memBuffer[i] = dummy;
        }

        int hashIndex;
        bool found;

        //will then re insert all elements using the insertion algorithm.
        int preffSize = size;
        for(int i = 0; i < preffSize; i++)
        {
            if(hashData[i] != dummy)
            {
                hashIndex = hashFunc(hashData[i]);

                found = true;
                for(int i = hashIndex; i < capacity && found == false; i++)
                {
                    int t = (hashIndex + (i*i)) % capacity;

                    if(hashData[t] == dummy)
                    {
                        hashData[t] = hashData[i];
                        found = true;
                    }
                }

            }else
            {
                preffSize++;
            }
        }

        if(hashData != nullptr && hashData != memBuffer)
        {
            delete[] hashData;
        }
        
        hashData = memBuffer;
    }
    void showtable()
    {
        for(int i = 0; i < capacity; i++)
        {
            std::cout << hashData[i] << ", ";
            if(i % 10 == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    int hashFunc(T key)
    {
        //provided by jim bailey and team.
        int hashCode = key.hashCode();
        return guas_hash(hashCode, capacity);
    }
    ~QuadraticProbe()
    {
         //deletes the data if it exists.
        if(hashData != nullptr)
        {
            delete[] hashData;
        }
    }
};

#endif