#include "hash_table.hpp"
#include <iostream>

int main()
{
    HashTable<int> ht(11);
    std::cout << ht;
    std::cout << "Done printing ht...\n";
}
