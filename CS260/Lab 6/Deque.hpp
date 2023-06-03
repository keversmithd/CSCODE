#ifndef DEQU_H
#define DEQU_h


#include <cmath>
#include <stdexcept>

template<typename T>
class Deque {
public:
    Deque(int preferredSize = 0) : queData(nullptr), head(0), tail(0), capacity(0), size(0)
    {
        if(preferredSize == 0) //resizes if preferred size is zero for this deque.
        {
            resize(20);
        }
        else //other wise resize with the preferred size.
        {
            resize(preferredSize);
        }
    }
    ~Deque()
    {

        if(queData != nullptr)
        {
            delete[] queData;
        }

    }
    void addTail(T element)
    {

        if (size == capacity) {
            resize(capacity * 2); // Double the capacity if deque is full
        }
        tail = (tail + 1) % capacity; // Move tail circularly
        queData[tail] = element;      // Add element to tail
        size++;

    }
    
    void add(int i, T element)
    {

        if(i < 0 || i > size)
        {
            return;
        }
        if(size+1 > capacity)
        {
            resize(capacity * 2);
        }
        if (i < size/2)
        {
            for (int k = 0; k<= i-1; k++)
            {
                queData[(head+k)%capacity] = queData[(head+k+1)%capacity];
            }
        }else
        {
            for (int k = size; k > i; k--)
            {
                queData[(head+k)%capacity] = queData[(head+k-1)%capacity];
            }
            
        }
        queData[(head+i)%capacity] = element;
        size++;
    }
    void addHead(T element)
    {
        if (size == capacity) {
            resize(capacity * 2); // Double the capacity if deque is full
        }
        head = (head - 1 + capacity) % capacity; // Move head circularly
        queData[head] = element;                 // Add element to head
        size++;
    }
    T removeTail()
    {
        if (size == 0) {
            throw std::out_of_range("removed tail with no values");
        }
        T removedElement = queData[tail]; // Get element from tail
        tail = (tail - 1 + capacity) % capacity; // Move tail circularly
        size--;
        if (size < capacity / 4) {
            resize(capacity / 2); // Shrink the capacity if deque is less than 25% full
        }
        return removedElement;
    }

    T getTail()
    {
        if (size == 0) {
            throw std::out_of_range("removed tail with no values");
        }
        return queData[tail];
    }

    T getHead()
    {
        if (size == 0) {
            throw std::out_of_range("removed tail with no values");
        }
        return queData[head];
    }
    bool isEmpty()
    {
        return (size <= 0); //returns whether the capacity is zero or not.
    }

    T removeHead()
    {
        if (size == 0) {
            throw std::out_of_range("removed head with no values");
        }
        T removedElement = queData[head]; // Get element from head
        head = (head + 1) % capacity;      // Move head circularly
        size--;
        if (size < capacity / 4) {
            resize(capacity / 2); // Shrink the capacity if deque is less than 25% full
        }
        return removedElement;
    }
    void resize(int newSize)
    {
        T *newData = new T[newSize]; // Create a new dynamic array with new size
        for (int i = 0; i < size; i++) {
            newData[i] = queData[(head + i) % capacity]; // Copy elements from old array to new array
        }
        head = 0;       // Reset head index
        tail = size - 1; // Reset tail index
        capacity = newSize; // Update capacity
        if(queData != nullptr)
        {
            delete[] queData;   // Delete old array
        }
        
        queData = newData;  // Point queData to new array
    }

    void clear()
    {
        size = 0;
        head = 0;
        tail = size-1;
    }

private:
    T *queData; // Pointer to dynamic array holding deque elements
    int head;     // Index of the head element
    int tail;     // Index of the tail element
    int capacity; // Capacity of the deque
    int size;     // Number of elements in the deque
};

#endif