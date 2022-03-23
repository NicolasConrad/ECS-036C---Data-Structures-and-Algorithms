#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<char> h(3);
    h.insert(15, 'x');
    h.insert(22, 'y');
    std::cout << h;
    h.insert(39, 'a');
    h.insert(32, 'b');
    std::cout << h;
}
