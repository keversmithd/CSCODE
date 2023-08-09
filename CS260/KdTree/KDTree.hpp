#ifndef KD_TREE_H_IMPL1
#define KD_TREE_H_IMPL1

#include "KDTreeMedian.hpp"

KDVec* TransmuteNormalDataSet(float* Data, int Dimension, int Size)
{
    KDVec* vectorSet = new KDVec[Size];
    float* DataPtr = Data;
    for(int i = 0; i < Size; i++)
    {
        vectorSet[i] = KDVec(DataPtr, Dimension);
        DataPtr += Dimension;
    } 
}

struct KDNode
{
    KDVec location;
    KDNode* left;
    KDNode* right;
    int m_depth;
    //add depth here for conviences.
    KDNode() : location(), left(nullptr), right(nullptr)
    {

    }
    KDNode(float* data, int length) : location(data,length), left(nullptr), right(nullptr)
    {

    }
    KDNode(float* data, int length, int depth) : location(data,length), m_depth(depth), left(nullptr), right(nullptr)
    {

    }
    
    KDNode(KDVec loc) : location(loc), left(nullptr), right(nullptr)
    {
        
    }
    KDNode(KDVec loc, KDNode* l, KDNode* r) : location(loc), left(l), right(r)
    {

    }
    bool isLeaf()
    {
        return (left == nullptr && right == nullptr);
    }
};

struct KDStackPackage
{
    KDNode* node;
    KDMedianRecovery recovery;
};

struct KDTree
{
private:
    KDNode* root;
    int dimension;
public:
    KDTree(float* Data, int Dimension, int Size) : root(nullptr), dimension(Dimension)
    {
        int Depth = 0;
        int Axis = Depth % Dimension;
        KDVec* KDSet = TransmuteNormalDataSet(Data, Dimension, Size); //order N!! very bad
        KDMedianRecovery RecoveryCrate = recoverMedian({KDSet, Size}, Axis);
        root = new KDNode{RecoveryCrate.Median, nullptr, nullptr};
        Deque<KDStackPackage> Package;
        Package.addTail({root, RecoveryCrate});
        Depth++;

        while(!Package.isEmpty())
        {
            KDStackPackage ThePackage = Package.removeTail();
            Axis = Depth % Dimension;
            KDMedianRecovery left = recoverMedian({ThePackage.recovery.left.data, ThePackage.recovery.left.length}, Axis);
            KDMedianRecovery right = recoverMedian({ThePackage.recovery.right.data, ThePackage.recovery.right.length}, Axis);
            ThePackage.node->left = new KDNode{left.Median, nullptr, nullptr};
            ThePackage.node->right = new KDNode{right.Median, nullptr, nullptr};
            Package.addTail({ThePackage.node->left, left});
            Package.addTail({ThePackage.node->right, right});
            Depth++;
        }

    }

    void AddPoint(float* vector)
    {
        if(root == nullptr)
        {
            root = new KDNode(vector, dimension,0);
        }else
        {
            int depth = 0;
            KDNode* r = root;
            KDNode* p = nullptr;
            int lr = 0;

            while(r != nullptr)
            {
                int axis = depth % dimension;
                if(r->location[axis] < vector[axis])
                {   
                    p = r;
                    r = r->left;
                    
                    lr = 0;
                }else if(r->location[axis] > vector[axis])
                {
                    p = r;
                    r = r->right;
                    lr = 1;
                }else
                {
                    if(vector[axis] == r->location[axis])
                    {
                        return;
                    }else
                    {
                        if(r->right == nullptr)
                        {
                            p = r;
                            r = r->right;
                            lr = 1;
                        }else if(r->left == nullptr)
                        {
                            p = r;
                            r = r->left;
                            lr = 0;
                        }else
                        {
                            p = r;
                            r = (depth % 2 == 0) ? r->left : r->right;
                            lr = (depth % 2 == 0);
                        }
                    }
                }
                depth++;
            }


            (lr == 0) ? p->left = new KDNode(vector, dimension,depth-1) : p->right = new KDNode(vector, dimension,depth-1);
        }
        
    }

    void RemovePointIterative(float* vector)
    {
        if(root == nullptr)
        {
            return;
        }
        KDVec n(vector, dimension);
        KDNode* r = root;
        KDNode* p = nullptr;
        bool found = false;
        int depth = 0;
        int lr = 0;
        while(r != nullptr && found == false)
        {
            if(r->location == n)
            {
                if(r->isLeaf())
                {
                    delete[] r;
                }else
                {
                    //find a replacement point of the same splitting plane with minimum splitting value at right, or minimum splitting value at left
                    int axis = depth % dimension;
                    if(r->right != nullptr)
                    {
                        //traverse down the subtree looking for the minimum axisxvalue
                        
                    }else
                    {   
                        //traverse down the subtree look for the maximum axisxvalue
                    }
                }

            }else
            {
                int axis = depth % dimension;
                if(r->location[axis] < vector[axis])
                {   
                    p = r;
                    r = r->left;
                    lr = 0;
                }else if(r->location[axis] > vector[axis])
                {
                    p = r;
                    r = r->right;
                    lr = 1;
                }else
                {
                    if(vector[axis] == r->location[axis])
                    {
                        return;
                    }else
                    {
                        if(r->right == nullptr)
                        {
                            p = r;
                            r = r->right;
                            lr = 1;
                        }else if(r->left == nullptr)
                        {
                            p = r;
                            r = r->left;
                            lr = 0;
                        }else
                        {
                            p = r;
                            r = (depth % 2 == 0) ? r->left : r->right;
                            lr = (depth % 2 == 0);
                        }
                    }
                }

                depth++;
            }




        }

    }

    void RemovePoint(KDNode* n)
    {
        if(n == root)
        {
            //edge case.
        }

        KDNode* Iter = n;
        
        while(Iter != nullptr)
        {
            if(Iter->isLeaf())
            {
                delete Iter;
            }else
            {
                if(Iter->right != nullptr)
                {
                    KDNode* Replacement = FindMinimumInSubtree(Iter, Iter->m_depth%dimension);
                    Iter->location = Replacement->location;
                    Iter = Replacement;        
                }
                if(Iter->left != nullptr)
                {
                    KDNode* Replacement = FindMaximumInSubtree(Iter, Iter->m_depth%dimension);
                    Iter->location = Replacement->location;
                    Iter = Replacement; 
                }
            }
        }

        
    }

    KDNode* FindMinimumInSubtree(KDNode* rt, int axis)
    {
        Deque<KDNode*> s;
        KDNode* r = rt;

        KDNode* minNode = nullptr;
        float minax = 0;

        while(r != nullptr || !s.isEmpty())
        {
            while(r != nullptr)
            {
                s.addTail(r);
                r = r->left;
            }

            r = s.removeTail();

            if(minax == 0)
            {
                minNode = r;
                minax = r->location[axis];
            }else if(r->location[axis] < minax)
            {
                minNode = r;
                minax = r->location[axis];
            }

            r = r->right;
        }

        return minNode;

    }

    KDNode* FindMaximumInSubtree(KDNode* rt, int axis)
    {
        Deque<KDNode*> s;
        KDNode* r = rt;

        KDNode* maxNode = nullptr;
        float maxax = 0;

        while(r != nullptr || !s.isEmpty())
        {
            while(r != nullptr)
            {
                s.addTail(r);
                r = r->left;
            }

            r = s.removeTail();

            if(maxax == 0)
            {
                maxNode = r;
                maxax = r->location[axis];
            }else if(r->location[axis] > maxax)
            {
                maxNode = r;
                maxax = r->location[axis];
            }

            r = r->right;
        }

        return maxNode;
    }

    ~KDTree()
    {

    }

};



#endif