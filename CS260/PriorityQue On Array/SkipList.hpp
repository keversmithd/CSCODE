#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <vector>
#include "ran.hpp"



template<typename T>
struct SKNode
{   
    T x;
    SKNode<T>**  next;
    int length;

    SKNode(T ix, int h) : length(h)
    {
        x = ix;

        next = new SKNode<T>*[h+1];
        for(int i = 0; i < h+2; i++)
        {
            next[i] = nullptr;
        }

    }
    int height()
    {
        return length;
    }

    ~SKNode()
    {
        if(next != nullptr)
        {
            delete[] next;
        }
    }   
};

template<typename T>
struct SkipList
{
    SKNode<T>* sentinel;
    int elements;

    SKNode<T>** stack;

    T m_empty;
    int (*c)(const T a, const T b);
    int h;

    SkipList( int (*compare)(const T a, const T b) , T empty) : h(0), sentinel(nullptr), c(compare), m_empty(empty), elements(0)
    {
        if(c == nullptr)
        {
            throw std::out_of_range("SkipList with nullptr compare funciton.\n");
        }

        int height = pickHeight();
        sentinel = new SKNode<T>(m_empty, height);
        h = height;
        stack = new SKNode<T>*[height+1];

    }

    SKNode<T>* findPredNode(T x)
    {
        SKNode<T>* u = sentinel;
        int r = h;
        while (r >= 0)
        {
            while(u->next[r] != nullptr && c(u->next[r]->x, x) == 1)
            {
                u = u->next[r];
            }
            r--;
        }
        return u;
    }

    T find(T x)
    {
        SKNode<T>* u = findPredNode(x);
        if(u->next[0] == nullptr)
        {
            return m_empty;
        }
        return u->next[0]->x;
    }

    int pickHeight()
    {
        int z = idis(gen);
        int k = 0;
        int m = 1;
        while((z & m) != 0)
        {
            k++;
            m <<= 1;
        }
        return (k > 0) ? k : k+1;
    }

    bool add(T x)
    {
        SKNode<T>* u = sentinel;
        int r = h;
        int comp = 0;
        while(r >= 0)
        {
            while (u->next[r] != nullptr && (comp = c(u->next[r]->x, x)) == 1)
            {
                u = u->next[r];
            }

            if(u->next[r] != nullptr && comp == 0) return false;
            stack[r--] = u;
        }

        SKNode<T>* w = new SKNode<T>(x, pickHeight());
        while(h < w->height())
            stack[++h] = sentinel;
        for (int i = 0; i < w->height(); i++)
        {
            w->next[i] = stack[i]->next[i];
            stack[i]->next[i] = w;
        }
        elements++;
        return true;
    }

    bool remove(T x)
    {
        bool removed = false;
        SKNode<T>* u = sentinel;
        int r = h;
        int comp = 0;

        while(r >= 0)
        {
            while (u->next[r] != nullptr && (comp = c(u->next[r]->x, x)) == 1)
            {
                u = u->next[r];
            }
            if (u->next[r] != nullptr && comp == 0)
            {
                removed = true;
                u->next[r] = u->next[r]->next[r];
                if(u == sentinel && u->next[r] == nullptr)
                {
                    h--;
                }
            }
            r--;
        }
        if(removed) elements--;
        return removed;
    }

};

#endif