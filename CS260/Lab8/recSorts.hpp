#ifndef REC_SORT_H
#define REC_SORT_H
#include <stdio.h>
#include <string>
#include "Deque.hpp"
void heapSort(int* heapArray, int size); //Heap sort implementation 
void mergeSort(int* heapArray, int size); //mergeSortImplementation
void viewArray(int* heapArray, int size); //simple array viewer helper
void merge(int array[], int const left, int const mid, int const right); //a merge subroutine.
void quickSort(int* heapArray, int size); //quick sort implementation.
std::string findNth(int* heapArray, int size, int index); //partial sorts the array enough to find the nth number in correct order.

#endif