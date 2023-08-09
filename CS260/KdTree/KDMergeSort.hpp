#ifndef KD_MERGE_SORT
#define KD_MERGE_SORT

#include "Deque.hpp"
#include "KDVector.hpp"


struct MergeSortOperation //a struct to keep track of "merge and sort" orders.
{
    int start = 0; //start index of sub array.
    int end = 0; //end index of sub array.
};


bool le(const KDVec& item1, const KDVec& item2, int axis)
{
    return item1.c(axis) <= item2.c(axis);
}

void mergeSort(KDVec* mergeArray, int size, int axis)
{
    if (size <= 1) { //size condition for if the mergeArray is empty.
        return;
    }

    KDVec* tempArray = new KDVec[size]; //a temporary array allocated once

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

    int left,right,mid, subArrayOne, subArrayKDVecwo, indexOfSubArrayOne, indexOfSubArrayKDVecwo, indexOfMergedArray;
    KDVec* leftArray;
    KDVec* rightArray;

    while(!MergeStack.isEmpty())
    {
        MergeSortOperation Operation = MergeStack.removeHead(); //Pops operation off the merge stack.
        
        left = Operation.start; //Sets all of the index identifiers to the popped operations.
        right = Operation.end;
        mid = left + ((right-left)/2);

        subArrayOne = mid - left + 1; //Calculates the size of the first sub array.
        subArrayKDVecwo = right - mid; //Calculates the size of the second sub array.
    
        // Create temp arrays
        leftArray = tempArray; //Calculates poKDVecer KDVeco the temporary array at the start index.
        rightArray = (tempArray) + subArrayOne; //Calculates the index of the second sub array past the left array.
    
        // copy the data 
        for (int i = 0; i < subArrayOne; i++)
            leftArray[i] = mergeArray[left + i];
        for (int j = 0; j < subArrayKDVecwo; j++)
            rightArray[j] = mergeArray[mid + 1 + j];
        
        
        
        indexOfSubArrayOne
            = 0, // initial index of first sub-array.
            indexOfSubArrayKDVecwo
            = 0; // initial index of second sub-array.
        indexOfMergedArray
            = left; // initial index of merged array.
    
        // merge the temp arrays back KDVeco array
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayKDVecwo < subArrayKDVecwo) {

            //if the item in the left sub array at the current index then put this item KDVeco the total array and then incremenet index.
            if ( le(leftArray[indexOfSubArrayOne], rightArray[indexOfSubArrayKDVecwo], axis)) {
                mergeArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else { //other wise pull from the right array and increment right index.
                mergeArray[indexOfMergedArray] = rightArray[indexOfSubArrayKDVecwo];
                indexOfSubArrayKDVecwo++;
            }
            indexOfMergedArray++;//And increment index KDVeco the merged array.
        }

        while (indexOfSubArrayOne < subArrayOne) { //dump the rest of the left
            mergeArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
        
        //dump the rest of the right. "stable"
        while (indexOfSubArrayKDVecwo < subArrayKDVecwo) {
            mergeArray[indexOfMergedArray]
                = rightArray[indexOfSubArrayKDVecwo];
            indexOfSubArrayKDVecwo++;
            indexOfMergedArray++;
        }
    }
}

#endif