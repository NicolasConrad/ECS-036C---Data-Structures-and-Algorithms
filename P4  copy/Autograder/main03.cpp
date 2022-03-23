#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<std::string> ht(7);
    std::cout << ht.insert(52, "Hello") << '\n';
    std::cout << ht.insert(45, "AA") << '\n';
    std::cout << ht.insert(46, "BB") << '\n';
    std::cout << ht;
}
