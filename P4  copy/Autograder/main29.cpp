#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> h(5);
    std::cout << h.tableSize() << '\n';
    h.insert(3, 5);
    h.insert(10, -2);
    h.insert(10, -3);
    std::cout << h.tableSize() << '\n';
    HashTable<int> h2(3);
    std::cout << h2.tableSize() << '\n';
}
