#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<char> h(7);
    h.insert(0, '$');
    h.insert(12, 'x');
    h.insert(19, 'y');
    std::cout << h.remove(15) << '\n';
    std::cout << h.remove(0) << '\n';
    std::cout << h;
    std::cout << h.remove(19) << '\n';
    std::cout << h;
    std::cout << h.insert(19, 'a') << '\n';
    std::cout << h;
}
