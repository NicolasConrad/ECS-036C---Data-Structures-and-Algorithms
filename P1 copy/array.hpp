#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <ostream>

/**
 * Array of a fixed length.
 */
/**
 * std::size_t is a C++ alternative to the size_t type from C.
 * size_t is typically used when referring to anything that is a quantity
 * related to memory, such as the length of an array (which is in memory).
 * It is an unsigned integer type and is typically (but not always) a typedef
 * for something like unsigned or long unsigned.
 * (If you think this is complicated, then you should look up size_type.)
 */
template <typename T, std::size_t Length>
class Array
{
public:
    /**
     * TODO: Provide a static assertion here that will prohibit arrays
     * of length 0.
     */
    static_assert(Length != 0, "Length cannot be 0");

    Array();
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other);

    /**
     * Returns the size of the array.
     */
    std::size_t size() const;

    /**
     * Returns the first or last element of the array.
     *
     * Ideally, there would be non-const overloads for these too.
     */
    const T& front() const;
    const T& back() const;

    /**
     * Returns the element of the array that is at the given index.
     * Throws std::out_of_range if index is out of range.
     */
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    /**
     * Equality checking, i.e. checking if two arrays contain the exact
     * same elements.
     */
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

private:
    // TODO: Your member variables and helper methods go here.
    T arr[Length];

};

/**
 * Returns the element of the array that is at the given index.
 * Causes compilation to fail (with a static assertion) if index is out
 * of range.
 */
template <std::size_t Index, typename T, std::size_t Length>
T& get(Array<T, Length>& array);
template <std::size_t Index, typename T, std::size_t Length>
const T& get(const Array<T, Length>& array);

/**
 * Prints each element of the array.
 */
template <typename T, std::size_t Length>
std::ostream& operator<<(std::ostream& os, const Array<T, Length>& array);

#include "array.inl"
#endif  // ARRAY_HPP
