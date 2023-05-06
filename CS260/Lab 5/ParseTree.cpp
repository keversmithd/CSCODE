#include "ParseTree.hpp"


ParseTree::ParseTree(std::string expression)
{
    doParse(expression);
}
ParseNode ParseTree::doParse(std::string expression){}
std::string ParseTree::preOrder(){}
std::string ParseTree::inOrder(){}
std::string ParseTree::postOrder(){}
std::string ParseTree::display(){}
ParseTree::~ParseTree(){}