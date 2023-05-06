
#ifndef DEQU_H
#define DEQU_H


#include <string>
#include <cmath>
#include <stdexcept>

template<typename T>
struct Deque {
public:
    Deque(int preferredSize = 0) : head(0), tail(0), capacity(0), m_size(0), queData(nullptr)
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
        if (m_size == capacity) {
            resize(capacity * 2); // Double the capacity if deque is full
        }
        tail = (tail + 1) % capacity; // Move tail circularly
        queData[tail] = element;      // Add element to tail
        m_size++;
    }
    void addHead(T element)
    {
        if (m_size == capacity) {
            resize(capacity * 2); // Double the capacity if deque is full
        }
        head = (head - 1 + capacity) % capacity; // Move head circularly
        queData[head] = element;                 // Add element to head
        m_size++;
    }
    T removeTail()
    {
        if (m_size == 0) {
            throw std::out_of_range("removed tail with no values");
        }
        T removedElement = queData[tail]; // Get element from tail
        tail = (tail - 1 + capacity) % capacity; // Move tail circularly
        m_size--;
        if (m_size < capacity / 4) {
            resize(capacity / 2); // Shrink the capacity if deque is less than 25% full
        }
        return removedElement;
    }
    bool isEmpty()
    {
        return (m_size <= 0);
    }
    std::string dumpArray()
    {
        std::string gValue; //creates a string.
        for(int i = 0; i < capacity; i++)
        {
            gValue += std::to_string(queData[i]) + ", "; //for each value in the deque from zero to capacity, append the value in string form.
        }
        return gValue;
    }
    std::string listQueue()
    {
         std::string gValue; //create string.
        for(int i = 0; i < capacity; i++) //for each element in the array.
        {
            int modDex = (head+i) % capacity; //calculate modulated index.
            gValue += std::to_string(queData[modDex]) + ", "; //append value to the string.

        }
        return gValue;
    }
    T removeHead()
    {
        if (m_size == 0) {
            throw std::out_of_range("removed head with no values");
        }
        T removedElement = queData[head]; // Get element from head
        head = (head + 1) % capacity;      // Move head circularly
        m_size--;
        if (m_size < capacity / 4) {
            resize(capacity / 2); // Shrink the capacity if deque is less than 25% full
        }
        return removedElement;
    }
    void resize(int newSize)
    {
        T *newData = new T[newSize]; // Create a new dynamic array with new size
        for (int i = 0; i < m_size; i++) {
            newData[i] = queData[(head + i) % capacity]; // Copy elements from old array to new array
        }
        head = 0;       // Reset head index
        tail = m_size - 1; // Reset tail index
        capacity = newSize; // Update capacity
        if(queData != nullptr)
        {
            delete[] queData;   // Delete old array
        }
        
        queData = newData;  // Point queData to new array
    }

    int size()
    {
        return m_size;
    }

    int& operator [](const int index)
    {
        if(index < 0 || index >= capacity-1)
        {
            -1;
        }
        return queData[(head + index) % capacity];
    }

private:
    T *queData; // Pointer to dynamic array holding deque elements
    int head;     // Index of the head element
    int tail;     // Index of the tail element
    int capacity; // Capacity of the deque
    int m_size;     // Number of elements in the deque
};

#endif