#ifndef TREAP_H
#define TREAP_H

#include "Deque.hpp"
#include "ran.hpp"
template<typename T>
struct TRPNode
{   
    int size = 1;
    int depth = 0;
    int height = 0;

    T value;
    TRPNode<T>* left;
    TRPNode<T>* right;
    TRPNode<T>* parent;
    int p = 0;
    
};

template<typename T>
struct TRPTree
{
    TRPNode<T>* root;
    int elements;
    int(*c)(T a, T b);

    TRPTree(int(*compare)(T a, T b)) : root(nullptr), c(nullptr), elements(0)
    {
        c = compare;
        if(c == nullptr){throw ("agggg");}

    }

    int depth(TRPNode<T>* u)
    {
        int d = 0;
        while(u != root)
        {
            u = u->parent;
            d++;
        }
        return d;
    }

    int size(TRPNode<T>* u)
    {
        if(u == nullptr) return 0;
        return 1 + size(u->left) + size(u->right);
    }

    int height(TRPNode<T>* u)
    {
        if (u == nullptr) return -1;
        int lheight = height(u->left);
        int rheight = height(u->right);
        return 1 + (lheight > rheight) ? lheight : rheight;  
    }

    void traverse(TRPNode<T>* u)
    {
        if (u == nullptr) return;
        traverse(u->left);
        traverse(u->right);
    }

    void traverse2()
    {
        TRPNode<T>* u = root, prev = nullptr, next = nullptr;
        
        while(u != nullptr) //while u not nullptr
        {

            

            //if decendant from a childless node
            //go priority clock wise around node

            //if decendant from its left node
            //go right up tree

            

            if(prev == u->parent) //the root will always match this clause and go left, will then go left again and so on until no nodes, and then will come back to the root.
            {
                if(u->left != nullptr) next = u->left; //use left
                else if(u->right != nullptr) next = u->right; //or use right
                else next = u->parent; //okay just use parent

            }else if (prev == u->left) //other wise if prev was a left, then go right
            {
                if (u->right != nullptr) next = u->right; //use right
                else next = u->parent; //okay just use a parent
            }else
            {
                next = u->parent; //otherwise u = parent
            }

            prev = u; //prev equals previous
            u = next; //u = next
        }
    }

    int size2()
    {
        TRPNode<T>* u = root;
        TRPNode<T>* prev = nullptr;
        TRPNode<T>* next = nullptr;
        int n = 0;
        while(u != nullptr)
        {
            if(prev == u->parent) //if set to parent before and prev not changed
            {
                n++;
                if(u->left != nullptr) next = u->left; 
                else if(u->right != nullptr) next = u->right;
                else next = u->parent; //goes up  if no children

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
        Deque<TRPNode<T>*> q;
        if(root != nullptr) q.addTail(root);
        while(!q.isEmpty())
        {
            TRPNode<T>* u = q.removeHead();
            if(u->left != nullptr) q.addTail(u->left);
            if(u->right != nullptr) q.addTail(u->right);
        }
    }

    T findEQ(T x)
    {

        TRPNode<T>* u = root;
        while (u != nullptr)
        {
            int comp = compare(x, u->value);
            
            if(comp == 1)
                u = u->left;
            else if (comp == 2)
                u = u->right;
            else if (comp == 0)
                return u.x;
        }

        return T();
    }

    T find(T x, bool& found)
    {
        TRPNode<T>* w = root, z = nullptr;
        while(w != nullptr)
        {
            int comp = c(x, w->x);
            if (comp == 1)
            {
                z = w;
                w = w->left;
            }else if (comp == 2)
            {
                w = w->right;
            }else
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
    TRPNode<T>* findNode(T x, bool& found)
    {
        TRPNode<T>* w = root;
        TRPNode<T>* z = nullptr;
        while(w != nullptr)
        {
            int comp = c(x, w->value);
            if (comp == 1)
            {
                z = w;
                w = w->left;
            }else if (comp == 2)
            {
                w = w->right;
            }else
            {
                found = true;
                return w;
            }
        }
        found = (z == nullptr);
        if(found)
        {
            return z;
        }
        return T();
    }
    bool add(T x)
    {
        TRPNode<T>* q = new TRPNode<T>();
        q->value = x;
        q->p = dis(gen);


        TRPNode<T>* p = findLast(x);
        
        if(addChild(p, q))
        {
            bubbleUp(q);
            return true;
        }
        return false;
    }

    void bubbleUp(TRPNode<T>* u)
    {
        while(u->parent != nullptr && u->parent->p > u->p)
        {
            if(u->parent->right == u)
            {
                rotateLeft(u->parent);
            }else
            {
                rotateRight(u->parent);
            }
        }
        if(u->parent == nullptr)
        {
            root = u;
        }
    }

    void trickleDown(TRPNode<T>* u)
    {
        while(u->left != nullptr || u->right != nullptr)
        {
            if(u->left == nullptr)
            {
                rotateLeft(u);
            }else if(u->right == nullptr)
            {
                rotateRight(u);
            }else if(u->left->p < u->right->p)
            {
                rotateRight(u);
            }else{
                rotateLeft(u);
            }
            if(root == u)
            {
                root = u->parent;
            }
        }
    }

    TRPNode<T>* findLast(T x)
    {
        TRPNode<T>* w = root;
        TRPNode<T>* prev  = nullptr;
        Deque<TRPNode<T>*> UpChain;
        while(w != nullptr)
        {
            UpChain.addTail(w);

            prev = w;
            int comp = c(x, w->value);
            if(comp == 1)
                w = w->left;
            else if (comp == 2)
                w = w->right;
            if(comp == 0)
                return w;
        }

        while(!UpChain.isEmpty())
        {
            TRPNode<T>* q = UpChain.removeTail();
            q->size = 1 + (q->left ?  q->left->size : 0) + (q->right ? q->right->size : 0);
            q->height = 1 + std::max((q->left ? q->left->height : 0), (q->right ? q->right->height : 0));
            q->depth = 1 + (q->parent ? q->parent->depth : -1);
        }

        return prev;
    }

    bool addChild(TRPNode<T>* p, TRPNode<T>* u)
    {
        if(p == nullptr)
        {
            u->depth = 0;
            u->height = 0;

            root = u;

        } else
        {
            int comp = c(u->value, p->value);
            if(comp == 1)
            {
                p->left = u;
            } else if (comp == 2)
            {
                p->right = u;
            }else
            {
                return false;
            }
            
            u->parent = p;
        }
        
        elements++;
        return true;
    }
    
    void splice(TRPNode<T>* u)
    {
        TRPNode<T>* s;
        TRPNode<T>* p;

        if(u->left != nullptr) //if u has a left child
        { 
            s = u->left; //set s to that left child.

        } else //u has only one child
        {
            s = u->right;
        }

        if(u == root) //if u is the root, then set the root to the left dominant child.
        {
            root = s;
            p = nullptr;

        } else {

            p = u->parent;
            if (p->left == u)
            {
                p->left = s;
            }else{
                p->right = s;
            }
        }

        if(s != nullptr)
        {
            s->parent = p;
        }

        while (p != nullptr)
        {
            p->size = 1 + (p->left ? p->left->size : 0) + (p->right ? p->right->size : 0);
            p->height = 1 + std::max((p->left ? p->left->height : -1), (p->right ? p->right->height : -1));
            p->depth = 1 + (p->parent ? p->parent->depth : -1);

            p = p->parent;
        }

        elements--;
    }

    bool remove(const T x)
    {
        TRPNode<T>* u = findLast(x);
        if(u != nullptr && c(u->value, x) == 0)
        {
            trickleDown(u);
            splice(u);
            return true;
        }
        return false;
    }

    // void remove(const T value)
    // {


    //     TRPNode<T>* w = root;
    //     while(w != nullptr)
    //     {
    //         int comp = c(value, w->value);
    //         if(comp == 1)
    //             w = w->left;
    //         else if(comp == 2)
    //             w = w->right;
    //         else
    //         {
    //             removeNode(w);
    //             w = nullptr;
    //         }
                
    //     }
    // }

    void removeNode(TRPNode<T>* u)
    {
        if(u->left == nullptr || u->right == nullptr)
        {
            splice(u);
        }
        else {
            TRPNode<T>* w = u->right;
            while(w->left != nullptr)
                w = w->left;
            u->value = w->value;
            splice(w);
        }

        TRPNode<T>* p = u->parent;
        while (p != nullptr)
        {
            p->size = 1 + (p->left ? p->left->size : 0) + (p->right ? p->right->size : 0);
            p->height = 1 + std::max((p->left ? p->left->height : -1), (p->right ? p->right->height : -1));
            p->depth = 1 + (p->parent ? p->parent->depth : -1);
            p = p->parent;
        }
    }

    Deque<T> getLE(const T x)
    {
        Deque<T> lessThanOrEqual;

        bool Found = false;
        TRPNode<T>* r = findNode(x, Found);
        if(!Found)
        {
            return lessThanOrEqual;
        }
        Deque<TRPNode<T>*> nodes;
        nodes.addTail(r);
        bool leaf = false;
        while(!nodes.isEmpty())
        {
            r = nodes.removeTail();
            lessThanOrEqual.addHead(r->value);

            if(r->right && !leaf)
                nodes.addTail(r->right);
            if(r->left && !leaf)
                nodes.addTail(r->left);
            else if(r->parent && c(r->parent->value,  r->value) != 2)
            {
                nodes.addTail(r->parent);
                if(r->parent->left && c(r->parent->left->value,  r->value) == 1)
                {
                    nodes.addTail(r->parent->left);
                }
                if (r->parent->right && c(r->parent->right->value,  r->value) == 1)
                {
                    nodes.addTail(r->parent->right);
                }
                leaf = true;
            }   

            

        }

        return lessThanOrEqual;


    }

    void rotateLeft(TRPNode<T>* u)
    {
        TRPNode<T>* w = u->right;
        w->parent = u->parent;
        if(w->parent != nullptr)
        {
            if(w->parent->left == u)
            {
                w->parent->left = w;
            }else{
                w->parent->right = w;
            }
        }
        u->right = w->left;
        if(u->right != nullptr)
        {
            u->right->parent = u;
        }
        u->parent = w;
        w->left = u;
        if(u == root) { root = w; root->parent = nullptr;}
    }

    void rotateRight(TRPNode<T>* u)
    {
        TRPNode<T>* w = u->left;
        w->parent = u->parent;

        if(w->parent != nullptr)
        {
            if(w->parent->left == u)
            {
                w->parent->left = w;
            }else
            {
                w->parent->right = w;
            }
        }
        u->left = w->right;
        if(u->left != nullptr)
        {
            u->left->parent = u;
        }
        u->parent = w;
        w->right = u;
        if (u == root) { root = w; root->parent = nullptr; }

    }

};

#endif