#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<char> h1(11);
    h1.insert(3, 'x');
    h1.insert(5, 'y');
    HashTable<char> h2(11);
    h2.insert(11, 'a');
    h2.insert(4, 'b');
    h2.insert(14, 'c');
    h2.insert(5, 'd');
    std::cout << h1 + h2;
    std::cout << h1;
    std::cout << h2;
}
