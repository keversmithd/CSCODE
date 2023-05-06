#ifndef HASH_CODE_H
#define HASH_CODE_H
#include <random>
#include <cmath>
#include "ran.hpp"


inline bool isPrime(int value)
{
    if (value <= 1)  return false; //if the value is less than 1 return false.
    if (value <= 3)  return true; //if the value is greater than 1 and less than or equal to three , so basically 2 and 3 return true.

    if (value%2 == 0 || value%3 == 0) return false; //other wise if the number is divisble by two or three return false.
   
    for (int i=5; i*i<=value; i=i+6) //tbh don't even understand this, i guess it checks divisibliity of other prime numbers up until value
        if (value%i == 0 || value%(i+2) == 0)
           return false;
   
    return true;
}

inline int previousPrime(int value)
{


    if(value <= 2)
    {
        throw std::out_of_range("prime less than two");
    }
    if(value == 3) return 2;
    if(value == 5) return 3;

    value = ((value-1) % 2 == 0) ? value-2 : value-1;

    while(!isPrime(value))
    {
        value -= 2;
    }
    return value;
}

inline int nextPrime(int value)
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

int combineHashCodes(int h1, int h2)
{
    int hash = 17;
    hash = 31 * hash + h1;
    hash = 31 * hash + h2;
    return hash;
}

int hash(int x)
{
    int w = sizeof(x)*8;
    int tw = pow(2,32);
    uint64_t z = (x * 2654435761);
    int hc = z % tw;
    return  hc;
}

int hashCoded(double value)
{
    long bits = static_cast<long>(value);
    int high = (int)(bits >> 32);
    int low = (int)bits;
    return combineHashCodes(high, low);
}

struct Compound_P
{
    double p;
    double q;

    int hashCode()
    {
        long unsigned int z[] = {0x2058cc50L, 0xcb19137eL};
        long long unsigned int zz = 0xbea0107e5067d19dL;

        long h0 = hashCoded(p);
        long h1 = hashCoded(q);
        
        return (int)(((z[0] * h0 + z[1] * h1) * zz) >> 32);
    }
};

int modvs(int k, int m)
{

    double a = sizeof(k)*8;
    double b = (m/2);
    double c = m;
    double e = 2.71828;

    return static_cast<long long int>(a*e*( (pow((k-b),2))/(2*pow(c,2)) )) % m;



    

    
}

int guas_hash(int k, int m)
{
    std::default_random_engine generator(k);
    std::normal_distribution<double> distribution(0.0, 1.0);

    double random_number = distribution(generator);

    double exponent = -std::pow(random_number, 2.0)/2.0;
    double gaussian_value = std::exp(exponent);

    return static_cast< int>(std::round(gaussian_value * m)) % m;
}

int multiplicationMethod(int k, int m)
{
    uint8_t w = sizeof(k) * 8;
    
    double A = 0.5*(sqrt(5)-1);
    double s = k*A;
    double intpart;
    double x = modf(s, &intpart);
    double mx = m*x;
    int hk = floor(mx);

    return hk;
}




#endif