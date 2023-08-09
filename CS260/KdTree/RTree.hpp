#ifndef R_TREE_H
#define R_TREE_H

#include "RArchive.hpp"
#include "Deque.hpp"

struct RTree
{
private:
    RNode* root;
public:
    RTree() : root(nullptr)
    {

    }
    void Search(const RBoundingContainer query)
    {
        if(root == nullptr)
        {
            return;
        }

        RNode* r = nullptr;
        Deque<RNode*> ToBeSearched;
        std::vector<RBoundingContainer> IntersectedBoundingContainers;
        ToBeSearched.addTail(root);

        while(!ToBeSearched.isEmpty())
        {
            r = ToBeSearched.removeTail();

            if(r->isLeaf())
            {
                for(int i = 0; i < r->entries.size(); i++)
                {
                    if(RectangleIntersection(r->entries[i].boundingVolume, query))
                    {
                        IntersectedBoundingContainers.push_back(r->entries[i].boundingVolume);
                    }
                }
            }else
            {
                for(int i = 0; i < r->entries.size(); i++)
                {
                    if(RectangleIntersection(r->entries[i].boundingVolume, query))
                    {
                        ToBeSearched.addTail(r->entries[i].child);
                    }
                }
            }
        }
    }
    void Insert(const RBoundingContainer object)
    {
        if(root == nullptr)
        {
            root = new RNode(object);
        }
        RNode* r = root;

        while(r != nullptr)
        {
            if(r->isLeaf())
            {

            }else
            {
                int IndexOfLeastEnlargement = -1;
                int LeastEnlargement = 0;
                int LeastEnlargementBuffer = 0;
                
                for(int i = 0; i < r->entries.size(); i++)
                {
                    if(RectangleIntersection(r->entries[i].boundingVolume, object))
                    {
                        if(IndexOfLeastEnlargement == -1)
                        {
                            LeastEnlargement = EnlargementOfBoundingContainer(object, r->entries[i].boundingVolume);
                            IndexOfLeastEnlargement = i;
                        }else
                        {   
                            LeastEnlargementBuffer = EnlargementOfBoundingContainer(object, r->entries[i].boundingVolume);
                            if(LeastEnlargementBuffer < LeastEnlargement)
                            {
                                LeastEnlargement = LeastEnlargementBuffer;
                                IndexOfLeastEnlargement = i;
                            }
                        }
                    }
                }

                if(IndexOfLeastEnlargement != -1)
                {
                    r = r->entries[IndexOfLeastEnlargement].child;
                }else
                {
                    REntry newEntry;
                    newEntry.boundingVolume = object;
                    newEntry.child = nullptr;
                    r->entries.push_back(newEntry);
                }

            }
            
        }
    }

};
#endif