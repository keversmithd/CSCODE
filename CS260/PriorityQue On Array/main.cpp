#include <iostream>

#include "SkipList.hpp"

#include "IArray.hpp"

int compare(const int A, const int B)
{
    if(A == B)
    {
        return 0;
    }

    return (A > B) ? 2 : 1;

}
int main()
{

    int k = 1;

    SkipList<int> sk(compare, -1);

    sk.add(22);
    sk.remove(22);
    std::cout << sk.find(22) << std::endl;
    sk.add(34);
    std::cout << sk.find(34) << std::endl;

    return -1;


}