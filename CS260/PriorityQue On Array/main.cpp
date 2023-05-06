#include <iostream>
#include "SEDList.hpp"
#include "SEVList.hpp"
int main()
{
    SEList<int> i(1);
    bool added = i.add(23);
    added = i.add(44);
    i.showLists();
    added = i.add(44);
    i.showLists();

    std::cout << "value removed" << i.remove(0) << std::endl;
    i.showLists();

    Location<int> someKindOfLocation = i.getLocation(0);


    someKindOfLocation = i.getLocation(1);


    // someKindOfLocation = i.getLocation(2);
    // std::cout << someKindOfLocation.nodal->value.at(someKindOfLocation.index) << std::endl;


    i.add(1, 24);
    i.showLists();
    i.add(1, 25);
    i.add(1, 21);
    i.showLists();



}