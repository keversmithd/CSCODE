#include "ChainHash.hpp"

ChainHash::ChainHash(int desiredCapacity) : hashData(nullptr), capacity(0), maxHeight(0)
{
    //Constructor the the hash table using a parameter with a default value of zero.
    //If the paramter is less than or equal to zero set the capacity to seven, otherwise set it to the desired capacity.
    if(desiredCapacity <= 0)
    {
        capacity = 7;
    }else 
    {
        capacity = desiredCapacity;
    }

    resize(capacity); //Ultimately resize based on the capacity value.
}
void ChainHash::addItem(const std::string value)
{
    if(maxHeight >= 4) //If max height of any linked list in the table is greater than or equal to four, then resize and rehash.
    {
        maxHeight = 0;
        int prevSize = capacity;
        int newCapacity = (2*capacity)-1;

        if(isPrime(newCapacity))
        {
            resize(newCapacity);
        }
        else
        {
            resize(nextPrime(newCapacity));
        }
        rehash(prevSize);
    }
    int linkedListIndex = hashFunc(value); //Gets the hash index.
    hashData[linkedListIndex].AddToEnd(value); //Appends to the end of that linked list.
    maxHeight = (hashData[linkedListIndex].elements > maxHeight) ? hashData[linkedListIndex].elements : maxHeight; //Set value of the new max height.
}
void ChainHash::displayLists() //function not listed.
{
    for(int i = 0; i < capacity; i++)
    {
        printf("List: #%d.\n", i);
        HashLink<std::string>* tip = hashData[i].root;
        while(tip != nullptr)
        {
            printf("%s, ", tip->value.c_str());
            tip = tip->next;
        }
        printf("\n");
    }
}
std::string ChainHash::displayTable()
{
    //Creates string and concatenates values onto the string and returns the string.
    std::string tableData;
    for(int i = 0; i < capacity; i++)
    {
        HashLink<std::string>* tip = hashData[i].root;
        if(tip == nullptr)
        {
            tableData += "_empty_";
        }
        while(tip != nullptr)
        {
            tableData += tip->value + ", ";
            tip = tip->next;
        }
        tableData += "\n";
    }
    

    return tableData;
}
bool ChainHash::findItem(const std::string value)
{
    //Calculates hash index of the value, then runs search on that specific linked list.
    int linkedListIndex = hashFunc(value);
    HashLink<std::string>* link = hashData[linkedListIndex].root;
    bool found = false;
    while(link != nullptr && found == false)
    {
        if(link->value == value)
        {
            found = true;
        }else
        {
            link = link->next;
        }
    }
    return found;
}
void ChainHash::resize(int newSize)
{
    //Simply resizes the list and copies over the values.
    HashList<std::string>* memBuffer = new HashList<std::string>[newSize];
    if(memBuffer == nullptr){throw("bad");}

    int elementsToCopy = (newSize >= capacity) ? capacity : newSize;
    if(hashData != nullptr)
    {
        memcpy(memBuffer, hashData, (elementsToCopy)*sizeof(HashList<std::string>));
    }   
    
    if(hashData != nullptr && hashData != memBuffer)
    {
        delete[] hashData;
    }

    hashData = memBuffer;
    capacity = newSize;
}

void ChainHash::rehash(int prevSize)
{

    //A rehash function, which keeps track of the current node and the previous node.

    HashLink<std::string>* currNode = nullptr;
    HashLink<std::string>* prevNode = nullptr;

    //It uses these temp nodes to save the current and previous node before altering them or removing them from the list.

    HashLink<std::string>* tempCurrNode = nullptr;
    HashLink<std::string>* tempPrevNode = nullptr;

    //It uses these two strings to keep track of whether the loop is reinserting the same value into the same list over and over again.

    std::string redistributionValue;
    std::string previousValue;

    int HashFunc = 0;
    bool p = false;

    for(int i = 0; i < prevSize; i++)
    {
        currNode = hashData[i].root;
        prevNode = hashData[i].root;
        while(currNode != nullptr)
        {
            tempCurrNode = currNode;
            tempPrevNode = prevNode;
            if(p == true)
            {
                prevNode = prevNode->next;
            }
            p = true;
            currNode = currNode->next;
            redistributionValue.clear();
            redistributionValue = hashData[i].remove(tempPrevNode,tempCurrNode);
            HashFunc = hashFunc(redistributionValue);

            if(redistributionValue == previousValue)
            {
                prevNode = currNode;
                if(currNode != nullptr && currNode->next != nullptr)
                {
                    currNode = currNode->next;
                }
            }
            else
            {
                hashData[HashFunc].AddToEnd(redistributionValue);
            }

            previousValue = redistributionValue;
        }
        
    }   
}
void ChainHash::removeItem(const std::string value)
{
    //Finds and removes the value from the list using the index.
    int linkedListIndex = hashFunc(value);
    hashData[linkedListIndex].remove(value);
}
int ChainHash::hashFunc(const std::string key)
{
    //Provided by jim bailey and team
    int hashValue = 0;

    for(int i = 0; i < key.length(); i++)
    {
        hashValue *= 128;
        hashValue += key[i];
        hashValue %= capacity;
    }

    return hashValue;
}
ChainHash::~ChainHash()
{
    //deletes the main storage pointer if it isn't nullptr.
    for(int i = 0; i < capacity; i++)
    {
        hashData[i].destroy = true;
    }
    if(hashData != nullptr)
    {
        delete[] hashData;
    }
}