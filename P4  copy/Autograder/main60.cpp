#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<int> p2(10);
    p2.insert(3, -5);
    p2.insert(2, -10);
    const int* minValue = p2.getMinValue();
    std::cout << *minValue << '\n';
    p2.insert(1, -15);
    minValue = p2.getMinValue();
    std::cout << *minValue << '\n';
}
