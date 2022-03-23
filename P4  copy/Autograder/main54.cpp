#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p1(5);
    p1.insert(5, 10);
    p1.insert(3, 13);
    p1.insert(6, 12);
    int* p = p1.get(5);
    *p = -100;
    p = p1.get(6);
    *p = -200;
    std::cout << p1;
}
