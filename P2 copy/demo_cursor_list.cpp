#include "cursor_list.hpp"

#include <iostream>

int main()
{
    int l1 = clCreate();
    int l2 = clCreate();
    int l3 = clCreate();
    std::cout << clLength(l3) << ' ' << clIsEmpty(l3) << '\n';  // 0 1
    printSlots(0, 7);
    std::cout << "==========\n";
    clAppend(l1, 10);
    clAppend(l2, 20);
    clAppend(l3, 30);
    clAppend(l1, 40);
    std::cout << clLength(l1) << ' ' << clIsEmpty(l1) << '\n';  // 2 0
    std::cout << clFind(l1, 30) << '\n';  // 0
    std::cout << clFind(l1, 40) << '\n';  // 7
    printSlots(0, 10);
    std::cout << "**********\n";
    clInsert(clFind(l1, 10), 50);
    clInsert(clFind(l1, 10), 60);
    clPrint(l1);  // 10 60 50 40
    std::cout << "$$$$$$$$$$\n";
    clDelete(l1, 50);
    clPrint(l1);  // 10 60 40
    std::cout << clLength(l1) << '\n';  // 3
    std::cout << "@@@@@@@@@@\n";
    int l4 = clCopy(l1);
    clPrint(l4);
    std::cout << "&&&&&&&&&&\n";
    printSlots(0, 30);
    std::cout << "##########\n";
    std::cout << "Free list:\n";
    clPrint(0);
    clDestroy(l1);
    printSlots(0, 15);
    std::cout << "~~~~~~~~~~\n";
    std::cout << "Free list: (data doesn't matter)\n";
    clPrint(0);
    std::cout << "!!!!!!!!!!\n";
    clAppend(l4, 70);
    clInsert(l4, 80);  // insert at front
    std::cout << "Before reverse:\n";
    clPrint(l4);  // 80 10 60 40 70
    std::cout << "After reverse:\n";
    clReverse(l4);  // 70 40 60 10 80
    clPrint(l4);
}
