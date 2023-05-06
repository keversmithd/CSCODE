#ifndef STRING_HASH_H
#define STRING_HASH_H
#include <string>
#include <iostream>
bool isPrime(int value);
int nextPrime(int value);

class StringHash //A linear probing method for hash mapping.
{
private:
    std::string* hashData;
    int capacity;
    int size;
public:
    StringHash(int preferredSize = 0);
    void addItem(const std::string value);
    bool findItem(const std::string value);
    std::string displayTable();
    void removeItem(const std::string value);
    void resize();
    int hashFunc(const std::string key);
    ~StringHash();
};

#endif