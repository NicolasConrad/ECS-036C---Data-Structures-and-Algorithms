#include "array.hpp"
#include <iostream>
int main()
{
    Array<int, 1> arr1;
    arr1.at(0) = 15;
    std::cout << arr1;
    Array<float, 2> arr2;
    arr2.at(0) = 13.4f;
    arr2.at(1) = 27.85f;
    try
    {
        arr2.at(2) = 100.3f;
        std::cout << "Did not encounter any exceptions.\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected out_of_range exception.\n";
    }
    catch (...)
    {
        std::cout << "Caught unexpected kind of exception.\n";
    }
}
