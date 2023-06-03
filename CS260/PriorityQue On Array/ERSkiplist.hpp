//SkiplistList: An Efficient Random-Access List
#ifndef ERSKIP_H
#define ERSKIP_H

template<typename T>
struct ERSkipNode
{
    T x;
    ERSkipNode<T>** next;
    int size;
    int* length;

    ERSkipNode(T ix, int h) : x(ix), next(nullptr), length(nullptr), size(0), size(h)
    {
        next = new ERSkipNode<T>*[h+1];
        for(int i = 0; i < h+2; i++)
        {
            next[i] = nullptr;
        }
        length = new int[h+1];
    }

    int height()
    {
        return size-1;
    }
};


#endif