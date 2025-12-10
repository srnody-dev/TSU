//
//  dynamicarray.hpp
//  oop2
//
//  Created by srnody on 21.10.2025.
//

#pragma once

#include <iostream>
#include <assert.h>

template<typename ItemType>
class DynamicArray
{
public:
    class iterator
    {
    public:
        iterator(ItemType* arrayData, int itemIndex)
        : arrayData_(arrayData), itemIndex_(itemIndex) {}
        bool operator!=(const iterator& other) const
        {
            return (arrayData_ != other.arrayData_) || (arrayData_ == other.arrayData_ && itemIndex_ != other.itemIndex_);
        }
        bool operator==(const iterator& other) const
        {
            return !(*this != other);
        }
        ItemType& operator*()
        {
            return arrayData_[itemIndex_];
        }
        iterator& operator++()
        {
            itemIndex_++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            ++itemIndex_;
            return old;
        }
        int operator-(const iterator& other) const
        {
            return itemIndex_ - other.itemIndex_;
        }
    private:
        ItemType* arrayData_;
        int itemIndex_;
        friend class DynamicArray;
    };
    class cIterator
    {
    public:
        cIterator(const ItemType* arrayData, int itemIndex)
        : arrayData_(arrayData), itemIndex_(itemIndex) {}
        bool operator!=(const cIterator& other) const
        {
            return (arrayData_ != other.arrayData_) ||
            (arrayData_ == other.arrayData_ && itemIndex_ != other.itemIndex_);
        }
        bool operator==(const cIterator& other) const
        {
            return !(*this != other);
        }
        const ItemType& operator*() const
        {
            return arrayData_[itemIndex_];
        }
        cIterator& operator++()
        {
            itemIndex_++;
            return *this;
        }
        cIterator operator++(int)
        {
            cIterator old = *this;
            ++itemIndex_;
            return old;
        }
        int operator-(const cIterator& other) const
        {
            return itemIndex_ - other.itemIndex_;
        }
    private:
        const ItemType* arrayData_;
        int itemIndex_;
    };
    
    DynamicArray();
    DynamicArray(int initialLength);
    DynamicArray(const ItemType* array, int length);
    DynamicArray(const DynamicArray& otherArray);
    DynamicArray(DynamicArray&& otherArray);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& otherArray);
    DynamicArray& operator=(DynamicArray&& otherArray);

    ItemType& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const ItemType& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }
    
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator+=(const DynamicArray& other);

    int getLength() const { return arrayLength_; }
    bool insertAt(const int index, const ItemType& value);
    bool removeAt(const int index);
    void print() const;
    void swap(DynamicArray& other);
    int find(const ItemType& value) const;
    void sort();
    bool removeByValue(const ItemType& value);
    int removeAllByValue(const ItemType& value);
    DynamicArray& operator+=(const ItemType& value);

    
    iterator begin() { return iterator(arrayData_, 0); }
    iterator end() { return iterator(arrayData_, arrayLength_); }
        
    cIterator begin() const { return cIterator(arrayData_, 0); }
    cIterator end() const { return cIterator(arrayData_, arrayLength_); }
    
    iterator insert(iterator position, const ItemType& value);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
       
    
private:
    ItemType* arrayData_;
    int arrayLength_;
};

