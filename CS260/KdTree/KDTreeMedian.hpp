#ifndef KD_TREE_MEDIAN
#define KD_TREE_MEDIAN

#include "KDVector.hpp"
#include "KDMergeSort.hpp"
struct KDVecPartition
{
    KDVec* data; //change this all to store the dimensionality of the vectors
    int length;
};

struct KDMedianRecovery
{
    KDVec Median;
    KDVecPartition left;
    KDVecPartition right;
};


KDMedianRecovery recoverMedian(KDVecPartition partition, int axis)
{
    mergeSort(partition.data, partition.length, axis);
    KDMedianRecovery recoveryReturn;
    int medianLocation = partition.length/2;
    recoveryReturn.Median = partition.data[medianLocation];
    recoveryReturn.left = {partition.data, medianLocation+1};
    recoveryReturn.right = {partition.data+medianLocation+1, partition.length - medianLocation+1};

}

#endif