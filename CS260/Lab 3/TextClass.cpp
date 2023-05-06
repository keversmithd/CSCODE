#include "TextClass.hpp"
#include <stdexcept>
TextClass::TextClass() : head(nullptr), tail(nullptr), nodes(0), next(nullptr)
{
    //Sets head, tail and next to nullptr.
    //Sets the "size" variable nodes to zero.
}
void TextClass::addHead(const int value)
{
    TextClassNode* newHead = new TextClassNode(); //Creates a new node.
    newHead->value = value; //Changes its value to the input variable "value".
    if(head == nullptr) //If there is no head then....
    {
        head = newHead; // Set head to our new node and...
        tail = newHead; // Set tail to our new node.
    }else //Otherwise
    {
        newHead->next = head; //Set the next of our new node to the current head of the linked list and..
        head->prev = newHead; //Set the previous pointer of our head node to the the new node and...
        head = newHead; //Set head to our new node.
    }
    
}
void TextClass::addTail(const int value)
{ 
    TextClassNode* nextTail = new TextClassNode(); //Creates a new node.
    nextTail->value = value; //Sets the value of our new node to the input variable "value".
    nextTail->prev = tail; //Sets the previous pointer to point to the tail our of linked list.
    if(tail != nullptr)
    {
        tail->next = nextTail; //If tail exists then set its next pointer to this new tail.
    }
    if(head == nullptr)
    {
        head = nextTail; //If head doesn't exist set this to head and tail.
    }
    tail = nextTail; //Set tail to this new node.
}
char TextClass::getHead()
{
    if(head == nullptr) //If head doesn't exist then throw an out of range exception.
    {
        throw std::out_of_range("get head bad");
    }
    return head->value; //Return the value of the head pointer.
}
char TextClass::getTail()
{
    if(tail == nullptr) //If tail doesn't exist throw out of range error.
    {
        throw std::out_of_range("get tail bad");
    }
    return tail->value; //Return the value of the tail pointer.
}
int TextClass::removeHead()
{
    if(head == nullptr) //If head doens't exist throw range error.
    {
        throw std::out_of_range("remove head bad");
    }
    TextClassNode* nextHead = head->next; //Get the element next to the head element.
    int returnedValue = head->value; //Gather the value stored inside of the head pointer.
    delete head; //Now delete head.
    head = nextHead; //Set head to the element adjacent to the head pointer.
    if(head == nullptr) //If the adjacent pointer was non existent then set tail to nullptr to.
    {
        tail = nullptr;
    }
    return returnedValue; //Return the removed value.
}
int TextClass::removeTail()
{
    if(tail == nullptr)
    {
        throw std::out_of_range("remove tail bad");
    }
    TextClassNode* quickPrev = tail->prev; //Get the element previous to the tail.
    if(quickPrev == nullptr) //If this element was nothing, then set to head to nullptr because the list is empty.
    {
        head = nullptr;
    }
    int quickInt = tail->value; //Gather the previous tails information.
    delete tail; //Now delete the tail.
    tail = quickPrev; //Set tail to the previous pointer.
    return quickInt; //Return the gathered information from the removed pointer.
    
}
bool TextClass::find(const int value)
{
    if(head == nullptr || tail == nullptr) //If list is empty return false.
    {
        return false;
    }
    TextClassNode* root = head; //Creates an iteration node set the head of the linked list.
    bool found = false; //Creates a variable to keep track of whether the node has been found or not.
    while(root != nullptr && found == false) //While the iteration node does not point to nothing and the element has not been found...
    {
        found = (root->value == value); //Found is set to whether the root contains the same value.
        root = root->next; //Iterates root to the next element.
        
    }
    return found; //Returns the status of the found variable.
}
bool TextClass::findRemove(const int value)
{
    if(head == nullptr || tail == nullptr) //If list is empty return false.
    {
        return false;
    }
    TextClassNode* root = head; //Creates an iteration node set the head of the linked list.
    bool found = false; //Creates a variable to keep track of whether the node has been found or not.
    while(root != nullptr && found == false) //While the iteration node does not point to nothing and the element has not been found...
    {
        TextClassNode* next = root->next; //Gets a pointer next to the current pointed to node.
        found = (root->value == value); //Found is set to whether the root contains the same value.
        if(found == true) //If found is true...
        {
            if(root->prev == nullptr) //And it is the head
            {
                head = root->next; //Then set head to the found nodes next value.
                head->prev = nullptr; //Then set the roots next variable to nullptr.

            }else if(root->prev != nullptr) //If it is not the head.
            { 
                root->prev->next = root->next; //Then set the previous pointer to the root to point to the pointer next to the root.
            }            
            delete root; //And delete the root.
        }
        root = next; //Iterates root to the next element.
        
    }
    return found; //Returns the found status.
}
std::string TextClass::displayList()
{
    std::string megaString; //Creates a std string object.
    std::string endsWith; //And a buffer just for some more chars.
    if(head == nullptr) //If  list is empty throw error and return an empty string.
    {
        throw std::out_of_range("display bad");
        return megaString;
    }
    TextClassNode* rootPtr = head; //Create an iterative node pointing to the head.
    while(rootPtr != nullptr) //While the pointer has not reached the end of the list.
    {
        endsWith = (rootPtr->next != nullptr) ? ", " : "\n"; //If the next element in the list is non existent then simply add a new line because we are done adding information to the string.
        megaString += (char)rootPtr->value + endsWith; //Concatenate the value of the element at the iterative node and the endsWith string.
        rootPtr = rootPtr->next; //Iterates root to the next element.
    }
    return megaString; //Returns this string.
}
void TextClass::append(const TextClass& otherList)
{
    if(otherList.head == nullptr || otherList.tail == nullptr) //If the other list is empty then soft throw a simple return.
    {
        return;
    }
    TextClassNode* inserted = otherList.head; //An iterative node pointing to the other lists head.
    while(inserted != nullptr)
    {
        addTail(inserted->value); //Add a tail to our linked list using this iterative nodes value.

        inserted = inserted->next; //And iterate the next node in the other list.
    }
}
// bool TextClass::findNext(const int value)
// {
//     if(head == nullptr || tail == nullptr)
//     {
//         return false;
//     }
//     TextClassNode* root = head;
//     bool found = false;
//     while(root != nullptr && found == false)
//     {
//         found = (root->value == value);
//         if(found == true)
//         {
//             if(next != nullptr && (void*)root == (void*)next)
//             {
//                 found = false;
//             }
//             else
//             {
//                 next = root;
//             }
            
//         }
//         root = root->next;
//     }

//     if(found == false)
//     {
//         next = nullptr;
//     }

//     return found;
// }

bool TextClass::findNext(const int value)
{
    if(head == nullptr || tail == nullptr)
    {
        return false;
    }
    TextClassNode* root = head; //set iterator to head
    bool found = false; //found false
    bool addressReached = false; //false
    bool encircledOnce = false; //false
    while(root != nullptr && found == false)
    {
        found = (root->value == value); //if the root value is the current value seraching for.
        if(found == true) //if that is the case.
        {

            if((void*)root == (void*)next) //if the current addresss is the same as the next token, set address reached to true.
            {
                addressReached = true;
            }
            
            if(next != nullptr && (void*)root == (void*)next) //if this is current the same as the next token keep searching
            {
                found = false;
            }else
            if(next != nullptr && (next->value == value) && !addressReached) //or if the value of the next token is the same we are searching for keep searching
            {
                found = false;
            }
            else //other wise this is the root and stop searching
            {
                next = root;
            }
            
        }
        if(!encircledOnce && (void*)root == (void*)tail) //If the list has not been encircled once and the current iteartion is at the tail end of the list.
        {
            root = head; //Start at the head of the list.
            encircledOnce = true; //And set encircled once to true.
        }else
        {
            root = root->next; //Otherwise iterate as normal.
        }
    }

    if(found == false) //If nothing is found.
    {
        next = nullptr; //Set the saved reference to nullptr.
    }

    return found; //Return the found status.
}

bool TextClass::checkLinkedStatus()
{
    if(head == nullptr){return true;}
    TextClassNode* iterator = head;
    bool connectivity = true;
    while(iterator != nullptr)
    {
        if(iterator->prev != nullptr)
        {
        }else
        {
            if ((void*)iterator != (void*)head)
            {
                connectivity = false;
            }
        }
        if(iterator->next != nullptr)
        {
        }else
        {
            if((void*)iterator != (void*)tail)
            {
                connectivity = false;
            }
        }
        iterator = iterator->next;
    }
    return connectivity;
}
void TextClass::insertLast(const int value)
{
    if(next != nullptr)
    {
        TextClassNode* insertion = new TextClassNode(); //Creates a new node.
        insertion->value = value; //Set the value of the new node to the value variable.
        insertion->next = next; //Sets the next to point to the saved reference variable from find next.
        if(next->prev != nullptr) //If the refence variable is not the head
        {
            insertion->prev = next->prev; //Then set the previous pointer of the inserted node to point to the "next" nodes previous element.
            next->prev->next = insertion; //Then set the "next" nodes previous elements next pointer to the inserted node.
            next->prev = insertion; //Then set the "next" nodes previous pointer inserted.
        }
        
    }
    
}
int TextClass::removeLast(){
    int L = -1; //Creates temporary variable of the last found elements value.
    if(next != nullptr)
    {
        if(next->prev != nullptr) //If "next" is not the head.
        {
            next->prev->next = next->next; //skip this node.
            next->next->prev = next->prev; //skip this node backward.
        }
        L = next->value; //save varialble.
        delete next; //delete the saved reference.
        next = nullptr; //make this reference pointer to nullptr.
    }
    return L; //return the saved variable.
}
TextClass::~TextClass()
{

    //Iterates through the list until it reaches the end and deletes all of them.

    TextClassNode* iterator = head;
    TextClassNode* memSkip = nullptr;

    while(iterator != nullptr)
    {
        memSkip = iterator;
        iterator = iterator->next;
        if(memSkip != nullptr)
        {
            delete memSkip;
        }
    }
}