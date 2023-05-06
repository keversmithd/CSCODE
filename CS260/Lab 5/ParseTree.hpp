#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <string>
#include "Deque.hpp"

struct ParseNode
{
    char value;
    ParseNode* left;
    ParseNode* right;
};

struct ParseTree
{
    Deque<ParseNode> ParseStack;
    ParseTree(std::string expression);
    ParseNode doParse(std::string expression);
    std::string preOrder();
    std::string inOrder();
    std::string postOrder();
    std::string display();
    ~ParseTree();
};

#endif