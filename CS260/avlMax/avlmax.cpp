#include <iostream>
#include "Bintree.hpp"
#include "AVLBALANCE.hpp"
#include "viewtree.hpp"

int c_compare(const int a, const int b)
{
    if(a == b) return 0;

    return (a > b) ? 2 : 1; 
}

int main()
{
    BTree<int> e(c_compare);
    e.add(22);
    e.add(33);
    e.add(44);
    e.add(22);
    e.add(77);
    e.add(88);
    e.add(11);
    e.remove(11);
    e.add(1);

    Deque<int> zz = e.getLE(88);
    std::cout << zz.listQueue() << std::endl;


    view_tree<int, BTNode<int>*>(e.root, e.elements);
    
}