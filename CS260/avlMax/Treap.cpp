#include "Treap.hpp"
#include <iostream>
#include "viewtree.hpp"
int c_compare(const int a, const int b)
{
    if(a == b) return 0;

    return (a > b) ? 2 : 1; 
}

int main()
{   
    TRPTree<int> e(c_compare);

    e.add(22);
    e.add(33);
    e.add(44);
    e.add(22);
    e.add(77);
    e.add(88);
    e.add(11);
    e.add(0);
    e.add(-2);
    e.add(-3);
    e.add(-4);
    e.add(-5);
    e.add(-6);
    e.add(-7);
    e.add(-8);
    e.add(-9);


    e.add(-10);
    e.add(-11);
    e.add(-12);
    e.add(-13);
    e.add(-14);
    e.add(-15);
    e.add(-16);
    e.add(-17);


    e.add(99);
    e.add(110);
    e.add(120);
    e.add(130);
    e.add(140);
    e.add(150);
    e.add(160);
    

    //e.remove(11);
    e.add(1);

    // Deque<int> zz = e.getLE(88);
    // std::cout << zz.listQueue() << std::endl;


    view_tree<int, TRPNode<int>*>(e.root, e.elements);
}