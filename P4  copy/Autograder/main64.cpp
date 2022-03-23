#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p(30);
    for (unsigned i = 0; i < 12; ++i)
        p.insert(100 + i, -5 - (int) i);
    p.deleteMin();
    p.decreaseKey(110, 80);
    std::cout << p;
    p.increaseKey(30, 80);
    std::cout << p;
}
