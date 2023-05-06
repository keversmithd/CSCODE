#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H


template<typename T>
struct doubleprobe
{
private:
    T* hashData;
    T dummy;
    int capacity;
    int PRIME;
    int size;
public:
    doubleprobe(T unknown) : hashData(nullptr), capacity(7), size(0), dummy(unknown)
    {
        resize();
    }
    void addItem(const T value)
    {

        if(size+1 > capacity/2)
        {
            resize();
        }
        
        int hashIndex = hash1(value), offset = hash2(value);

        int iters = 0;
        while(hashData[hashIndex] != dummy && (iters*offset) < size)
        {
            hashIndex = (hashIndex+offset)%capacity;
            iters++;
        }

        hashData[hashIndex] = value;
        size++;
    }
    bool findItem(const T value)
    {
        //Will select hash funciton of item, if the value at that location is not the value it will keep searching until encircled completely once, then it will return false if not found.

        int hashIndex = hash1(value), offset = hash2(value);

        int iters = 0;
        while(hashData[hashIndex] != value && (iters*offset) < size)
        {
            hashIndex = (hashIndex+offset)%capacity;
            if(hashData[hashIndex] == value)
            {
                return true;
            }
            iters++;
        }

        return false;
    
    }
    int hash1(T value)
    {
        return (value.hashCode())%capacity;
    }
    int hash2(T value)
    {
        return PRIME - (value.hashCode()%PRIME);
    }
    void resize()
    {
        //will resize the list to the next prime function.
        int storage = nextPrime(capacity*1.2);
        T* memBuffer = new T[storage]; 
        capacity = storage;
        PRIME = previousPrime(capacity);
        for(int i = 0; i < capacity; i++)
        {
            memBuffer[i] = dummy;
        }

        int hashIndex;
        int offset;
        bool found;

        //will then re insert all elements using the insertion algorithm.
        int preffSize = size;
        for(int i = 0; i < preffSize; i++)
        {
            if(hashData[i] != dummy)
            {
                hashIndex = hash1(hashData[i]), offset = hash2(hashData[i]);

                while(memBuffer[hashIndex] != dummy)
                {
                    hashIndex = (hashIndex+offset) % capacity;
                }
                
                memBuffer[hashIndex] = hashData[i];
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

    void removeItem(const T value)
    {
            //will use the find algorithm and then set that value to unknown if it does find other wise, it will just loop around and return.
        int hashIndex = hash1(value), offset = hash2(value);
        if(hashData[hashIndex] == value)
        {
            hashData[hashIndex] = dummy;
            size--;
        }else
        {

        

        int iters = 0;
        while(hashData[hashIndex] != value && (iters*offset) < size)
        {
            hashIndex = (hashIndex+offset)%capacity;
            if(hashData[hashIndex] == value)
            {
                hashData[hashIndex] = dummy;
                size--;
                return;
            }
            iters++;
        }

        }
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

    ~doubleprobe()
    {
        if(hashData != nullptr)
        {
            delete[] hashData;
        }
    }

};


#endif