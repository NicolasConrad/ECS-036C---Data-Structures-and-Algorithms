#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<std::string> ht(7);
    ht.insert(15, "abc");
    ht.insert(8, "abcd");
    ht.insert(22, "abc");
    std::cout << ht.removeAllByValue("abc") << '\n';
    std::cout << ht;
}
