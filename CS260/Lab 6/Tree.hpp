#ifndef TREE_MAN_H
#define TREE_MAN_H
#include <string>
#include "Deque.hpp"
struct TreeNode
{
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class Tree
{
    TreeNode* root;
    public:
        Tree(); //Basic Constructor responsible for only initializing root as nullptr.
        void insertValue(const int value);
        std::string inOrder();
       

        std::string preOrder();
    
        std::string postOrder();
      
        std::string display();
        
        void inOrderRec(std::string& s, TreeNode* n);


        void preOrderRec(std::string& s, TreeNode* n);


        void postOrderRec(std::string& s, TreeNode* n);

    
        bool findValue(const int value);
        

        void removeValue(const int value);
        
        
        int findLarger(const int value);
       
        int removeLarger(const int value);
};

#endif