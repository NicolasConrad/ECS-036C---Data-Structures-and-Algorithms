#ifndef CURSOR_LIST_HPP
#define CURSOR_LIST_HPP


/**
 * Cursor space functions.
 *
 * "Header node" refers to the node used to indicate the start of the list.
 * Such a node's data is arbitrary; none of your functions should ever care
 * about the data member of a header node.
 *
 * A "node" refers to an occupied/"allocated" slot.
 */


/**
 * During lecture, the version of cursor_list.hpp that was shown had the macro
 * NUM_SLOTS and the definitions of struct Slot and the SLOTS array here.
 * Since defining an array in a header file tends to lead to a linker error
 * in C++, I moved these lines of code to cursor_list.cpp.
 */


/**
 * "Allocates" a slot that is not currently allocated and returns its index.
 * The very first time that this function is called, the "free list" must be
 * set up, since -- initially -- all of the slots' next members are 0.
 *
 * Does NOT perform any real dynamic memory allocation; malloc(), realloc(),
 * and new are prohibited!
 * Selects the first available node on the "free list", i.e. SLOTS[0].next.
 *
 * The autograder will not check if the next member of the allocated node is 0.
 *
 * Throws std::runtime_error exception if no more available slots.
 */
unsigned slotAlloc();


/**
 * "Deallocates" the slot/node that is at @index.
 * Does NOT perform any real dynamic memory deallocation; free() and delete
 * are prohibited!
 * Puts the "deallocated" node at the front of the "free list".
 * Does not need to modify the data member of the "deallocated" node.
 */
void slotFree(unsigned index);


/**
 * Prints the contents of each slot from index @start up to but excluding @end.
 * 
 * This function did not exist in the version of cursor_list.hpp shown during
 * 01/21 lecture.
 * This function's implementation is already provided to you in the
 * version of cursor_list.cpp provided on Canvas.
 */
void printSlots(unsigned start, unsigned end);


/**
 * Returns a new empty list containing just a header node
 * (i.e. returns the index of this header node).
 * Since ths header node would be the last node in this empty list,
 * its next member must be 0.
 * 
 * Throws std::runtime_error exception if no more available slots.
 */
unsigned clCreate();


/**
 * "Deallocates" all slots in the list that starts at @head, i.e. adds all
 * nodes in this list to the "free list".
 *
 * OPTIONAL CHALLENGE: Implement this function such that it runs in constant
 * time (where the input size is the number of nodes) and with constant
 * auxiliary space.
 */
void clDestroy(unsigned head);


/**
 * Adds a new node with value @val to the end of the list that contains @node.
 * (@node need not be the index of a header node.)
 * Throws std::runtime_error exception (and should not attempt to append)
 * if no more available slots.
 */
void clAppend(unsigned node, int val);


/**
 * Adds a new node with value @val immediately after @node.
 * (@node need not be the index of a header node.)
 * Throws std::runtime_error exception (and should not attempt to insert)
 * if no more available slots.
 */
void clInsert(unsigned node, int val);


/**
 * Returns slot index of first node that contains @val in the list
 * whose header node is at index @head.
 * Returns 0 if not found.
 */
unsigned clFind(unsigned head, int val);


/**
 * Prints the data member of each node (except for the header node) in the
 * list whose header node is at index @head.
 * See the examples in prog_hw2.pdf for how the output should look.
 */
void clPrint(unsigned head);


/**
 * Deletes first occurrence of a node that contains @val in the list
 * whose header node is at index @head.
 * Returns true if a node was deleted; returns false otherwise.
 */
bool clDelete(unsigned head, int val);


/**
 * Returns true if the header node that is at index @head is the only
 * node in its list (indicating the list is empty).
 * Otherwise, returns false.
 */
bool clIsEmpty(unsigned head);


/**
 * Returns the length of the given list, not counting the header node.
 * Assumes that @head is the index of a header node.
 */
unsigned clLength(unsigned head);


/**
 * Deletes all nodes in the list whose header node is at index @head
 * that have the value @val.
 * Returns the number of nodes deleted.
 */
unsigned clDeleteAll(unsigned head, int val);


/**
 * Creates a copy of the list whose header node is at index @head
 * and returns the index of this copy's header node.
 *
 * If there are not enough slots to create a copy, then no slots
 * will be allocated (although the free list, without changing length, might
 * still be modified), and an std::runtime_error exception will be thrown.
 */
unsigned clCopy(unsigned head);


/**
 * Reverses the list whose header node is at index @head.
 *
 * IMPLEMENTATION DETAILS: (not normally in a header file)
 *
 * - You are not allowed to allocate or deallocate any slots in this function
 *   (or to call any function that does this).
 *
 * - Whether you choose to change the nodes' data members or their next
 *   members is your choice. (The autograder won't care.)
 *   Whatever you do, the header node must remain the header node,
 *   i.e. @head should still be the index of the list's header node.
 *   In other words, you are reversing all nodes starting at SLOTS[head].next.
 *
 * OPTIONAL CHALLENGE that is like an interview problem:
 * Implement this function with O(1) auxiliary space, i.e. with a constant
 * amount of local variables/space that doesn't scale with the size of the
 * list. Do this all while having the function run in linear (O(n)) time,
 * where n is the number of nodes.
 */
void clReverse(unsigned head);


#endif  // CURSOR_LIST_HPP
