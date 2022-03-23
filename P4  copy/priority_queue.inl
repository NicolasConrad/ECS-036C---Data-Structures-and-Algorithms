#include "priority_queue.hpp"

#include <iostream>
#include<memory>

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(unsigned maxSize)
{
	if(maxSize == 0)
		throw std::runtime_error("runtime error");

	arr = std::make_unique<pBucket<ValueType>[]>(maxSize+1);
	this->size_max = maxSize;
}

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue(){}

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(const PriorityQueue& rhs)
{
	this->arr = std::make_unique<pBucket<ValueType>[]>(rhs.size_max + 1);
	this->size_max = rhs.size_max;
	this->elements = rhs.elements;
	this->ht = rhs.ht;

	for(unsigned i = 0; i < rhs.size_max; i++)
		this->arr[i] = rhs.arr[i];
}

template <typename ValueType>
PriorityQueue<ValueType>& PriorityQueue<ValueType>::operator=(const PriorityQueue& rhs)
{
	this->arr = std::make_unique<pBucket<ValueType>[]>(rhs.size_max + 1);
	this->size_max = rhs.size_max;
	this->elements = rhs.elements;
	this->ht = rhs.ht;

	for(unsigned i = 0; i < rhs.size_max; i++)
		this->arr[i] = rhs.arr[i];

	return *this;
}

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(PriorityQueue&& rhs) noexcept
{
	this->arr = std::move(rhs.arr);
	this->size_max = rhs.size_max;
	this->elements = rhs.elements;
	this->ht = rhs.ht;

	rhs.arr = nullptr;
	rhs.size_max = 0;
	rhs.elements = 0;
}

template <typename ValueType>
PriorityQueue<ValueType>& PriorityQueue<ValueType>::operator=(PriorityQueue&& rhs) noexcept
{	
	this->arr = std::move(rhs.arr);
	this->size_max = rhs.size_max;
	this->elements = rhs.elements;
	this->ht = rhs.ht;

	rhs.arr = nullptr;
	rhs.size_max = 0;
	rhs.elements = 0;

	return *this;
}

template <typename ValueType>
unsigned PriorityQueue<ValueType>::numElements() const
{
	return this->elements;
}

template <typename ValueType>
unsigned PriorityQueue<ValueType>::maxSize() const
{
	return this->size_max;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::insert(unsigned key, const ValueType& value)
{
	if(this->elements + 1 > this->size_max || this->get(key))
		return false;
	else if(this->get(key))
	{
		if( this->arr[ *( ht.get(key) ) ].isDeleted == false)
			return false;
	}

	//insert
	this->arr[nextEmpty].key = key;
	this->arr[nextEmpty].value = value;
	ht.insert(key, nextEmpty);

	percolateUp(nextEmpty);

	this->elements++;
	this->nextEmpty++;
	return true;
}

template <typename ValueType>
const unsigned* PriorityQueue<ValueType>::getMinKey() const
{	
	return &arr[1].key;
}

template <typename ValueType>
const ValueType* PriorityQueue<ValueType>::getMinValue() const
{
	return &arr[1].value;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::deleteMin()
{
	if(elements == 0)
		return false;

	ht.remove(arr[1].key);
	this->arr[1].key = this->arr[this->elements].key;
	this->arr[1].value = this->arr[this->elements].value;

	ht.update(arr[elements].key, 1);

	this->arr[this->elements].isDeleted = true;

	elements--;
	nextEmpty--;

	percolateDown(1);

	return true;
}

template <typename ValueType>
ValueType* PriorityQueue<ValueType>::get(unsigned key)
{
	unsigned int* index = ht.get(key);

	if(index == nullptr)
		return nullptr;

	if( !this->arr[*index].isDeleted )
		return &arr[*index].value;

	return nullptr;
}

template <typename ValueType>
const ValueType* PriorityQueue<ValueType>::get(unsigned key) const
{
	unsigned int* index = ht.get(key);

	if(index == nullptr)
		return false;

	if( !this->arr[*index].isDeleted )
		return &arr[*index].value;

	return nullptr;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::decreaseKey(unsigned key, unsigned change)
{
	if(change == 0)
		return false;

	unsigned* index = ht.get(key);

	if(index == nullptr || this->get( key - change ) || this->arr[*index].isDeleted )
		return false;

	this->arr[*index].key -= change;
	ht.remove(key);

	if(this->arr[*index].key < this->arr[*index/2].key )
		ht.insert(key-change, percolateUp(*index));
	else if( this->arr[*index].key > this->arr[2*(*index)].key || this->arr[*index].key > this->arr[ (2*(*index)) + 1].key )
		ht.insert(key-change, percolateDown(*index));

	return true;
}
    
template <typename ValueType>
bool PriorityQueue<ValueType>::increaseKey(unsigned key, unsigned change)
{
	if(change == 0)
		return false;

	unsigned* index = ht.get(key);

	if(index == nullptr || this->get( key + change ) || this->arr[*index].isDeleted )
		return false;

	this->arr[*index].key += change;
	ht.remove(key);

	if(this->arr[*index].key < this->arr[*index/2].key )
		ht.insert(key+change, percolateUp(*index));
	else if( this->arr[*index].key > this->arr[2*(*index)].key || this->arr[*index].key > this->arr[ (2*(*index)) + 1].key )
		ht.insert(key+change, percolateDown(*index));

	return true;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::remove(unsigned key)
{
	unsigned* index = ht.get(key);

	if(index == nullptr)
		return false;
	
	ht.remove(arr[*index].key);
	this->arr[*index].key = this->arr[elements].key;
	this->arr[*index].value = this->arr[elements].value;
	ht.update(arr[elements].key, *index);

	this->arr[elements].isDeleted = true;

	elements--;
	nextEmpty--;

	if(this->arr[*index].key < this->arr[*index/2].key )
		percolateUp(*index);
	else
		percolateDown(*index);

	return true;
}


template <typename ValueType>
unsigned PriorityQueue<ValueType>::percolateUp(unsigned index)
{
	unsigned tempKey;
    ValueType tempValue;

    //percolate up
    while(arr[index].key < arr[index/2].key)
    {
        tempKey = arr[index].key;
        tempValue = arr[index].value;

        arr[index].key = arr[index/2].key;
        arr[index].value = arr[index/2].value;

        arr[index/2].key = tempKey;
        arr[index/2].value = tempValue;

      	ht.update(arr[index].key, index);
       	ht.update(arr[index/2].key, index/2);

        index = index/2;
    }

    return index;
}

template <typename ValueType>
unsigned PriorityQueue<ValueType>::percolateDown(unsigned index)
{
    unsigned tempKey;
    ValueType tempValue;

    while(this->arr[index].key > this->arr[2*index].key || this->arr[index].key > this->arr[(2*index) + 1].key )
    {
        tempKey = this->arr[index].key;
        tempValue = this->arr[index].value;

        if( (2*index) > elements)
            break;

        if(this->arr[2*index].key < this->arr[(2*index) + 1].key)
        {
            this->arr[index].key = this->arr[2*index].key;
            this->arr[index].value = this->arr[2*index].value;
            this->arr[2*index].key = tempKey;
            this->arr[2*index].value = tempValue;

           	ht.update(arr[index].key, index);
            ht.update(arr[2*index].key, 2*index);

            index *= 2;
        }else
        {
            this->arr[index].key = this->arr[(2*index) + 1].key;
            this->arr[index].value = this->arr[(2*index) + 1].value;
            this->arr[(2*index) + 1].key = tempKey;
            this->arr[(2*index) + 1].value = tempValue;

            ht.update(arr[index].key, index );
            ht.update(arr[(2*index)+1].key, (2*index)+1 );

            index = (2*index) + 1;
        }
    }

    return index;
}










