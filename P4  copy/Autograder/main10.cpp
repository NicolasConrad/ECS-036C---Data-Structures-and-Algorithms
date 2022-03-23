#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> ht(7);
    ht.insert(5, 20);
    ht.insert(4, 27);
    ht.insert(15, 35);
    ht.update(5, -5);
    int* p = ht.get(5);
    if (p) std::cout << *p << '\n';
    else std::cout << "Got null pointer.\n";
    p = ht.get(4);
    if (p) std::cout << *p << '\n';
    else std::cout << "Got null pointer.\n";
}
