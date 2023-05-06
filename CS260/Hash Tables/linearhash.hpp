#ifndef LINHASH_H
#define LINHASH_H
#include "ran.hpp"
#include <vector>
#include <cstring>


//tabulated hashing

//uses d = log2(t.capacity())
//uses int mat[4][256] filled with random numbers

// int h = x.hashCode();
// return (tab[0][h&0xff]
// ˆ tab[1][(h>>>8)&0xff]
// ˆ tab[2][(h>>>16)&0xff]
// ˆ tab[3][(h>>>24)&0xff])
// >>> (w-d);

template<typename T>
struct LinearHash
{
    T* t;
    uint64_t z;
    T def;
    int capacity;
    int n,d,q;
    LinearHash() : t(nullptr), n(0), d(0), q(0), z(dis(gen)), capacity(0)
    {
        def = T();
        resize();
    }
    T find(T x, bool& found)
    {
        int i = hash(x);
        while(t[i] != def)
        {
            if(x == t[i])
            {
                found = true;
                return t[i];
            }
            i = (i == capacity - 1) ? 0 : i + 1;
        }
        found = false;
        return T();
    }

    bool add(T x)
    {
        if(n != 0)
        {
            bool found;
            find(x, found);
            if(found != false) return false;
        }
        if(2*(q+1) > capacity) resize();
        int i = hash(x);
        while(t[i] != def)
        {
            i = (i==capacity-1) ? 0 :  i + 1;
        }
        if(t[i] == def) q++;
        n++;
        t[i] = x;
        return true;

    }

    T remove(T x)
    {
        int i = hash(x);
        while(t[i] != def)
        {
            T y = t[i];
            if(x == y)
            {
                t[i] = def;
                n--;
                if(8*n < capacity) resize();
                return y;
            }
            i = (i == capacity-1) ? 0 : i + 1;
        }
        return T();
    }

    void resize()
    {
        d = 1;
        while((1<<d) < 3*n) d++;
        T* mt = new T[(1<<d)];
        std::memset(mt, def, (1<<d)*sizeof(T));
        capacity = (1<<d);
        q = n; 

        int tn = n;
        for(int j = 0; j < tn; j++)
        {
            T value = t[j];
            if(t[j] == def)
            {
                tn++;
            }else
            {
                int i = hash(value);
                while(mt[i] != def)
                {
                    i = (i==capacity-1) ? 0 :  i + 1;
                }
                mt[i] = value;
            }
        }

        if(t != nullptr && mt != t)
        {
            delete[] t;
        }
        t = mt;
        
    }

    int hash(T x)
    {
        double d = log2(capacity);
        int w = 32;
        double twow = pow(2,32);
        uint64_t t = static_cast<uint64_t>(twow);
        
        z = z % (t-1);
        if(z % 2 == 0)
        {
            z += 1;
        }
        uint64_t modvalue = ((z*x) % t);
        uint64_t wd = (w-d);
        uint64_t modex = modvalue >> (w-(uint64_t)d);
        return modex;
    }
};

#endif