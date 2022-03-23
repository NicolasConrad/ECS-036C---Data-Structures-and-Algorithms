#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<std::string> p(100);
    bool toggle = false;
    for (unsigned key = 20; key > 5; --key)
    {
        if (toggle) p.insert(key, "hey");
        else p.insert(key, "hi");
        toggle = !toggle;
    }
    std::cout << p;
    for (unsigned key = 9; key <= 13; ++key)
        p.remove(key);
    std::cout << p;
}
