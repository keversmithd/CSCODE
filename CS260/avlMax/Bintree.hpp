#ifndef BINTRE
#define BINTRE

#include "Deque.hpp"

template<typename T>
struct BTNode
{   
    T value;
    BTNode<T>* left;
    BTNode<T>* right;
    BTNode<T>* parent;
    
};

template<typename T>
struct BTree
{
    BTNode<T>* root;
    int(*c)(T a, T b);

    BTree(int(*compare)(T a, T b)) : root(nullptr), c(nullptr)
    {
        c = compare;
        if(c == nullptr){throw ("agggg");}

    }

    int depth(BTNode<T>* u)
    {
        int d = 0;
        while(u != root)
        {
            u = u->parent;
            d++;
        }
        return d;
    }

    int size(BTNode<T>* u)
    {
        if(u == nullptr) return 0;
        return 1 + size(u->left) + size(u->right);
    }

    int height(BTNode<T>* u)
    {
        if (u == nullptr) return -1;
        int lheight = height(u->left);
        int rheight = height(u->right);
        return 1 + (lheight > rheight) ? lheight : rheight;  
    }

    void traverse(BTNode<T>* u)
    {
        if (u == nullptr) return;
        traverse(u->left);
        traverse(u->right);
    }

    void traverse2()
    {
        BTNode<T>* u = root, prev = nullptr, next = nullptr;
        while(u != nullptr)
        {
            if( prev == u->parent)
            {
                if(u->left != nullptr) next = u->left;
                else if(u->right != nullptr) next = u->right;
                else next = u->parent;
            }else if (prev == u->left)
            {
                if (u->right != nullptr) next = u->right;
                else next = u->parent;
            }else
            {
                next = u->parent;
            }

            prev = u;
            u = next;
        }
    }

    int size2()
    {
        BTNode<T>* u = root, prev = nullptr, next = nullptr;
        int n = 0;
        while(u != nullptr)
        {
            if(prev == u->parent)
            {
                n++;
                if(u->left != nullptr) next = u->left;
                else if(u->right != nullptr) next = u->right;
                else next = u->parent;
            }else if (prev == u->left)
            {
                if(u->right != nullptr) next = u->right;
                else next = u->parent;
            } else {
                next = u->parent;
            }
            prev = u;
            u = next;
        }
        return n;
    }

    void bfTraverse()
    {
        Deque<BTNode<T>*> q;
        if(root != nullptr) q.addTail(root);
        while(!q.isEmpty())
        {
            BTNode<T>* u = q.removeHead();
            if(u->left != nullptr) q.addTail(u->left);
            if(u->right != nullptr) q.addTail(u->right);
        }
    }

    T find(T x, bool& found)
    {
        BTNode<T>* w = root, z = nullptr;
        while(w != nullptr)
        {
            int comp = c(x, w->x);
            if (comp < 0)
            {
                z = w;
                w = w->left;
            }else if (comp > 0)
            {
                w = w->right;
            } else
            {
                found = true;
                return w->value;
            }
        }
        found = (z == nullptr);
        if(found)
        {
            return z->value;
        }
        return T();
    }

};

#endif