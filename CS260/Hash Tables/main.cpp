#include <iostream>
#include "linearprobe.hpp"
#include "quadraticprober.hpp"
#include "doublehash.hpp"
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


int main()
{
    // QuadraticProbe<ProbeItem> map;
    // map.addItem({22});
    // map.addItem({56});
    // map.addItem({88});
    // map.addItem({26});
    // map.showtable();

    doubleprobe<ProbeItem> P({-1});
   P.addItem({22});
   P.addItem({33});
   P.addItem({52});
   P.addItem({11});
   P.removeItem({11});
   P.showtable();


}