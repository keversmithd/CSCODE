#ifndef DEQUE_H
#define DEQUE_H

template<typename T>
struct ArrayDeque
{
private:
    T* queData;
    int head;
    int capacity;
    int numberOfElements;
public:
    void ShowArray()
    {
        for(int i = 0; i < numberOfElements; i++)
        {
            std::cout << queData[i] << ", ";
        }
        std::cout << std::endl;
    }
    ArrayDeque(int preferredSize = 0) : queData(nullptr), head(0), capacity(0), numberOfElements(0)
    {
        if(preferredSize > 0)
        {
            resize(preferredSize);
        }
    }
    T get(int i)
    {
        return queData[(head+i)%capacity];
    }
    void add(int i, T x)
    {
        if(i < 0 || i > numberOfElements)
        {
            return;
        }

        if (numberOfElements+1 > capacity) resize();
        if (i < numberOfElements/2)
        {
            head = (head == 0) ? capacity-1 : head-1;
            for(int k = 0; k <= i-1; k++)
            {
                queData[(head+k)%capacity] = queData[(head+k+1)%capacity];
            }

        }else
        {
            for(int k = numberOfElements; k > i; k--)
            {
                queData[(head+k)%capacity] = queData[(head+k-1)%capacity];
            }
        }
        queData[(head+i)%capacity] = x;
        numberOfElements++;
    }

    T remove(int i )
    {
        T x = queData[(head+i)%capacity];
        if (i < numberOfElements/2)
        {
            for (int k = i; k > 0; k--)
            {
                queData[(head+k)%capacity]= queData[(head+k-1)%capacity];
                
            }
            head = (head+1) % capacity;
        }else{
            for(int k = i; k < numberOfElements-1; k++)
            {
                queData[(head+k)%capacity] = queData[(head+k+1)%capacity];
            }
            
        }

        numberOfElements--;
        if(3*numberOfElements < capacity) resize();
        return x;
    }

    void resize(int preferredSize = 0)
    {
        T* memData = (T*)malloc(std::max((capacity*2)+preferredSize, 1)*sizeof(T));
        for(int i = 0; i < numberOfElements; i++)
        {
            memData[i] = queData[(head+i)%numberOfElements];
        }
        if(queData != nullptr && memData != queData)
        {
            free(queData);
        }
        queData = memData;
        capacity = std::max((capacity*2)+preferredSize, 1);
    }

};

#endif