#ifndef SEDLIS_H
#define SEDLIS_H

#include "Deque.hpp"
#include <stdexcept>



template<typename T>
struct SEDNode
{
    Deque<T> value;
    SEDNode(int b) : next(nullptr), prev(nullptr), value(b)
    {

    }
    SEDNode* next;
    SEDNode* prev;
};

template<typename T>
struct Location
{
    SEDNode<T>* nodal;
    int index;
    Location(){}
    Location(SEDNode<T>* Nodal, int Index)
    {
        nodal = Nodal;
        index = Index;
    }
};


template<typename T>
struct SEList
{
private:
    SEDNode<T> root;
    int numberOfElements;
    int boundLimit;
public:
    SEList(int bounds = 5) : root(0), numberOfElements(0), boundLimit(bounds)
    {
        if(bounds <= 0)
        {
            boundLimit = 5;
        }
    }
    Location<T> getLocation(int i)
    {
        if(i >= numberOfElements)
        {
            throw std::out_of_range("invalid index to get location");
        }


        if(i < numberOfElements/2) //if i is in the left range of all elements.
        {            
            SEDNode<T>* nodal = root.next; 
            while(i >= nodal->value.size())
            {
                i -= nodal->value.size(); //this will jump from array bucket to array bucket until it reaches the optimal location.
                nodal = nodal->next;
            }

            return Location<T>(nodal, i);

        }else {

            //this doesn't work because there is nothing past the root, which would be the head. so need to add a tail here but for now will just fix later

            SEDNode<T>* nodal = &root;
            int idx = numberOfElements;
            while(i < idx)
            {
                nodal = nodal->prev;
                idx -= nodal->value.size();
            }
            return Location<T>(nodal, i-idx);
        }
    }

    T get(int i)
    {
        Location<T> l = getLocation(i);
        return l.nodal->value.at(l.index);
    }

    T set(int i, T element)
    {
        Location<T> l = getLocation(i);
        T value = l.nodal->value.at(l.index);
        l.nodal->value[l.index] = element;
        return value;
    }

    SEDNode<T>* addBefore(SEDNode<T>* node) //not actually before/but after?
    {
        SEDNode<T>* newNode = new SEDNode<T>(boundLimit+1);


        if(root.prev != nullptr)
        {
            root.prev->next = newNode;
            newNode->prev = root.prev;
        }

        if(root.next == nullptr)
        {
            root.next = newNode;
        }

        newNode->next = &root;
        root.prev = newNode;


        return newNode;
    }

    bool add(T element)
    {

        SEDNode<T>* last = root.prev;

        if(last == nullptr || last->value.size() == boundLimit+1)
        {
            last = addBefore(&root);
        }

        last->value.addTail(element);
        numberOfElements++;
        return true;
    }

    void showLists()
    {
        SEDNode<T>* iterator = root.next;
        int listNumber = 0;
        while(iterator != nullptr && iterator != &root)
        {
            listNumber++;
            std::cout << "List #" << listNumber << std::endl;
            for(int i = 0; i < iterator->value.size(); i++)
            {
                std::cout << iterator->value[i] << ", ";
            }
            std::cout << std::endl;
            iterator = iterator->next;
            
        }
        std::cout << "\n" << std::endl;
    }

    void add(int i, T element)
    {
        if (i == numberOfElements) //adds to end if i is at the end of the numberOfElements and there is one empty space left in the previous list.
        {
            add(element);
            return;
        }

        Location<T> block = getLocation(i);
        SEDNode<T>* blockPointer = block.nodal;

        int r = 0;
        while(r < boundLimit && blockPointer != &root && blockPointer->value.size() == boundLimit+1) //finds next empty block or until head
        {
            blockPointer = blockPointer->next; 
            r++;
        }
        if(r == boundLimit)
        {
            spread(block.nodal);  //spreads the insertion location.
            showLists();
            blockPointer = block.nodal;
        }
        if(blockPointer == &root)
        {
            blockPointer = addBefore(blockPointer);
        }
        while(blockPointer != block.nodal)
        {
            blockPointer->value.insert(blockPointer->value.begin(), blockPointer->prev->value.back());
            blockPointer = blockPointer->prev;
        }
        blockPointer->value.insert(blockPointer->value.begin()+block.index, element);
        numberOfElements++;
    }

    void readNodesList(SEDNode<T>* node)
    {
        std::cout << "Node Reading: " << std::endl;
        for(int i = 0; i < node->value.size(); i++)
        {
            std::cout << node->value.at(i) << ", ";
        }
        std::cout << std::endl;
    }

    void spread(SEDNode<T>* node)
    {
        SEDNode<T>* w = node;
        for(int j = 0; j < boundLimit; j++) //gathers the node (boundLimit) distance to the right of the insertion node.
        {
            w = node->next;
        }
        w = addBefore(w);
        while (w != node)
        {
            while(w->value.size() < boundLimit)
            {
                w->value.insert(w->value.begin(), w->prev->value.back());
                w->prev->value.pop_back();
            }
            w = w->prev;
        }
    }

    void gather(SEDNode<T>* node)
    {
        SEDNode<T>* w = node;
        for (int j= 0; j < boundLimit-1; j++)
        {
            while(w->value.size() < boundLimit)
            {
                w->value.push_back(w->next->value.front());
                w->next->value.erase(w->next->value.begin());
            }
            w = w->next;
        }

        remove(w);
    }

    void remove(SEDNode<T>* node)
    {
        if(node->prev != nullptr)
        {
            node->prev->next = node->next;

        }
        if(node->next != nullptr)
        {
            node->next->prev = node->prev;
        }
        delete node;
    }

    T remove(int i)
    {
        Location<T> location = getLocation(i); //Get location
        T suspectValue = location.nodal->value[location.index]; //Gather the actuall value at location i

        SEDNode<T>* nodal = location.nodal; //assign to location node.

        int r = 0; //r is block parameter for finding next with room
        while(r < boundLimit && nodal != &root && nodal->value.size() == boundLimit-1)
        {
            nodal = nodal->next;
            r++;
        }

        if(r == boundLimit)
        {
            gather(location.nodal);
        }

        nodal = location.nodal;
        nodal->value.erase(nodal->value.begin()+location.index);
        while(nodal->value.size() < boundLimit-1 && nodal->next != &root)
        {
            nodal->value.push_back(nodal->next->value.front());
            nodal->next->value.erase(nodal->next->value.begin());
            nodal = nodal->next;
        }

        if (nodal->value.size() == 0)
        {
            remove(nodal);
        }
        numberOfElements--;
        return suspectValue;
    }

};

//to-do use big deque to implement instead.

#endif