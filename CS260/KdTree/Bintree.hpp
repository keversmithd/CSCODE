#ifndef BINTRE
#define BINTRE

//unbalanced with useful trees

#include "Deque.hpp"

template<typename T>
struct BTNode
{   
    int size = 1;
    int depth = 0;
    int height = 0;

    BTNode(T p_value, int p_size, int p_height, int p_depth) : value(p_value), size(p_size), height(p_height), depth(p_depth)
    {
        
    }

    T value;
    BTNode<T>* left;
    BTNode<T>* right;
    BTNode<T>* parent;
    
};

template<typename T>
struct BTree
{
    BTNode<T>* root;
    int elements;
    int(*c)(T a, T b);

    BTree(int(*compare)(T a, T b)) : root(nullptr), c(nullptr), elements(0)
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

    int SizeRecursiveOrderN(BTNode<T>* u)
    {
        if(u == nullptr) return 0;
        return 1 + size(u->left) + size(u->right);
    }

    int SizeIterativeN(BTNode<T>* u)
    {
        //calculates size of the tree in terms of number of nodes
        BTNode<T>* prev = nullptr;
        BTNode<T>* next = nullptr;
        int n = 0;
        while(u != nullptr)
        {
            if(prev == u->parent) //if set to parent before and prev not changed
            {
                n++;
                if(u->left != nullptr) next = u->left; 
                else if(u->right != nullptr) next = u->right;
                else next = u->parent; //goes up if no children

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

    T findEQ(T x)
    {

        BTNode<T>* u = root;
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
        BTNode<T>* w = root, z = nullptr;
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
    
    BTNode<T>* findNode(T x, bool& found)
    {
        BTNode<T>* w = root;
        BTNode<T>* z = nullptr;
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
    
    
    BTNode<T>* findLast(T x)
    {
        BTNode<T>* w = root;
        BTNode<T>* prev  = nullptr;
        Deque<BTNode<T>*> UpChain;
        //finds last node in terms of searching in which to add
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
            BTNode<T>* q = UpChain.removeTail();
            q->size = 1 + (q->left ?  q->left->size : 0) + (q->right ? q->right->size : 0);
            q->height = 1 + std::max((q->left ? q->left->height : 0), (q->right ? q->right->height : 0));
            q->depth = 1 + (q->parent ? q->parent->depth : -1);
        }

        return prev; 
    }


    bool add(T x)
    {
        BTNode<T>* p = findLast(x);




        BTNode<T>* q = new BTNode<T>();
        if(p)
        {
            q->depth = p->depth + 1;
        }
        q->value = x;

        return addChild(p, q);
    }

    bool addChild(BTNode<T>* p, BTNode<T>* u)
    {
        if(p == nullptr)
        {
            u->depth = 0;
            u->height = 0;
            root = u;

        } else
        {
            int comp = c(u->value, p->value); //completely unneccary
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
    
    bool addUnadulterated(T x)
    {
        if(root == nullptr)
        {
            root = new BTNode<T>(x);
            root->depth = 0;
            root->height = 0;
            return true;
        }

        BTNode<T>* w = root;
        BTNode<T>* prev  = nullptr;
        Deque<BTNode<T>*> UpChain;
        int lr = 0;
        while(w != nullptr)
        {
            UpChain.addTail(w);

            prev = w;
            int comp = c(x, w->value);
            if(comp == 1)
            {   
                w = w->left;
                lr = 0;
            }   
            else if (comp == 2)
            {
                w = w->right;
                lr = 1;
            }
            if(comp == 0)
            {
                return false;
            }    
        }

        while(!UpChain.isEmpty())
        {
            BTNode<T>* q = UpChain.removeTail();
            q->size = 1 + (q->left ?  q->left->size : 0) + (q->right ? q->right->size : 0);
            q->height = 1 + std::max((q->left ? q->left->height : 0), (q->right ? q->right->height : 0));
            q->depth = 1 + (q->parent ? q->parent->depth : -1);
        }


        (lr == 0) ? prev->left = new BTNode<T>(x) : prev->right = new BTNode<T>(x);
        
        elements++;
        return true;
    }

    void splice(BTNode<T>* u)
    {
        BTNode<T>* s;
        BTNode<T>* p;

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

    void remove(const T value)
    {
        BTNode<T>* w = root;
        while(w != nullptr)
        {
            int comp = c(value, w->value);
            if(comp == 1)
                w = w->left;
            else if(comp == 2)
                w = w->right;
            else
            {
                removeNode(w);
                w = nullptr;
            }
                
        }
    }

    void removeNode(BTNode<T>* u)
    {
        if(u->left == nullptr || u->right == nullptr)
        {
            splice(u);
        }
        else {
            BTNode<T>* w = u->right;
            while(w->left != nullptr)
                w = w->left;
            u->value = w->value;
            splice(w);
        }

        BTNode<T>* p = u->parent;
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
        BTNode<T>* r = findNode(x, Found);
        if(!Found)
        {
            return lessThanOrEqual;
        }
        Deque<BTNode<T>*> nodes;
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

};

#endif