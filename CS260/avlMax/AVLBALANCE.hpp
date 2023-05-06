#ifndef AVLBALANCE_H
#define AVLBALANCE_H
#include "Deque.hpp"
template<typename T>
struct avl_node
{
    T value;
    avl_node *left = nullptr;
    avl_node *right = nullptr;
};

struct avl_parent_box
{
    double x, y;
};

template<typename T>
struct avl_node_parent
{
    double x, y;
    avl_node<T>* node = nullptr;
    avl_parent_box parent;

};

template<typename T>
struct avl_tree
{
    avl_node<T>* root;
    int elements;
    bool(*c_left)(const T a, const T b);
    bool(*c_right)(const T a, const T b);

    avl_tree(bool(*Compare_left)(const T a, const T b), bool(*Compare_right)(const T a, const T b)) : root(nullptr) , elements(0)
    {
        if(Compare_left == nullptr || Compare_right == nullptr)
        {
            throw ("Bad");
        }
        c_left = Compare_left;
        c_right = Compare_right;
    }
    int height(avl_node<T>* t)
    {
        //will traverse all the way down the nodal tree, and basically count all of the nodes until it isn't nullptr.
        int h = 0;
        if(t != nullptr)
        {
            int l_height = height(t->left);
            int r_height = height(t->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height+1;
        }
        return h;
    }
    int difference(avl_node<T>* t) //log n
    {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int b_factor = l_height-r_height;
        return b_factor;
    }
    //Possible optimization of keeping the height of the sub tree at each node
    avl_node<T>* rr_rotate(avl_node<T>* parent)
    {
        avl_node<T>* t = nullptr;
        t = parent->right;
        parent->right = t->left;
        t->left = parent;
        return t;
    }

    avl_node<T>* ll_rotate(avl_node<T>* parent)
    {
        avl_node<T>* t = nullptr;
        t = parent->left;
        parent->left = t->right;
        t->right = parent;

        return t;
    }
    avl_node<T>* lr_rotate(avl_node<T>* parent)
    {
        avl_node<T>* t;
        t = parent->left;
        parent->left = rr_rotate(t);
        return ll_rotate(parent);
    }
    avl_node<T>* rl_rotate(avl_node<T>* parent)
    {
        avl_node<T>* t;
        t = parent->right;
        parent->right = ll_rotate(t);
        return rr_rotate(parent);
    }

    avl_node<T>* balance(avl_node<T>* t)
    {
        int bal_facotr = difference(t);
        if(bal_facotr > 1)
        {
            if(difference(t->left) > 0)
                t = ll_rotate(t);
            else
                t = lr_rotate(t);
        }else if (bal_facotr < -1)
        {
            if(difference(t->right) > 0)
                t = rl_rotate(t);
            else
                t = rr_rotate(t);
        }

        return t;
    }

    void insert(T value)
    {
        root = insert(root, value);
        elements++;
    }
    avl_node<T>* insert(avl_node<T>* r, T value)
    {
        
        if(r == nullptr)
        {
            r = new avl_node<T>();
            r->value = value;
            r->left = nullptr;
            r->right = nullptr;
            return r;
        }else if (c_left(value, r->value))
        {
            r->left = insert(r->left, value);
            r = balance(r);
        }else if (c_right(value, r->value))
        {
            r->right = insert(r->right, value);
            r = balance(r);
        } return r;

        
    }

    
    void inorder()
    {
        inorder(root);
    }
    void inorder(avl_node<T>* t)
    {
        if(t == nullptr)
        {
            return;
        }
        inorder(t->left);
        printf("%d, ", t->value);
        inorder(t->right);
    }


    void rootorder()
    {
        int levels = log2(elements);

        int nodeproccessed = 1;
        int currentLevel = log2(nodeproccessed);
        int tLevel = currentLevel;

        Deque<avl_node<T>*> q;
        q.addTail(root);

        while(!q.isEmpty())
        {
            avl_node<T>* p = q.removeHead();
            if(p != nullptr)
            {

            
            currentLevel = log2(nodeproccessed);
            for(tLevel = tLevel; tLevel != currentLevel; tLevel++)
            {
                printf("\n");
            }
            printf("%d ", p->value);
            nodeproccessed++;

            q.addTail(p->left);
            q.addTail(p->right);
            }

            
        }



    }
  
    void texorder()
    {
        if(root == nullptr)
        {
            return;
        }

        int initalSpacing = log2(elements);

        Deque<avl_node_parent<T>> q;

        int nodeproccessed = 3;
        int currentLevel = log2(nodeproccessed);
        int tLevel = currentLevel;

        double ypad = 1.0;
        double y = 0.0;



        avl_node_parent<T> origin;
        origin.node = root;
        origin.parent = {0,0};
        origin.x = 0;
        origin.y = 0;

        printf("\\draw (%f,%f) circle (10pt) [] node {%d}; \n", origin.x, origin.y, root->value);

        if(root != nullptr && root->left != nullptr)
        {
            avl_node_parent<T> left;;
            left.node = root->left;
            left.parent = {origin.x, origin.y};
            left.x = -initalSpacing;
            left.y = -1;
            q.addTail(left);
        }

        if(root != nullptr && root->right != nullptr)
        {
            avl_node_parent<T> right;
            right.node = root->right;
            right.parent = {origin.x, origin.y};
            right.x = initalSpacing;
            right.y = -1;
            q.addTail(right);
        }
        

        while(!q.isEmpty())
        {
            
            avl_node_parent<T> p = q.removeHead();
            nodeproccessed++;
            if(p.node != nullptr)
            {
                printf("\\draw ($(%f, %f)+(275:10pt)$) -- ($(%f, %f)+(90:10pt)$);\n", p.parent.x, p.parent.y, p.x, p.y);
                printf("\\draw (%f, %f) circle(10pt) [] node {%d};\n", p.x, p.y, p.node->value);
                
                currentLevel = abs(p.y - 1);
                
                double innerSpacing = abs(p.x - p.parent.x)/2.0;

                avl_node_parent<T> leftChild;
                leftChild.parent = {p.x,p.y};
                leftChild.node = p.node->left;
                leftChild.x = p.x - innerSpacing;
                leftChild.y = -currentLevel;

                q.addTail(leftChild);

                avl_node_parent<T> rightChild;
                rightChild.parent = {p.x, p.y};
                rightChild.node = p.node->right;
                rightChild.x = p.x + innerSpacing;
                rightChild.y = -currentLevel;

                q.addTail(rightChild);

            }
            
            
        }



    }


};




#endif