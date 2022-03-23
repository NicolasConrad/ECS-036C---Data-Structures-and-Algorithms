#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p3(5);
    p3.insert(10, -10);
    p3.insert(5, -15);
    p3.insert(3, -20);
    p3.insert(2, 0);
    PriorityQueue<int> p4(p3);
    std::cout << p4;
    p4.remove(5);
    std::cout << p4;
    std::cout << p3;
}
