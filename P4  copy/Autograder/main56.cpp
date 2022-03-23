#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p2(5);
    p2.insert(5, 10);
    p2.insert(3, 13);
    p2.insert(6, 12);
    PriorityQueue<int>& p1 = p2;
    int* p = p1.get(5);
    std::cout << *p << '\n';
    p = p1.get(6);
    std::cout << *p << '\n';
}
