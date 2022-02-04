#include "cursor_list.hpp"

#include <iostream>

#define NUM_SLOTS 30

struct Slot
{
    int data;
    unsigned next;  // index of next slot
};

static struct Slot SLOTS[NUM_SLOTS];
bool firstCall = true;

unsigned checkNumFree()
{
    unsigned index = 0;
    unsigned numFree = 0;
    while(true)
    {
        numFree++;

        if(SLOTS[index].next == 0)
            break;

        index = SLOTS[index].next;
    }  

    return numFree;  
}

unsigned slotAlloc()
{
    // TODO: Implement.
    if(firstCall)
    {
        firstCall = false;
        for(int i = 0; i < NUM_SLOTS; i++)
        {
            if(i == NUM_SLOTS - 1)
            {
                SLOTS[i].next = 0;
                continue;
            }

            SLOTS[i].next = i+1;
        }
    }

    return SLOTS[0].next;
}

void slotFree(unsigned index)
{
    // TODO: Implement.
    
    //put deallocated node at front of free list
    SLOTS[index].next = SLOTS[0].next;
    SLOTS[0].next = index;
    
}

void printSlots(unsigned start, unsigned end)
{
    for (unsigned i = start; i < end; ++i)
        std::cout << "SLOTS[" << i << "]: " << SLOTS[i].data
            << ' ' << SLOTS[i].next << '\n';
}

unsigned clCreate()
{
    // TODO: Implement.
    unsigned temp = slotAlloc();

    if(SLOTS[0].next==0)
        throw std::runtime_error("No more slots");
    
    //adjust free list
    SLOTS[0].next = SLOTS[temp].next;
    SLOTS[temp].next = 0;

    //return index of next free slot
    return temp;
    
}

void clDestroy(unsigned head)
{
    // TODO: Implement.
    //last point to first free list element
    //slots[0].next point to head
    unsigned last = head;

    while(SLOTS[last].next != 0)
        last = SLOTS[last].next;

    SLOTS[last].next = SLOTS[0].next;
    SLOTS[0].next = head;
}

void clAppend(unsigned node, int val)
{
    // TODO: Implement.
    if(SLOTS[0].next==0)
        throw std::runtime_error("No more slots");

    unsigned newIndex = SLOTS[0].next;

    //get last node of list
    while(SLOTS[node].next != 0)
        node = SLOTS[node].next;

    //last node of list points to appended element
    SLOTS[node].next = newIndex;

    //assign free slot to val
    SLOTS[newIndex].data = val;

    //adjust free list
    SLOTS[0].next = SLOTS[SLOTS[0].next].next;

    //assign new node's next to 0
    SLOTS[newIndex].next = 0;
    
}

void clInsert(unsigned node, int val)
{
    // TODO: Implement.
    if(SLOTS[0].next==0)
        throw std::runtime_error("No more slots");
    
    unsigned insertIndex = SLOTS[0].next;

    SLOTS[ insertIndex ].data = val;

    //adjust free list
    SLOTS[0].next = SLOTS[ SLOTS[0].next ].next;

    //set inserted node next to equal original node's next
    SLOTS[ insertIndex ].next = SLOTS[node].next;

    //set original node's next to new node
    SLOTS[node].next = insertIndex;

}

unsigned clFind(unsigned head, int val)
{
    // TODO: Implement.
    while(true)
    {
        if(SLOTS[head].data == val)
            return head;

        if(SLOTS[head].next == 0)
            return 0;

       head = SLOTS[head].next;
    }
}

void clPrint(unsigned head)
{
    // TODO: Implement.
    bool first = true; 
    while(true)
    {
        if(first)
        {
            first = false;
            std::cout << "SLOTS[" << head << "]: (header)\n";
        }else
            std::cout << "SLOTS[" << head << "]: " << SLOTS[head].data << "\n";

        if(SLOTS[head].next == 0)
            break;

        head = SLOTS[head].next;
    }
}

bool clDelete(unsigned head, int val)
{
    // TODO: Implement.
    unsigned prevIndex = 0;
    while(true)
    {
        if(SLOTS[head].data == val)
        {
            if(prevIndex != 0)
                SLOTS[prevIndex].next = SLOTS[head].next;
            slotFree(head);
            return true;
        }

        if(SLOTS[head].next == 0)
            return false;

        prevIndex = head;
        head = SLOTS[head].next;
    }
}

bool clIsEmpty(unsigned head)
{
    // TODO: Implement.
    if(SLOTS[head].next == 0)
        return true;
    return false;
}

unsigned clLength(unsigned head)
{
    // TODO: Implement.
    unsigned length = 0;
    while(SLOTS[head].next != 0)
    {
        head = SLOTS[head].next;
        length++;
    }

    return length;
}

unsigned clDeleteAll(unsigned head, int val)
{
    // TODO: Implement.
    unsigned numDeleted = 0;
    unsigned prevListElement = 0;
    unsigned prevNext;

    while(true)
    {
        //save the next element of list to go to after deletion
        prevNext = SLOTS[head].next;

        if(SLOTS[head].data==val)
        {
            if(prevListElement != 0)
                SLOTS[prevListElement].next = SLOTS[head].next;
            slotFree(head);
            numDeleted++;
        }else
            prevListElement = head;

        if(SLOTS[head].next == 0)
            break;

        head = prevNext;

    }
    return numDeleted;
}

unsigned clCopy(unsigned head)
{
    // TODO: Implement.
    if(clLength(head) >= checkNumFree())
        throw std::runtime_error("not enough space");
    

    unsigned start = clCreate();
    SLOTS[start].data = SLOTS[head].data;

    while(SLOTS[head].next != 0)
    {
        head = SLOTS[head].next;
        clAppend(start, SLOTS[head].data);
    }

    return start;

}

void clReverse(unsigned head)
{
    // TODO: Implement.
    unsigned prevIndex = 0;
    unsigned current = SLOTS[head].next;
    unsigned next;

    while(current != 0)
    {
        next = SLOTS[current].next;

        SLOTS[current].next = prevIndex;

        prevIndex = current;
        current = next;
    }

    SLOTS[head].next = prevIndex;
}





























