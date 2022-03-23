#include "priority_queue.hpp"
#include <iostream>

int main()
{
    PriorityQueue<char> x(9);
    x.insert(5, 'a');
    x.insert(7, 'b');
    x.insert(17, 'b');
    x.insert(6, 'b');
    x.insert(3, 'b');
    x.insert(12, 'b');
    x.insert(10, 'b');
    x.insert(1, 'b');
    x.deleteMin();
    std::cout << x.numElements() << '\n';
    x.deleteMin();
    std::cout << x.numElements() << '\n';
    x.deleteMin();
    std::cout << x.numElements() << '\n';
}
