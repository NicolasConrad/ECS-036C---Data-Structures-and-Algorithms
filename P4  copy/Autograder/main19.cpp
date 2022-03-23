#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<bool> h(11);
    h.insert(52, true);
    h.insert(35, false);
    h.insert(72, true);
    h.insert(32, false);
    std::cout << h.removeAllByValue(false) << '\n';
    std::cout << h.removeAllByValue(false) << '\n';
}
