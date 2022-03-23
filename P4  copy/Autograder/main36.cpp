#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<std::string> h1(5);
    h1.insert(4, "alligator");
    h1.insert(2, "crocodile");
    HashTable<std::string> h2(7);
    h2.insert(7, "rabbit");
    h2 = h1;
    h2.insert(7, "spider");
    std::cout << h1;
    std::cout << h2;
    std::cout << h2.numElements() << '\n';
}
