#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<std::string> h(7);
    h.insert(3, "abc");
    h.insert(10, "def");
    h.insert(17, "ghi");
    HashTable<std::string> h2(7);
    h2.insert(17, "ghi");
    h2.insert(10, "def");
    h2.insert(3, "abc");
    std::cout << (h == h2) << '\n';
    h2.remove(10);
    std::cout << (h == h2) << '\n';
    h.remove(10);
    std::cout << (h == h2) << '\n';
}
