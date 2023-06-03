#include "PriorityQ.hpp"

PriorityQ::PriorityQ() : innerHeap()
{   
    //constructs inner heap
}
void PriorityQ::addItem(const int item)
{
    innerHeap.addItem(item); //calls the add itme function of the innerHeap.
}
int PriorityQ::getItem()
{
    return innerHeap.getItem(); //returns getItem of the inner heap.
}