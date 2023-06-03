#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <string>
#include "Deque.hpp"

struct ParseNode
{
    char value;
    ParseNode* left = nullptr;
    ParseNode* right = nullptr;
};

struct ParseTree
{
    bool think;
    Deque<ParseNode*> ParseStack;
    ParseTree(std::string expression);
    ParseNode* doParse(std::string expression);
    void parseInOrder(std::string expression);
    bool isOperand(const char letter);
    std::string preOrder();
    std::string inOrder();
    std::string postOrder();
    std::string display();

    ~ParseTree();
};

#endif