#include "hash_table.hpp"
#include <iostream>

int main()
{
    std::cout << (HashTable<int>(5) == HashTable<int>(7)) << '\n';
    HashTable<std::string> h(7);
    std::cout << (h == h) << '\n';
    HashTable<std::string> h2(7);
    h.insert(5, "abc");
    h2.insert(5, "def");
    std::cout << (h == h2) << '\n';
}
