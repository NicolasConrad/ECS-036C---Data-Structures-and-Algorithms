#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> h1(5);
    h1.insert(10, -5);
    h1.insert(20, -10);
    h1.remove(10);
    auto h2 = h1;
    std::cout << (h1.get(20) == nullptr) << '\n';
    std::cout << (h2.get(20) == nullptr) << '\n';
    std::cout << (h2.get(10) == nullptr) << '\n';
    std::cout << h2;
}
