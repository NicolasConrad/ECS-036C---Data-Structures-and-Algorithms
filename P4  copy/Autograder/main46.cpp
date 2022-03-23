#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<std::string> p(3);
    std::cout << p.insert(5, "AA") << '\n';
    std::cout << p.insert(10, "BB") << '\n';
    std::cout << p.insert(8, "CC") << '\n';
    std::cout << p.insert(20, "DD") << '\n';
    std::cout << p;
}
