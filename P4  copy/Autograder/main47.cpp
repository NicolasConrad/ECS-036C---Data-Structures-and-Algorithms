#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p1(5);
    p1.insert(5, 10);
    p1.insert(3, 13);
    p1.insert(6, 12);
    PriorityQueue<int> p2(10);
    p2.insert(3, -5);
    p2.insert(2, -10);
    p2.insert(1, -15);
    std::cout << p2.insert(2, -15) << '\n';
    PriorityQueue<int> p3(5);
    p3.insert(10, -10);
    p3.insert(5, -15);
    p3.insert(3, -20);
    p3.insert(2, 0);
    std::cout << p1 << p2 << p3;
}
