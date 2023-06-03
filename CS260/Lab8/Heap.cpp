#include "Heap.hpp"

Heap::Heap() : heapData(nullptr), size(0), capacity(4)
{
    //sets heap data to nullptr, size to 0 and capacity to 0.
    resize();
}

void Heap::addItem(const int item)
{
    if((size+1) > capacity)
    {
        resize(); //resize if the addition of one item will exceed the capacity.
    }

    heapData[size] = item; //puts item at the end of the array.
    heapifyUp(size); //heapify up the item.
    size++; //increment size.
}

void Heap::heapifyUp(int index)
{
    if(index < 0 || index > size)
    {
        return; //if at zero posiiton or index greater than size, then return.
    }

    int iteritableIndex = index;
    
    int parent = 0;
    int leftChild = 0;
    int rightChild = 0;

    bool HeapConditionSatisfied = false;

    while(HeapConditionSatisfied != true && iteritableIndex != 0) //heapify up using a bunch of if statements to check if the left and right hcild exists...
    {
        parent = iteritableIndex/2; //gets parent and left and right index.
        leftChild = (parent*2)+1;
        rightChild = (parent*2)+2;

        int parentValue = heapData[parent]; //selects parent value.

        if(leftChild <= size) //if left child exists in range.
        {
            int leftValue = heapData[leftChild]; //get left value.

            if(rightChild <= size) //if right child exists
            {
                int rightValue = heapData[rightChild]; //get right child.

                if((leftValue > parentValue) && (rightValue > parentValue)) //set heap satisief if both and greater tahn parent.
                {
                    HeapConditionSatisfied = true;
                }else
                {
                    int lessChild = (leftValue < rightValue) ? leftChild : rightChild; //else compare both and swap the lesser one.
                    heapData[parent] = heapData[lessChild];
                    heapData[lessChild] = parentValue;
                }

            }else
            {
                if(leftValue < parentValue) //else if right doens't exist just compare left and parent.
                {
                    int lessChild = leftChild;
                    heapData[parent] = heapData[lessChild];
                    heapData[lessChild] = parentValue;
                }else
                {
                    HeapConditionSatisfied = true;
                }
            }

        }else
        {
            HeapConditionSatisfied = true; //if non exist satisifed.
        }
        
        iteritableIndex = parent; //set the next iteration to the parent.
    }

}


void Heap::heapifyDown(int index)
{
    if(index < 0 || index > (size-1))
    {
        return; //if at zero posiiton or index greater than size, then return.
    }

    int iteritableIndex = index;
    
    int parent = 0; 
    int leftChild = 0;
    int rightChild = 0;


    bool HeapConditionSatisfied = false;

    while(HeapConditionSatisfied != true) //heapify down using a bunch of if statements to check if the left and right hcild exists...
    {
        
        parent = iteritableIndex; //gets parent and left and right index.
        leftChild = (parent*2)+1; 
        rightChild = (parent*2)+2;


        int parentValue = heapData[parent]; //selects parent value.

        if(leftChild < size) //if left child exists in range.
        {
            int leftValue = heapData[leftChild]; //get left value.

            if(rightChild < size) //if right child exists
            {
                int rightValue = heapData[rightChild]; //get right child.

                if(leftValue > parentValue && rightValue > parentValue) //set heap satisief if both and greater tahn parent.
                {
                    HeapConditionSatisfied = true;
                }else
                {
                    int lessChild = (leftValue < rightValue) ? leftChild : rightChild; //else compare both and swap the lesser one.
                    heapData[parent] = heapData[lessChild]; 
                    heapData[lessChild] = parentValue;
                    iteritableIndex = lessChild;
                }
                
            }else //else if right doens't exist just compare left and parent.
            {
                
                if(leftValue < parentValue)
                {
                    heapData[parent] = heapData[leftChild];
                    heapData[leftChild] = parentValue;
                    iteritableIndex = leftChild;
                }else
                {
                    HeapConditionSatisfied = true;
                }

            }
        }else
        {
            HeapConditionSatisfied = true; //elsse satisifed.
        }     
    }

}
int Heap::getItem()
{
    if(size == 0)
    {
        throw std::range_error("bad time"); //if size is empty return excetiopon

    }
    int item = heapData[0]; //gets root index.
    int lastitem = heapData[size-1]; //gets last item.

    heapData[0] = lastitem; //swaps decrements size, and then heapify down the root.
    heapData[size-1] = item;
    size--;
    heapifyDown(0);

     
    return item; //return previous root.
}
void Heap::resize()
{
    int* memBuffer = new int[(capacity+1)*2]; //resizes twice capacity.
    capacity = (capacity+1)*2;
    if((heapData != nullptr) && (size > 0))
    {
        memcpy(memBuffer, heapData, sizeof(int)*size);
        if(memBuffer != heapData)
        {
            delete[] heapData;
        }
    }

    heapData = memBuffer;
    
}

void Heap::viewHeap()
{
    if(size == 0)
    {
        return;
    }

    for(int i = 0; i < size; i++)
    {
        printf("%d, ", heapData[i]);
    }

    printf("\n");
}