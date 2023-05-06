#include <iostream>
#include "Bintree.hpp"
#include "AVLBALANCE.hpp"
bool c_left(const int a, const int b)
{
    return a < b;
}
bool c_right(const int a, const int b)
{
    return a >= b;
}

int main()
{
   avl_tree<int> e(c_left, c_right);
   e.insert(22);
   e.insert(34);
   e.insert(44);
   e.insert(56);
   e.insert(57);
   e.insert(58);
   e.insert(59);
   e.insert(61);
   e.insert(62);
   e.insert(63);
   e.insert(64);
   e.insert(65);
   e.insert(65);
   e.insert(65);
   e.insert(65);
   e.insert(64);
   e.insert(60);
   e.insert(21);
   e.insert(22);
   e.texorder();
}