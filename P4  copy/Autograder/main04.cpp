#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<char> ht(11);
    std::cout << ht.insert(3, 'x') << '\n';
    std::cout << ht.insert(25, 'b') << '\n';
    std::cout << ht.insert(3, 'y') << '\n';
    std::cout << ht.insert(14, 'a') << '\n';
    std::cout << ht;
}
