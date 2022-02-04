#include "cursor_list.hpp"

#include <iostream>

int main()
{
    
    unsigned c1 = clCreate();
    unsigned c2 = clCreate();
    for (unsigned i = 0; i < 5; ++i)
    {
        clAppend(c1, 5);
        clInsert(c1, 10);
        clAppend(c2, 5);
        clInsert(c2, 10);
    }
    printSlots(0, 30);
    std::cout << clDeleteAll(c2, 10) << '\n';
    printSlots(0, 30);
    std::cout << clDeleteAll(c2, 10) << '\n';
    clPrint(c1);
    clPrint(c2);
}