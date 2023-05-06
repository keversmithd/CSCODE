#ifndef PQUE_ARR_H
#define PQUE_ARR_H

#include <memory>

template<typename T>
class HeapArray
{
    private:
        T* heap;
        int nodes;
        int capacity;
        bool heapReady;
    public:
        HeapArray() : heap(nullptr), nodes(0), capacity(0), heapReady(false)
        {

        }

        void push(T element)
        {
            if(nodes+1 > capacity)
            {
                resize(std::max(capacity*2,1));
            }
            heap[nodes] = element;
            nodes++;
            heapReady = false;

        }
        void heapify(int i)
        {
            int currentNode = i;

            int largest = i
            , left = 0, right = 0;

            bool chainEnd = false;
            while(chainEnd == false)
            {
                left = 2*currentNode+1;
                right = 2*currentNode+2;

                if(left < (nodes) && heap[left] > heap[largest])
                {
                    largest = left;
                }

                if(right < (nodes) && heap[right] > heap[largest])
                {
                    largest = right;
                }

                if(largest != currentNode)
                {
                    T temp = heap[largest];
                    heap[largest] = heap[currentNode];
                    heap[currentNode] = temp;
                    currentNode = largest;
                }else
                {
                    chainEnd = true;
                }

            }
        }
        void heapup()
        {
            for(int i = (nodes/2)-1; i >= 0; i--)
            {
                heapify(i);
            }
            heapReady = true;
        }

        T extractMax()
        {
            if(heapReady == false){heapup();}

            heapify(0);
            T max = heap[0];
            T temp = heap[nodes-1];
            heap[nodes-1] = heap[0];
            heap[0] = temp;
            nodes--;
            return max;
        }

        void readHeap()
        {
            for(int i = 0; i < nodes; i++)
            {
                printf("%d, ", heap[i]);
                
            }

            printf("\n");
        }
        

        void resize(int newCapacity)
        {
            if(newCapacity <= 0)
            {
                return;
            }
            int memoryDelta = (newCapacity < capacity) ? newCapacity : nodes*sizeof(T);
            void* memHeap = malloc(newCapacity * sizeof(T));
            memcpy(memHeap, heap, memoryDelta);
            if(heap != nullptr && heap != memHeap)
            {
                free(heap);
            }
            heap = (T*)memHeap;
            capacity = newCapacity;
        }

        ~HeapArray()
        {
            if(heap != nullptr)
            {
                free(heap);
            }
        }
};

template<typename T>
class PriQue
{
    public:
    PriQue() : top(0), elements(0), capacity(0), theArray(nullptr)
    {

    }
    
    T removeHigh()
    {
        if(top == -1)
        {
            return T();
        }
        top -= 1;
        return theArray[top];
    }
    void addItem(int value)
    {
        if(elements+1 > capacity)
        {
            resize(std::max(capacity*2,1));
        }

        int index = top-1;
        while(theArray[index] > value && index >= 0)
        {
            theArray[index+1] = theArray[index];
            index--;
        }
        theArray[index+1] = value;
        top++;
        elements++;
    }
    void resize(int newCapacity)
    {
        if(newCapacity <= 0)
        {
            return;
        }
        int memoryDelta = (newCapacity < capacity) ? newCapacity : elements*sizeof(T);
        void* memHeap = malloc(newCapacity * sizeof(T));
        memcpy(memHeap, theArray, memoryDelta);
        if(theArray != nullptr && theArray != memHeap)
        {
            free(theArray);
        }
        theArray = (T*)memHeap;
        capacity = newCapacity;
    }
    ~PriQue(){}
    private:
    T* theArray;
    int capacity;
    int elements;
    int top;

};

#endif