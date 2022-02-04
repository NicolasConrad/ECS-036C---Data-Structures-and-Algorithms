#include "array.hpp"
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    Array<int, 3> vals;
    vals.at(0) = 18;
    vals.at(1) = 55;
    vals.at(2) = 49;
    std::cout << "Length: " << vals.size() << '\n';
    std::cout << vals;
    std::cout << "Front: " << vals.front() << '\n';
    std::cout << "Back: " << vals.back() << '\n';

    // This would cause a compiler error because i is a variable and is thus
    // not considered known at compile time.
    // unsigned i = 0;
    // get<i>(vals) = 54;

    Array<int, 2> vals2;
    vals2.at(0) = 35;
    vals2.at(1) = 45;
    std::cout << "Length: " << vals2.size() << '\n';
    std::cout << vals2;

    // This line causes a compiler error, because Array<int, 3> and
    // Array<int, 2> are NOT the same type!!
    // std::cout << (vals == vals2) << '\n';

    Array<int, 2> vals3;
    vals3.at(0) = 35;
    vals3.at(1) = 50;
    // Here, vals2 and vals3 are of the same type, namely Array<int, 2>.
    std::cout << (vals2 == vals3) << '\n';
    std::cout << (vals2 != vals3) << '\n';

    Array<std::string, 3> strs;
    get<0>(strs) = "Hello";
    get<1>(strs) = "there";
    get<2>(strs) = "world";
    std::cout << strs;

    // This line SHOULD cause a compiler error.
    // get<3>(strs) = "blah";

    // This SHOULD cause a compiler error.
    // Array<int, 0> vals4;
    // std::cout << vals4;
}
