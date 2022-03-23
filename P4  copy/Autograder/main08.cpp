#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> ht(11);
    ht.insert(5, 20);
    ht.insert(4, 27);
    ht.insert(15, 35);
    ht.update(5, -5);
    ht.update(15, 40);
    std::cout << ht;
}
