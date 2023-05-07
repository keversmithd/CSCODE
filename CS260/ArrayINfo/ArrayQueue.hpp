#ifndef ARR_QUEUE
#define ARR_QUEUE

template<typename T>
struct ArrayQueue
{
private:
    T* queueData;
    int head;
    int numberOfElements;
    int capacity;
public:
    ArrayQueue(int prefferedSize = 0) : queueData(nullptr), head(0), numberOfElements(0), capacity(0)
    {

    }
    bool add(T x)
    {
        if (numberOfElements+1 > capacity)
        {
            resize();
        }
        queueData[(head+numberOfElements) % capacity] = x;
        numberOfElements++;
        return true;
    }   
    T remove()
    {
        if(numberOfElements == 0){return T();}
        int removal = queueData[head];
        head = (head+1) % capacity;
        numberOfElements--;
        return removal;
    }

    void resize(int preferredSize = 0)
    {
        T* memoryData = (T*)malloc(std::max((capacity*2) + preferredSize, 1)*sizeof(T));
        for(int i = 0; i < numberOfElements; i++)
        {
            memoryData[i] = queueData[(head+i)%numberOfElements];
        }
        if(queueData != nullptr && queueData != memoryData)
        {
            free(queueData);
        }
        queueData = memoryData;
        capacity = std::max((capacity*2) + preferredSize, 1);
        head = 0;
    }
    ~ArrayQueue()
    {

    }
};

#endif