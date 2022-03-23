#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<std::string> p(15);
    p.insert(27, "XX");
    p.insert(30, "YY");
    p.insert(20, "ZZ");
    p.insert(15, "AA");
    std::cout << p;
    std::cout << p.decreaseKey(30, 20) << '\n';
    std::cout << p.decreaseKey(30, 2) << '\n';
    std::cout << p.decreaseKey(27, 7) << '\n';
    std::cout << p;
}
