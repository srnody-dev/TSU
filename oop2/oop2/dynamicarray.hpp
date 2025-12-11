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
    int findReturnIndex(const ItemType& value) const;
    void sort();
    bool removeByValue(const ItemType& value);
    int removeAllByValue(const ItemType& value);
    DynamicArray& operator+=(const ItemType& value);
    
    ItemType& fingMax();
    ItemType& findMin();
    const ItemType& fingMax() const;
    const ItemType& findMin() const;

    iterator begin() { return iterator(arrayData_, 0); }
    iterator end() { return iterator(arrayData_, arrayLength_); }
        
    cIterator begin() const { return cIterator(arrayData_, 0); }
    cIterator end() const { return cIterator(arrayData_, arrayLength_); }
    
    iterator insert(iterator position, const ItemType& value);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr);
        
    template<typename T>
    friend std::istream& operator>>(std::istream& is, DynamicArray<T>& arr);
       
    
private:
    ItemType* arrayData_;
    int arrayLength_;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr)
{
    os << "[";
    for (int i = 0; i < arr.arrayLength_; i++) {
        os << arr.arrayData_[i];
        if (i < arr.arrayLength_ - 1) {
            os << " ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, DynamicArray<T>& arr)
{
    delete[] arr.arrayData_;
    arr.arrayData_ = nullptr;
    arr.arrayLength_ = 0;
    
    int size;
    if (is >> size && size >= 0) {
        arr.arrayLength_ = size;
        if (size > 0) {
            arr.arrayData_ = new T[size];
            for (int i = 0; i < size; i++) {
                is >> arr.arrayData_[i];
            }
        }
    }
    return is;
}
