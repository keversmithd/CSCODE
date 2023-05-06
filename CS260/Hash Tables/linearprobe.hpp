#ifndef STRING_HASH_H
#define STRING_HASH_H


#include <iostream>
#include "hashcodes.hpp"



template<typename T>
class LinearProbe
{
private:
    T* hashData;
    T dummy;
    int capacity;
    int size;
public:
    LinearProbe(int preferredSize = 0) : hashData(nullptr), capacity(7), size(0)
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
        bool encircledOnce = false;
        bool done = false;
        bool found = true;

        //If the hashed index location is marked unknown then search linearly along the array, and even looping the array until an avaiable location is found.
        while(hashData[hashIndex] != dummy && done == false)
        {
            

            if(hashIndex == capacity-1)
            {
                if(encircledOnce == false)
                {
                    hashIndex = 0;
                    encircledOnce = true;
                }else
                {
                    done = true;
                    found = false;
                }
            }

            if(done == false)
            {
                hashIndex++;
            }
            
        }

        if(found == true)
        {
            hashData[hashIndex] = value;
            size++;
        }
    }
    bool findItem(const T value)
    {
        //Will select hash funciton of item, if the value at that location is not the value it will keep searching until encircled completely once, then it will return false if not found.
        int hashIndex = hashFunc(value);
        bool encircledOnce = false;
        bool done = false;
        bool found = true;

        while(hashData[hashIndex] != value && done == false)
        {
            if(hashIndex == capacity-1)
            {
                if(encircledOnce == false)
                {
                    hashIndex = 0;
                    encircledOnce = true;
                }else
                {
                    done = true;
                    found = false;
                }
            }

            if(done == false)
            {
                hashIndex++;
            }
            
        }

        return found;
    }
    void removeItem(const T value)
    {
            //will use the find algorithm and then set that value to unknown if it does find other wise, it will just loop around and return.
        int hashIndex = hashFunc(value);
        bool encircledOnce = false;
        bool done = false;
        bool found = true;

        while(hashData[hashIndex] != value && done == false)
        {
            if(hashIndex == capacity-1)
            {
                if(encircledOnce == false)
                {
                    hashIndex = 0;
                    encircledOnce = true;
                }else
                {
                    done = true;
                    found = false;
                }
            }

            if(done == false)
            {
                hashIndex++;
            }
            
        }

        if(found == true)
        {
            hashData[hashIndex] = dummy;
            size--;
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

        int hashIndex, encircledOnce, done, found;

        //will then re insert all elements using the insertion algorithm.
        int preffSize = size;
        for(int i = 0; i < preffSize; i++)
        {
            //printf("value: %s\n", hashData[i].c_str());
            if(hashData[i] != dummy)
            {
                hashIndex = hashFunc(hashData[i]);
                encircledOnce = false;
                done = false;
                found = true;

                while(memBuffer[hashIndex] != dummy && done == false)
                {
                    if(hashIndex == capacity-1)
                    {
                        if(encircledOnce == false)
                        {
                            hashIndex = 0;
                            encircledOnce = true;
                        }else
                        {
                            done = true;
                            found = false;
                        }
                    }

                    if(done == false)
                    {
                        hashIndex++;
                    }
                    
                }

                if(found == true)
                {
                    memBuffer[hashIndex] = hashData[i];
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

    void showthere()
    {
        int ps = 0;
        for(int i = 0; i < capacity; i++)
        {
            if(hashData[i] != dummy)
            {
                //std::cout << hashData[i] << ", ";
                if((ps+1) % 10 == 0)
                {
                    //std::cout << std::endl;
                }
                ps++;
            }
        }
        std::cout << ps;
        std::cout << std::endl;
    }

    

    int hashFunc(T key)
    {
        //provided by jim bailey and team.
        int hashCode = key.hashCode();
        return guas_hash(hashCode, capacity);
    }
    ~LinearProbe()
    {
         //deletes the data if it exists.
        if(hashData != nullptr)
        {
            delete[] hashData;
        }
    }
};

#endif