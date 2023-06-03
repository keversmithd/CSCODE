#ifndef IARRAY_H
#define IARRAY_H

#include <memory.h>

template <typename T>
struct IArray
{
    private:
        T* stack;
        int m_size;
        int capacity;
    public:

        IArray(int b = 0) : stack(nullptr), m_size(0), capacity(0) 
        {
            if (b > 0)
            {
                resize(b);
            }
        }

        T& operator [](int index)
        {
            if(index > (2*capacity)-1)
            {
                resize(index+1);
            }else if (m_size+1 > capacity)
            {
                resize();
            }

            return stack[index];
        }

        void resize()
        {
            T* newBox = new T[capacity*2];

            if(stack != nullptr)
            {   
                memcpy(newBox, stack, m_size*sizeof(T));

                if(stack != newBox)
                {
                    delete[] stack;
                }
            }
            
            capacity = 2*capacity;
        }

        int set(T value, int i)
        {
            for(int e = 0; e < i; e++)
            {
                stack[e] = value;
            }
        }

        int size()
        {
            return m_size;
        }

        void resize(int n)
        {
            T* newBox = new T[n];

            if(stack != nullptr)
            {   
                memcpy(newBox, stack, m_size*sizeof(T));

                if(stack != newBox)
                {
                    delete[] stack;
                }
            }

            stack = newBox;
            
            capacity = n;
        }
};

#endif