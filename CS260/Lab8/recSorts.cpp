#include "recSorts.hpp"


void heapifyDown(int* heapData, int size, int i) //heapify down
{
    int iteritableIndex = i; //starts at index i in the array.
    
    int leftChild = 0; //an index variable intended to keep track of the left child of the parent node at iteratble index.
    int rightChild = 0; //an index variable intended to keep track of the right child of the parent node at iteratble index.

    bool HeapConditionSatisfied = false; //A conditionaly variable for the heap condition is satisfied for the path from this original nodal index.

    while(HeapConditionSatisfied != true) //While the heap condition is not satisfied.
    {
        int original = iteritableIndex; //Set equal to iterable index for later comparison.

        leftChild = (iteritableIndex * 2) + 1; //Sets to left child of iterable index.
        rightChild = (iteritableIndex * 2) + 2; //Sets to right child of iterable index.

        if(leftChild < size && heapData[leftChild] > heapData[iteritableIndex]) //If left child is in range of array and is greater than the parent, then set to new iterable index.
        {
            iteritableIndex = leftChild;
        }
        if(rightChild < size && heapData[rightChild] > heapData[iteritableIndex]) //If right child is in range of array and is greater than the parent, then set to new iterable index.
        {
            iteritableIndex = rightChild;
        }

        if(iteritableIndex != original) //If the iterable index has changed at all, then swap the iterable index and original.
        {
            int temp = heapData[iteritableIndex];
            heapData[iteritableIndex] = heapData[original];
            heapData[original] = temp;
        }else //Otherwise break.
        {
            HeapConditionSatisfied = true;
        }
        
        
    }
}


void heapSort(int* heapData, int size)
{
    int startIndex = (size/2)-1; //Selects the last parent with children nodes in the tree.
    
    for(int i = startIndex; i >= 0; i--) //traverses back up through the tree and heapifies the node, which makes a max heap.
    {
        heapifyDown(heapData, size, i);
    }


    for (int i = size - 1; i >= 0; i--) { //reversees it.
 
        int temp = heapData[0];
        heapData[0] = heapData[i];
        heapData[i] = temp;
 
        // Heapify root element to get highest element at
        // root again
        heapifyDown(heapData, i, 0);
    }




}

struct MergeSortOperation //a struct to keep track of "merge and sort" orders.
{
    int start = 0; //start index of sub array.
    int end = 0; //end index of sub array.
};


void mergeSort(int* mergeArray, int size)
{
    if (size <= 1) { //size condition for if the mergeArray is empty.
        return;
    }

    int* tempArray = new int[size]; //a temporary array allocated once

    Deque<MergeSortOperation> Stack; //A stack for properly traversing the merge tree.
    Deque<MergeSortOperation> MergeStack; //A merge stack for loading "merge orders".

    int start, end, middle;

    Stack.addHead({ 0, size - 1 }); //Adds the entire array to the traversal stack.
    

    while (!Stack.isEmpty()) {
        MergeSortOperation Operation = Stack.removeHead(); //Pops the last sub array.
        MergeStack.addHead(Operation); //Adds the popped operation.

        start = Operation.start;
        end = Operation.end;

        if (start >= end) {
            continue;
        }

        middle = start + ((end - start) / 2);
        Stack.addHead({ start, middle }); //will travel to the left most sub tree first to the smallest element and stack the appropriate merge orders.
        Stack.addHead({ middle + 1, end });
    }

    int left,right,mid, subArrayOne, subArrayTwo, indexOfSubArrayOne, indexOfSubArrayTwo, indexOfMergedArray;
    int* leftArray;
    int* rightArray;

    while(!MergeStack.isEmpty())
    {
        MergeSortOperation Operation = MergeStack.removeHead(); //Pops operation off the merge stack.
        
        left = Operation.start; //Sets all of the index identifiers to the popped operations.
        right = Operation.end;
        mid = left + ((right-left)/2);

        subArrayOne = mid - left + 1; //Calculates the size of the first sub array.
        subArrayTwo = right - mid; //Calculates the size of the second sub array.
    
        // Create temp arrays
        leftArray = tempArray; //Calculates pointer into the temporary array at the start index.
        rightArray = (tempArray) + subArrayOne; //Calculates the index of the second sub array past the left array.
    
        // copy the data 
        for (int i = 0; i < subArrayOne; i++)
            leftArray[i] = mergeArray[left + i];
        for (int j = 0; j < subArrayTwo; j++)
            rightArray[j] = mergeArray[mid + 1 + j];
        
        
        
        indexOfSubArrayOne
            = 0, // initial index of first sub-array.
            indexOfSubArrayTwo
            = 0; // initial index of second sub-array.
        indexOfMergedArray
            = left; // initial index of merged array.
    
        // merge the temp arrays back into array
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {

            //if the item in the left sub array at the current index then put this item into the total array and then incremenet index.
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                mergeArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else { //other wise pull from the right array and increment right index.
                mergeArray[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;//And increment index into the merged array.
        }

        while (indexOfSubArrayOne < subArrayOne) { //dump the rest of the left
            mergeArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
        
        //dump the rest of the right. "stable"
        while (indexOfSubArrayTwo < subArrayTwo) {
            mergeArray[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
    }
}

int partition(int arr[], int low, int high)
{
    // chooses pivot right at the end, could use the median of three and then swap to end but that is saved for another day.
    int pivot = arr[high];
 
    //one before low, -1
    int i = (low - 1);
    //specifically iterates from this low position (-1) to the very end index
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) { 
 
            // will use the (+1) [position to swap with j if it less than the pivot]
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1]; //puts the pivot in the (-1) positon and returns the (+1) position.
    arr[i+1] = arr[high];
    arr[high]  = temp;
    return (i + 1);
}

void quickSort(int* heapArray, int size)
{
    Deque<MergeSortOperation> Stack;
    
    int start, end, middle;

    // Push the initial range to the stack
    Stack.addHead({0, size - 1});
    
    while (!Stack.isEmpty()) {

        MergeSortOperation Operation = Stack.removeHead();

        start = Operation.start;
        end = Operation.end;

        if (start < end) { //regular quick sort loop at each operation of the stack.
            int pi = partition(heapArray, start, end);
            Stack.addHead({ start, pi - 1}); //add left of partion.
            Stack.addHead({ pi + 1, end}); //add right of partioin.
        }

    }



}

std::string findNth(int* heapArray, int size, int index)
{
    Deque<MergeSortOperation> Stack;
    
    int start, end;

    // Push the initial range to the stack
    Stack.addHead({0, size - 1});

    int SubdivisionsSorted = 0;
    int CenterDistance = (((size/2)-index) < 0) ? ((size/2)-index)*-1 : ((size/2)-index);
    int NeccecarySubdivisions = ((size-CenterDistance))-2; //just calculates a distance based number of operations neccecary..

    while (!Stack.isEmpty() && SubdivisionsSorted < NeccecarySubdivisions) {

        MergeSortOperation Operation = Stack.removeHead();

        start = Operation.start;
        end = Operation.end;

        if (start < end) { //regular quick sort loop at each operation of the stack.
            int pi = partition(heapArray, start, end);

            SubdivisionsSorted++;

            Stack.addHead({ start, pi - 1}); //add left of partion.
            Stack.addHead({ pi + 1, end}); //add right of partioin.
        }

        

    }


    return std::to_string(heapArray[index]);
}

void viewArray(int* heapArray, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d, ", heapArray[i]);
    }
    printf("\n");
}