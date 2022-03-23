#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> h(5);
    std::cout << h.numElements() << '\n';
    h.insert(5, -3);
    h.insert(7, -2);
    h.insert(12, 40);
    std::cout << h.numElements() << '\n';
    h.remove(7);
    std::cout << h.numElements() << '\n';
}
