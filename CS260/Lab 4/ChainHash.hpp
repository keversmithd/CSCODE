#ifndef CHAIN_HASH_H
#define CHAIN_HASH_H
#include "HashList.hpp"
#include <string>
#include "StringHash.hpp"

class ChainHash //A seperate chaining hash-map  
{
private:
    HashList<std::string>* hashData;
    int capacity;
    int maxHeight;
public:
    ChainHash(int desiredCapacity = 0);
    void displayLists();
    std::string displayTable();
    void addItem(const std::string value);
    bool findItem(const std::string value);
    void rehash(int prevSize);
    void removeItem(const std::string value);
    int hashFunc(const std::string key);
    void resize(int newSize);
    ~ChainHash();
};


#endif