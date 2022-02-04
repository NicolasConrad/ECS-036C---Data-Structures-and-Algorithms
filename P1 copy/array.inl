// TODO: Implement the methods of class Array here or in the header file.
#include "array.hpp"
#include <cassert>
#include<stdexcept>

//constructors
template <typename T, std::size_t Length>
Array<T, Length>::Array() {}


template <typename T, std::size_t Length>
Array<T, Length>::~Array() {}


template <typename T, std::size_t Length>
Array<T, Length>::Array(const Array& other)
{
    for(unsigned i = 0; i < Length; i++)
        arr[i] = other.at(i);
}

template <typename T, std::size_t Length>
Array<T, Length>& Array<T, Length>::operator=(const Array& other)
{
    for(unsigned i = 0; i < Length; i++)
        arr[i] = other.at(i);
    return *this;
}

// For your convenience, I show you a bit of what the definition of the size()
// method looks like below.

template <typename T, std::size_t Length>
std::size_t Array<T, Length>::size() const
{
    // TODO: Implement.
    return Length;
}

//front
template <typename T, std::size_t Length>
const T& Array<T, Length>::front() const
{
    return arr[0];
}

//back
template <typename T, std::size_t Length>
const T& Array<T, Length>::back() const
{
    return arr[Length - 1];
}

//at 
template <typename T, std::size_t Length>
T& Array<T, Length>::at(std::size_t index)
{
    if(index < 0 || index >= Length)
        throw std::out_of_range("");
    return arr[index];
}

//at const
template <typename T, std::size_t Length>
const T& Array<T, Length>::at(std::size_t index) const
{
    if(index < 0 || index >= Length)
        throw std::out_of_range("");
    return arr[index];
}

//operator ==
template <typename T, std::size_t Length>
bool Array<T, Length>::operator==(const Array& other) const
{
    for(unsigned i = 0; i < Length; i++)
    {
        if(arr[i] != other.at(i))
            return false;
    }
    return true;
}

//operator !=
template <typename T, std::size_t Length>
bool Array<T, Length>::operator!=(const Array& other) const
{
    for(unsigned i = 0; i < Length; i++)
    {
        if(arr[i] != other.at(i))
            return true;
    }
    return false;
}

/**
 * Here, Index must come before T and Length in the `template < ... >` line.
 * I'm not sure why; I just know the compiler wants it that way.
 */

template <std::size_t Index, typename T, std::size_t Length>
T& get(Array<T, Length>& array)
{
    // TODO: Provide a static assertion that causes compilation to fail
    // if the given index is out of range.
    static_assert(Index >= 0, "Index out of range");
    static_assert(Index < Length, "Index out of range");
    // TODO: Retrieve the element.
    return array.at(Index);

}

// TODO: Implement the const overload of get(), either here or in the header
// file.
template <std::size_t Index, typename T, std::size_t Length>
const T& get(const Array<T, Length>& array)
{
    static_assert(Index >= 0, "Index out of range");
    static_assert(Index < Length, "Index out of range");
    return array.at(Index);
}


// TODO: Implement operator<<, either here or in the header file.
template <typename T, std::size_t Length>
std::ostream& operator<<(std::ostream& os, const Array<T, Length>& array)
{
    for(unsigned i = 0; i < Length; i++)
        os << array.at(i) << " ";
    os << "\n";
    return os;
}











