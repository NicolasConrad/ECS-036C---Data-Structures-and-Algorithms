#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<std::string> ht1(11);
    ht1.insert(5, "abc");
    ht1.insert(19, "def");
    ht1.insert(33, "hello");
    ht1.insert(30, "blah");
    ht1.insert(16, "there");
    HashTable<std::string> ht2(47);
    ht2.insert(5, "abc");
    ht2.insert(19, "def");
    ht2.insert(33, "hello");
    ht2.insert(30, "blah");
    ht2.insert(16, "there");
    std::cout << ht1;
    std::cout << ht2;
}
