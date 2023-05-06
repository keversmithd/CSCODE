#include <iostream>

#include "ParseTree.hpp"

#define TEST_BASE
#define TEST_ADV
#define TEST_THINK

#define DISPLAY

int main()
{
    std::cout << "Testing Base Parse Tree" << std::endl << std::endl;
    
    std::string expression1 = "AB+CD-*";
    std::string expression2 = "AB-C+DE/*";
    
    ParseTree ptree1(expression1);
    std::cout << "Input is " << expression1 << std::endl;
    std::cout << "In Order should be ((A+B)*(C-D)) or (((A)+(B))*((C)-(D))) \n   and is " << ptree1.inOrder() << std::endl;
    std::cout << "Post Order should be AB+CD-* and is " << ptree1.postOrder() << std::endl;
    std::cout << "Pre Order should be *+AB-CD and is " << ptree1.preOrder() << std::endl << std::endl;
    
    #ifdef DISPLAY
        std::cout << ptree1.display() << std::endl;
    #endif //DISPLAY



}