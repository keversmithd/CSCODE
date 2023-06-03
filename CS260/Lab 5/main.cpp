#include <iostream>

#include "ParseTree.hpp"

#define TEST_BASE
#define TEST_ADV
#define TEST_THINK

#define DISPLAY

int main(int argc, const char * argv[])
{
    #ifdef TEST_BASE
    
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
    
    ParseTree ptree2(expression2);
    std::cout << "Input is " << expression2 << std::endl;
    std::cout << "In Order output should be (((A-B)+C)*(D/E)) or ((((A)-(B))+(C))*((D)/(E))) \n   and is" << ptree2.inOrder() << std::endl;
    std::cout << "Post Order should be AB-C+DE/* and is " << ptree2.postOrder() << std::endl;
    std::cout << "Pre Order should be *+-ABC/DE and is " << ptree2.preOrder() << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree2.display() << std::endl;
#endif //DISPLAY
    
    std::cout << "Done with Parse Tree test" << std::endl << std::endl;
    
#endif // TEST_BASE
    
#ifdef TEST_ADV
    std::cout << "Testing Advanced Parse Tree" << std::endl << std::endl;
    
    std::string expression3 = "(A+B)*C+D";
    std::string expression4 = "A/(B+C)*(D+E)";
    std::string expression5 = "A/((B+C)*(D+E))";
    ParseTree ptree3("");

    ptree3.parseInOrder(expression3);
    std::cout << "Input is " << expression3 << std::endl;
    std::cout << "In Order should be (((A+B)*C)+D) or ((((A)+(B))*(C))+(D)) \n   and is " << ptree3.inOrder() << std::endl;
    std::cout << "Post Order should be AB+C*D+ and is " << ptree3.postOrder() << std::endl;
    std::cout << "Pre Order should be +*+ABCD and is " << ptree3.preOrder() << std::endl << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree3.display() << std::endl;
#endif //DISPLAY
    
    ptree3.parseInOrder(expression4);
    std::cout << "Input is " << expression4 << std::endl;
    std::cout << "In Order should be ((A/(B+C))*(D+E)) or (((A)/((B)+(C)))*((D)+(E))) \n   and is " << ptree3.inOrder() << std::endl;
    std::cout << "Post Order should be ABC+/DE+* and is " << ptree3.postOrder() << std::endl;
    std::cout << "Pre Order should be */A+BC+DE and is " << ptree3.preOrder() << std::endl << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree3.display() << std::endl;
#endif //DISPLAY
    
    ptree3.parseInOrder(expression5);
    std::cout << "Input is " << expression5 << std::endl;
    std::cout << "In Order should be (A/((B+C)*(D+E))) or ((A)/(((B)+(C))*((D)+(E)))) \n   and is " << ptree3.inOrder() << std::endl;
    std::cout << "Post Order should be ABC+DE+*/ and is " << ptree3.postOrder() << std::endl;
    std::cout << "Pre Order should be /A*+BC+DE and is " << ptree3.preOrder() << std::endl << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree3.display() << std::endl;
#endif //DISPLAY
    
    std::cout << "Done with Advanced Parse Tree test" << std::endl << std::endl;
    
#endif // TEST_ADV
    
#ifdef TEST_THINK
    std::cout << "Testing Thinking Problem" << std::endl << std::endl;
    
    std::string expression6 = "(((A+B)*C)+(D*(F/G)))";
    std::string expression7 = "((A*B)+(C-D))";
    std::string expression8 = "(A-(B-C))";

    ParseTree ptree4("");

    ptree4.parseInOrder(expression6);
    std::cout << "Input is " << expression6 << std::endl;
    std::cout << "In Order should be (A+B)*C+D*F/G and is " << ptree4.inOrder() << std::endl << std::endl;
    std::cout << "Post Order should be AB+C*DFG/*+ and is " << ptree4.postOrder() << std::endl;
    std::cout << "Pre Order should be +*+ABC*D/FG and is " << ptree4.preOrder() << std::endl << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree4.display() << std::endl;
#endif //DISPLAY
    
    ptree4.parseInOrder(expression7);
    std::cout << "Input is " << expression7 << std::endl;
    std::cout << "In Order should be A*B+C-D and is " << ptree4.inOrder() << std::endl << std::endl;
    std::cout << "Post Order should be AB*CD-+ and is " << ptree4.postOrder() << std::endl;
    std::cout << "Pre Order should be +*AB-CD and is " << ptree4.preOrder() << std::endl << std::endl;
    
#ifdef DISPLAY
    std::cout << ptree4.display() << std::endl;
#endif //DISPLAY

    ptree4.parseInOrder(expression8);
    std::cout << "Input is " << expression8 << std::endl;
    std::cout << "In Order should be A-(B-C) and is " << ptree4.inOrder() << std::endl << std::endl;
    std::cout << "Post Order should be ABC-- and is " << ptree4.postOrder() << std::endl;
    std::cout << "Pre Order should be -A-BC and is " << ptree4.preOrder() << std::endl << std::endl;

#ifdef DISPLAY
    std::cout << ptree4.display() << std::endl;
#endif //DISPLAY
    
    std::cout << "Done with Testing Thinking Problem" << std::endl << std::endl;
    
#endif // TEST_THINK
    
    return 0;
}