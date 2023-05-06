#ifndef PRIME_QUES
#define PRIME_QUE
#include <iostream>
#include "linearprobe.hpp"
#include "quadraticprober.hpp"
#include <vector>
struct ProbeItem
{
    int p;

    int hashCode()
    {
        return hash(p);
    }

    bool operator !=(ProbeItem A)
    {
        return p != A.p;
    }
    bool operator ==(ProbeItem B)
    {
        return p == B.p;
    }
    friend std::ostream& operator<<(std::ostream& os, const ProbeItem& dt);
};


std::ostream& operator<<(std::ostream& os, const ProbeItem& dt)
{
    os << dt.p;
    return os;
}

void primeQuest()
{
    LinearProbe<ProbeItem> uniqueSkips;


    int lastprime = 2;
    int prime = 3;
    
    for(int i = 0; i < 1000; i++)
    {
        if(!uniqueSkips.findItem({(prime-lastprime)}))
        {
            uniqueSkips.addItem({(prime-lastprime)});
        }
        //printf("%d, ", (prime-lastprime));
        if(i % 10 == 0)
        {
            //printf("\n");
        }
        lastprime = prime;
        prime = nextPrime(prime);
        
    }

    uniqueSkips.showthere();

    //todo, measure periodicity of unqiue skips show up in the set
    //todo, measure a subset which measures common sequences
    //todo, measure the relative index of the sequence(besides the number)

    
}

#endif