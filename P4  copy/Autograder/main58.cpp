#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p2(10);
    p2.insert(3, -5);
    p2.insert(2, -10);
    const unsigned* minKey = p2.getMinKey();
    std::cout << *minKey << '\n';
    p2.insert(1, -15);
    minKey = p2.getMinKey();
    std::cout << *minKey << '\n';
}
