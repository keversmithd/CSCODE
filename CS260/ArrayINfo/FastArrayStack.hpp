#ifndef FAST_ARRAY_H
#define FAST_ARRAY_h

#include <memory>

template<typename T>
struct FastArrayStack
{
private:
    T* stackData;
    int numberOfElements;
    int capacity;
public:
    void ShowArray()
    {
        for(int i = 0; i < numberOfElements; i++)
        {
            printf("%d ,", stackData[i]);
        }
        printf("\n");
    }
    FastArrayStack(int NumberOfElements = 0) : stackData(nullptr), numberOfElements(0), capacity(0)
    {
        if(NumberOfElements != 0)
        {
            resize(NumberOfElements);
        }
    }
    int size()
    {
        return numberOfElements;
    }
    T get(int i )
    {
        if(i < 0 || i > (numberOfElements-1))
        {
            return T();
        }
        return stackData[i];
    }
    T set(int i, T x)
    {
        if(i < 0 || i > (numberOfElements-1))
        {
            return T();
        }
        T intermediate = stackData[i];
        stackData[i] = x;
        return intermediate;
    }
    void add(int i, T x)
    {
        if(i < 0 || i > (numberOfElements))
        {
            return;
        }
        if(numberOfElements+1 > capacity)
        {
            resize();
        }
        memcpy(stackData+i+1, stackData+i, (numberOfElements-i)*sizeof(T));
        stackData[i] = x;
        numberOfElements++;
        ShowArray();
        
    }
    T remove(int i )
    {
        if(i < 0 || i > (numberOfElements-1))
        {
            return T();
        }
        T intermediate = stackData[i];
        memcpy(stackData+i, stackData+i+1, (numberOfElements-i-1)*sizeof(T));
 
        ShowArray();
        numberOfElements--;
        return intermediate;
    }
    void resize(int ResizeQuantity = 0)
    {
        T* MemoryBuffer = (T*)malloc(std::max((capacity*2)+ResizeQuantity, 1) * sizeof(T));
        memcpy(MemoryBuffer, stackData, numberOfElements*sizeof(T));
        if(stackData != nullptr && (stackData != MemoryBuffer))
        {
            free(stackData);
        }
        stackData = MemoryBuffer;
        capacity = std::max((capacity*2)+ResizeQuantity, 1);
        
    }

};

#endif

