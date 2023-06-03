#ifndef PRIOR_QUE_H
#define PRIOR_QUE_H
#include "Heap.hpp"
struct PriorityQ //implements heap
{
private:
    Heap innerHeap;
public:
    PriorityQ(); //constructor.
    void addItem(const int item); //add item.
    int getItem(); //get item.
};

#endif