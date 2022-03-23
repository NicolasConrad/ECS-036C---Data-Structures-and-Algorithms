#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p(3);
    std::cout << p.deleteMin() << '\n';
    p.insert(3, 12);
    p.insert(11, 18);
    p.insert(15, -5);
    std::cout << p.deleteMin() << '\n';
    std::cout << p;
}
