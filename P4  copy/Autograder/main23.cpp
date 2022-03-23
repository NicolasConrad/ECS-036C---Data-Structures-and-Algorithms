#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> h1(5), h2(5), h3(5);
    h1.insert(3, 100);
    h2.insert(3, 100);
    h3.insert(3, 100);
    h1.insert(32, 10);
    h2.insert(32, 10);
    h3.insert(32, 10);
    h1.insert(5, 12);
    h2.insert(5, 12);
    std::cout << (h1 == h2) << '\n';
    std::cout << (h2 == h1) << '\n';
    std::cout << (h1 == h3) << '\n';
    std::cout << (h3 == h2) << '\n';
}
