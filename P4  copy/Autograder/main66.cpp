#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<char> p(20);
    for (unsigned i = 0; i < 20; ++i)
        p.insert(30 - i, 'A' + i);
    std::cout << p;
    std::cout << "---\n";
    p.remove(15);
    std::cout << p;
    std::cout << "---\n";
    p.remove(17);
    std::cout << p;
    std::cout << "---\n";
    std::cout << p.remove(29) << '\n';
    std::cout << p;
    std::cout << p.remove(3000) << '\n';
    std::cout << p.remove(29) << '\n';
}
