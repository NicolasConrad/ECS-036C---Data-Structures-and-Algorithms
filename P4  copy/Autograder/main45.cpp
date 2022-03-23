#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<std::string> p1(20);
    std::cout << p1.maxSize() << '\n';
    PriorityQueue<std::string> p2(30);
    std::cout << p2.maxSize() << '\n';
}
