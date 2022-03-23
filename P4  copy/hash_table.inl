#include<stdexcept>
#include<memory>
#include<iostream>
#include "hash_table.hpp"


template<typename ValueType>
HashTable<ValueType>:: HashTable(unsigned tableSize)
{
	if(tableSize == 0 || tableSize % 2 == 0)
		throw std::runtime_error("runtime error");

	arr = std::make_unique<bucket<ValueType>[]>(tableSize);
	size = tableSize;
	elements = 0;
}

template<typename ValueType>
HashTable<ValueType>::~HashTable(){}


template<typename ValueType>
HashTable<ValueType>::HashTable(const HashTable& rhs)
{
	arr = std::make_unique<bucket<ValueType>[]>(rhs.tableSize());

	for(unsigned i = 0; i < rhs.tableSize(); i++)
		arr[i] = rhs.arr[i];

	size = rhs.tableSize();
	elements = rhs.numElements();
}

template<typename ValueType>
HashTable<ValueType>& HashTable<ValueType>::operator=(const HashTable& rhs)
{
	arr = std::make_unique<bucket<ValueType>[]>(rhs.tableSize());

	for(unsigned i = 0; i < rhs.tableSize(); i++)
		arr[i] = rhs.arr[i];

	size = rhs.tableSize();
	elements = rhs.numElements();

	return *this;
}

template<typename ValueType>
HashTable<ValueType>::HashTable(HashTable&& rhs) noexcept
{
	this->arr = std::move(rhs.arr);
	this->size = rhs.size;
	this->elements = rhs.elements;

	rhs.arr = nullptr;
	rhs.size = 0;
	rhs.elements = 0;
}

template<typename ValueType>
HashTable<ValueType>& HashTable<ValueType>::operator=(HashTable&& rhs) noexcept
{
	this->arr = std::move(rhs.arr);
	this->size = rhs.size;
	this->elements = rhs.elements;

	rhs.arr = nullptr;
	rhs.size = 0;
	rhs.elements = 0;
	return *this;
}

template<typename ValueType>
unsigned HashTable<ValueType>::tableSize() const
{
	return size;
}

template<typename ValueType>
unsigned HashTable<ValueType>::numElements() const
{
	return elements;
}


template<typename ValueType>
bool HashTable<ValueType>::insert(unsigned key, const ValueType& value)
{
	unsigned count = 0;
	unsigned index = (key%size) + (count * count);

	if(this->get(key))
	{
		while(true)
		{
			index = (key%size) + (count * count);
			
			while( index >= size )
				index -= size;
	
			if(this->arr[index].key == key)
			{
				if( ! this->arr[index].isDeleted )
					return false;
				else
					break;
			}

			count++;
		}
	}

	bool rehash = false;
	count = 0;
	index = (key%size) + (count * count);
	unsigned newSize;
	elements++;

	//Rehash
	if(elements > size/2)
	{
		rehash = true;
		newSize = nextPrime(2*size);

		std::unique_ptr<bucket<ValueType>[]> tempArr;
		tempArr = std::make_unique<bucket<ValueType>[]>(newSize);

		for(unsigned i = 0; i < size; i++)
		{
			if(!arr[i].empty)
			{
				count = 0;
				
				while(true)
				{
					index = (arr[i].key % newSize) + (count * count);
			
					while( index >= newSize )
						index -= newSize;
			
					if(tempArr[index].empty)
					{
						tempArr[index].key = arr[i].key;
						tempArr[index].value = arr[i].value;
						tempArr[index].empty = false;
						tempArr[index].isDeleted = false;
						break;
					}
					count++;
				}
			}
		}

		arr = std::move(tempArr);
	}

	if(rehash == true)
		size = newSize;

	//Insert new element
	count = 0;
	while(true)
	{
		index = (key%size) + (count * count);

		while( index >= size )
			index -= size;

		if(arr[index].empty)
		{
			arr[index].key = key;
			arr[index].value = value;
			arr[index].empty = false;
			arr[index].isDeleted = false;
			return true;
		}
		count++;
	}


}

template<typename ValueType>
ValueType* HashTable<ValueType>::get(unsigned key)
{
	unsigned count = 0;
	unsigned index = (key % size) + (count * count);

	while(true)
	{
		index = (key % size) + (count * count);

		while( index >= size )
			index -= size;

		if(arr[index].empty)
		{
			if(!arr[index].isDeleted)
				break;
		}
	
		if(arr[index].key == key)
		{
			if(arr[index].isDeleted)
				break;

			return &arr[index].value;
		}

		count++;
	}

	return nullptr;
}

template<typename ValueType>
const ValueType* HashTable<ValueType>::get(unsigned key) const
{
	unsigned count = 0;
	unsigned index = (key % size) + (count * count);

	while(true)
	{
		index = (key % size) + (count * count);

		while( index >= size )
			index -= size;

		if(arr[index].empty)
			break;
	
		if(arr[index].key == key)
		{
			if(arr[index].isDeleted)
				break;

			return &arr[index].value;
		}

		count++;
	}

	return nullptr;
}


template<typename ValueType>
bool HashTable<ValueType>::update(unsigned key, const ValueType& newValue)
{
	if(!this->get(key))
		return false;

	unsigned count = 0;
	unsigned index = (key % size) + (count * count);

	while(true)
	{
		index = (key % size) + (count * count);

		while( index >= size )
			index -= size;
	
		if(arr[index].key == key)
		{
			arr[index].value = newValue;
			break;
		}

		count++;
	}

	return true;
}


template<typename ValueType>
bool HashTable<ValueType>::remove(unsigned key)
{
	if(!this->get(key))
		return false;

	unsigned count = 0;
	unsigned index;

	while(true)
	{
		index = (key % size) + (count * count);

		while( index >= size )
			index -= size;
	
		if(arr[index].key == key)
		{
			arr[index].empty = true;
			arr[index].isDeleted = true;
			break;
		}

		count++;
	}
	elements--;
	return true;
}

template<typename ValueType>
unsigned HashTable<ValueType>::removeAllByValue(const ValueType& value)
{
	unsigned numDeleted = 0;

	for(unsigned i = 0; i < size; i++)
	{
		if(!arr[i].empty)
		{
			if(arr[i].value == value)
			{
				arr[i].empty = true;
				arr[i].isDeleted = true;
				numDeleted++;
			}
		}
	}

	elements -= numDeleted;
	return numDeleted;
}


template<typename ValueType>
bool HashTable<ValueType>::operator==(const HashTable& rhs) const
{
	if(this->elements >= rhs.elements)
	{
		for(unsigned i = 0; i < this->size; i++)
		{
			if(this->arr[i].empty)
				continue;

			for(unsigned j = 0; j < rhs.size; j++)
			{
				if(rhs.arr[j].empty)
				{
					if(j == rhs.size - 1)
						return false;

					continue;
				}

				if(this->arr[i].value == rhs.arr[j].value)
					break;
				else
				{
					if(j == rhs.size - 1)
						return false;
				}
			}
		}
	}else
	{
		for(unsigned i = 0; i < rhs.size; i++)
		{
			if(rhs.arr[i].empty)
				continue;

			for(unsigned j = 0; j < this->size; j++)
			{
				if(this->arr[j].empty)
				{
					if(j == this->size - 1)
						return false;

					continue;
				}

				if(rhs.arr[i].value == this->arr[j].value)
					break;
				else
				{
					if(j ==	this->size - 1)
						return false;
				}
			}
		}
	}

	return true;
}

template<typename ValueType>
bool HashTable<ValueType>::operator!=(const HashTable& rhs) const
{
	if(*this == rhs)
		return false;

	return true;
}

template<typename ValueType>
HashTable<ValueType> HashTable<ValueType>::operator+(const HashTable& rhs) const
{
	HashTable<ValueType> newTable(this->size);
	newTable = *this;

	for(unsigned i = 0; i < rhs.size; i++)
	{
		if(!rhs.arr[i].empty)
			newTable.insert(rhs.arr[i].key, rhs.arr[i].value);
	}

	return newTable;
}
















































