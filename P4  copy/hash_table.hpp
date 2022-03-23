#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include<memory>
#include<ostream>


/**
 * Implementation of a hash table that stores key-value
 * pairs mapping unsigned integers to instances of
 * ValueType.
 *
 * Hash function: key % tableSize
 * Collision resolution: quadratic probing.
 * Non-unique keys are not supported.
 *
 * Any use of the term "element" refers to a key-value pair.
 *
 * Some functions have runtime requirements.
 * During lecture, I mentioned that when talking about hash
 * tables, people tend to talk as if common hash table
 * operations take constant time, even though this is false.
 * Here, any mention of "constant time" in double quotes means
 * "amortized constant time on average", i.e. you should
 * use hashing to speed things up and not iterate through
 * all the buckets, ignoring the hash function. For instance,
 * it is required that you implement delete() in "constant
 * time", so you cannot take the inefficient approach of
 * searching for the relevant key by iterating 
 * bucket-by-bucket.
 *
 * The table rehashes whenever the insertion of a new
 * element would put the load factor at at least 1/2.
 * (The rehashing is done before the element would've been inserted.)
 * Upon a rehash, the table size (let's call it m) should
 * be increased to the lowest prime number that is greater
 * than or equal to 2m. Elements are then transferred
 * from the "old table" to the "new/larger table" in the
 * order in which they appear in the old table, and then
 * the new element is finally inserted.
 */
template <typename ValueType>
struct bucket
{
    unsigned key;
    bool isDeleted;
    bool empty = true;
    ValueType value;
};

bool isPrime(int num)
{
    for(int i = 2; i <= num/2; i++)
    {
        if(num % i == 0)
            return false;
    }

    return true;
}


int nextPrime(int num)
{
    while(!isPrime(num))
        num++;

    return num;
}

template <typename ValueType>
class HashTable
{
public:
    /**
     * Creates a hash table with the given number of
     * buckets/slots.
     *
     * Throws std::runtime_error if @tableSize is 0 or not
     * prime.
     */
    explicit HashTable(unsigned tableSize);

    ~HashTable();

    /**
     * Makes the underlying hash table of this object look
     * exactly the same as that of @rhs.
     */
    HashTable(const HashTable& rhs);
    HashTable& operator=(const HashTable& rhs);

    /**
     * Takes the underlying implementation details of @rhs
     * and gives them to "this" object.
     * After this, @rhs should be in a "moved from" state.
     */
    HashTable(HashTable&& rhs) noexcept;
    HashTable& operator=(HashTable&& rhs) noexcept;

    /**
     * Both of these must run in constant time.
     */
    unsigned tableSize() const;
    unsigned numElements() const;

    /**
     * Prints each bucket in the hash table.
     * See prog_hw4.pdf for how exactly this should look.
     *
     * I don't think that a friend of a templated class can
     * be defined outside of the class. If you can figure
     * out how to do that in a way that works on the CSIF,
     * go for it.
     */
    friend std::ostream& operator<<(std::ostream& os,
                                    const HashTable<ValueType>& ht)
    {
        // TODO: Implement this method.
        for(unsigned i = 0; i < ht.size; i++)
        {
            if(ht.arr[i].empty)
                os << "Bucket " << i << ": " << "(empty)" << std::endl;
            else
                os << "Bucket " << i << ": " << ht.arr[i].key << " -> " << ht.arr[i].value << std::endl;
        }
   
        return os;
    }

    /**
     * Inserts a key-value pair mapping @key to @value into
     * the table.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key is already in the table
     * (in which case, the insertion is not performed).
     */
    bool insert(unsigned key, const ValueType& value);

    /**
     * Finds the value corresponding to the given key
     * and returns its address.
     *
     * This function must run in "constant time".
     *
     * Returns null pointer if @key is not in the table.
     */
    ValueType* get(unsigned key);
    const ValueType* get(unsigned key) const;

    /**
     * Updates the key-value pair with key @key to be
     * mapped to @newValue.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key is not in the table.
     */
    bool update(unsigned key, const ValueType& newValue);

    /**
     * Deletes the element that has the given key.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key not found.
     */
    bool remove(unsigned key);

    /**
     * Deletes all elements that have the given value.
     *
     * Returns the number of elements deleted.
     */
    unsigned removeAllByValue(const ValueType& value);

    /**
     * Two instances of HashTable<ValueType> are considered 
     * equal if they contain the same elements, even if those
     * elements are in different buckets (i.e. even if the
     * hash tables have different sizes).
     */
    bool operator==(const HashTable& rhs) const;
    bool operator!=(const HashTable& rhs) const;

    /**
     * Returns a newly constructed hash table that is the hash table
     * that would result from inserting each element from @rhs
     * (in the order that they appear in the buckets)
     * into this (i.e. *this) hash table.
     */
    HashTable operator+(const HashTable& rhs) const;


private:
    // TODO: Your members here.
    std::unique_ptr<bucket<ValueType>[]> arr;
    unsigned size;
    unsigned elements;
};

#include "hash_table.inl"
#endif  // HASH_TABLE_HPP
