#include "StringHash.hpp"

StringHash::StringHash(int preferredSize) : hashData(nullptr), capacity(7), size(0)
{
    //Sets hashdata to nullptr, capacity to seven, and size to zero.
    if(preferredSize == 0)
    {
        resize();
    }
}
void StringHash::resize()
{
    //will resize the list to the next prime function.
    int storage = nextPrime(capacity);
    std::string* memBuffer = new std::string[storage]; 
    capacity = storage;

    for(int i = 0; i < capacity; i++)
    {
        memBuffer[i] = "UNKNOWN";
    }

    int hashIndex, encircledOnce, done, found;

    //will then re insert all elements using the insertion algorithm.
    int preffSize = size;
    for(int i = 0; i < preffSize; i++)
    {
        //printf("value: %s\n", hashData[i].c_str());
        if(hashData[i] != "UNKNOWN")
        {
            hashIndex = hashFunc(hashData[i]);
            encircledOnce = false;
            done = false;
            found = true;

            while(memBuffer[hashIndex] != "UNKNOWN" && done == false)
            {
                if(hashIndex == capacity-1)
                {
                    if(encircledOnce == false)
                    {
                        hashIndex = 0;
                        encircledOnce = true;
                    }else
                    {
                        done = true;
                        found = false;
                    }
                }

                if(done == false)
                {
                    hashIndex++;
                }
                
            }

            if(found == true)
            {
                memBuffer[hashIndex] = hashData[i];
            }
        }else
        {
            preffSize++;
        }
        

    }

    if(hashData != nullptr && hashData != memBuffer)
    {
        delete[] hashData;
    }
    
    hashData = memBuffer;

}
void StringHash::addItem(const std::string value)
{
    //If the appension of one element will be greater than capaicty resize the array.
    if(size+1 > capacity/2)
    {
        resize();
    }

    int hashIndex = hashFunc(value);
    bool encircledOnce = false;
    bool done = false;
    bool found = true;

    //If the hashed index location is marked unknown then search linearly along the array, and even looping the array until an avaiable location is found.
    while(hashData[hashIndex] != "UNKNOWN" && done == false)
    {
        

        if(hashIndex == capacity-1)
        {
            if(encircledOnce == false)
            {
                hashIndex = 0;
                encircledOnce = true;
            }else
            {
                done = true;
                found = false;
            }
        }

        if(done == false)
        {
            hashIndex++;
        }
        
    }

    if(found == true)
    {
        hashData[hashIndex] = value;
        size++;
    }

    
}
bool StringHash::findItem(const std::string value)
{
    //Will select hash funciton of item, if the value at that location is not the value it will keep searching until encircled completely once, then it will return false if not found.
    int hashIndex = hashFunc(value);
    bool encircledOnce = false;
    bool done = false;
    bool found = true;

    while(hashData[hashIndex] != value && done == false)
    {
        if(hashIndex == capacity-1)
        {
            if(encircledOnce == false)
            {
                hashIndex = 0;
                encircledOnce = true;
            }else
            {
                done = true;
                found = false;
            }
        }

        if(done == false)
        {
            hashIndex++;
        }
        
    }

    return found;
}
void StringHash::removeItem(const std::string value)
{
    //will use the find algorithm and then set that value to unknown if it does find other wise, it will just loop around and return.
    int hashIndex = hashFunc(value);
    bool encircledOnce = false;
    bool done = false;
    bool found = true;

    while(hashData[hashIndex] != value && done == false)
    {
        if(hashIndex == capacity-1)
        {
            if(encircledOnce == false)
            {
                hashIndex = 0;
                encircledOnce = true;
            }else
            {
                done = true;
                found = false;
            }
        }

        if(done == false)
        {
            hashIndex++;
        }
        
    }

    if(found == true)
    {
        hashData[hashIndex] = "UNKNOWN";
        size--;
    }

    
}
std::string StringHash::displayTable()
{
    //Appends each value of the array to the string and returns string.
    std::string tableData;
    for(int i = 0; i < capacity; i++)
    {
        tableData += hashData[i] + ", ";
    }
    tableData += "\n";
    return tableData;
}
bool isPrime(int value)
{
    if (value <= 1)  return false; //if the value is less than 1 return false.
    if (value <= 3)  return true; //if the value is greater than 1 and less than or equal to three , so basically 2 and 3 return true.

    if (value%2 == 0 || value%3 == 0) return false; //other wise if the number is divisble by two or three return false.
   
    for (int i=5; i*i<=value; i=i+6) //tbh don't even understand this, i guess it checks divisibliity of other prime numbers up until value
        if (value%i == 0 || value%(i+2) == 0)
           return false;
   
    return true;
}

int nextPrime(int value)
{
    if (value <= 1)
        return 2;
 
    int prime = value;
    bool found = false;

    //Will increment value until it is prime.

    while (!found) {
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}



int StringHash::hashFunc(const std::string key)
{
    //provided by jim bailey and team.
    int hashValue = 0;

    for(int i = 0; i < key.length(); i++)
    {
        hashValue *= 128;
        hashValue += key[i];
        hashValue %= capacity;
    }

    return hashValue;
}

StringHash::~StringHash()
{
    //deletes the data if it exists.
    if(hashData != nullptr)
    {
        delete[] hashData;
    }
}