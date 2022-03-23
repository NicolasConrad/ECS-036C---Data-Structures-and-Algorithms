#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> ht(7);
    ht.insert(5, 20);
    ht.insert(4, 27);
    ht.insert(15, 35);
    ht.update(5, -5);
    const HashTable<int>& constHt = ht;
    const int* p = constHt.get(5);
    if (p) std::cout << *p << '\n';
    else std::cout << "Got null pointer.\n";
    p = constHt.get(4);
    if (p) std::cout << *p << '\n';
    else std::cout << "Got null pointer.\n";
}
