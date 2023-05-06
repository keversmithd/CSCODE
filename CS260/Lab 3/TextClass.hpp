#ifndef TEXT_CLASS_H
#define TEXT_CLASS_H

#include <string>

struct TextClassNode //Node implementation for navigational purposes.
{
    int value = 0; //The "payload" or "actual information stored" of this node.
    TextClassNode* next = nullptr; //points to the next of its kind
    TextClassNode* prev = nullptr; //points to the previous of its kind
};

//Note: This text class has a negative memory efficency coefficient due to its narrowing conversion from four byte integer to one byte signed char.

struct TextClass //A string interface implementing a doubly "semi-circular" double ended linked list.
{
private:
    TextClassNode* head; //Pointer to beginning of linked list.
    TextClassNode* tail; //Pointer to the end of the linked list.
    TextClassNode* next; //Pointer to a saved reference from the last instance found with find next.
    int nodes;
public:
    TextClass(); //Default constructor, with no other alternatives.
    void addHead(const int value); //Push new node to the beginning of the linked list.
    void addTail(const int value); //Appends new node to the end of the linked list.
    char getHead(); //Retrieves the information from the head pointer.
    char getTail(); //Retrieves the information from the tail pointer.
    int removeHead(); //This will pop the current head out of the linked list and return its information.
    int removeTail(); //This will peel the current tail off the linked list and return its information.
    bool find(const int value); //This will return true or false depending if the information is present in the linked list.
    bool findRemove(const int value); //This will remove the element from the linked list if the information "value" is found in the linked list.
    std::string displayList(); //Returns a string concatenated with all the stringified elements from the linked list.
    void append(const TextClass& otherList); //This will add the list "otherList" with this list; this will place "otherList" at the end of this list.
    bool findNext(const int value); //This will find the next occurence of the value compared with the saved reference "next".
    bool checkLinkedStatus(); //This was just a debugging function.
    int removeLast(); //This will remove the pointer "next" from the linked list.
    void insertLast(const int value); //This will insert before the "next" pointers location in the linked list.

    ~TextClass(); //This will delete all of the nodes.
    
    
    
};

#endif