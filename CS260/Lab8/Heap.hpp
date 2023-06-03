#ifndef C_HEAP_H
#define C_HEAP_H
#include <memory>
#include <stdexcept>
#include <stdio.h>

struct Heap //creates a heap structures implementing an array, and keeping track of the size and capacity.
{
private:
    int* heapData;
    int size;
    int capacity;
public:
    Heap(); //constructor
    void addItem(const int item); //add item to the heap
    void heapifyUp(int index); //heapify up.
    void heapifyDown(int index); //heapify down.
    int getItem(); //gets the highest priority item.
    void resize(); //resizes the array.
    void viewHeap(); //views the heap as an array.
};

#endif