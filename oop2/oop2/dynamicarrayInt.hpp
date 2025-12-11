//
//  dynamicarrayInt.hpp
//  oop2
//
//  Created by srnody on 11.12.2025.
//

#pragma once

#include <iostream>
#include <cassert>

class DynamicArrayInt
{
public:
    class iterator
    {
    public:
        iterator(int* arrayData, int itemIndex)
        : arrayData_(arrayData), itemIndex_(itemIndex) {}
        
        bool operator!=(const iterator& other) const
        {
            return (arrayData_ != other.arrayData_) ||
                   (arrayData_ == other.arrayData_ && itemIndex_ != other.itemIndex_);
        }
        
        bool operator==(const iterator& other) const
        {
            return !(*this != other);
        }
        
        int& operator*()
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
        int* arrayData_;
        int itemIndex_;
        friend class DynamicArrayInt;
    };
    
    class const_iterator
    {
    public:
        const_iterator(const int* arrayData, int itemIndex)
        : arrayData_(arrayData), itemIndex_(itemIndex) {}
        
        bool operator!=(const const_iterator& other) const
        {
            return (arrayData_ != other.arrayData_) ||
                   (arrayData_ == other.arrayData_ && itemIndex_ != other.itemIndex_);
        }
        
        bool operator==(const const_iterator& other) const
        {
            return !(*this != other);
        }
        
        const int& operator*() const
        {
            return arrayData_[itemIndex_];
        }
        
        const_iterator& operator++()
        {
            itemIndex_++;
            return *this;
        }
        
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++itemIndex_;
            return old;
        }
        
        int operator-(const const_iterator& other) const
        {
            return itemIndex_ - other.itemIndex_;
        }
        
    private:
        const int* arrayData_;
        int itemIndex_;
    };
    
    DynamicArrayInt();
    DynamicArrayInt(int initialLength);
    DynamicArrayInt(const int* array, int length);
    DynamicArrayInt(const DynamicArrayInt& otherArray);
    DynamicArrayInt(DynamicArrayInt&& otherArray);
    ~DynamicArrayInt();

    DynamicArrayInt& operator=(const DynamicArrayInt& otherArray);
    DynamicArrayInt& operator=(DynamicArrayInt&& otherArray);

    int& operator[](int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const int& operator[](int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }
    
    bool operator==(const DynamicArrayInt& other) const;
    bool operator!=(const DynamicArrayInt& other) const;
    DynamicArrayInt operator+(const DynamicArrayInt& other) const;
    DynamicArrayInt& operator+=(const DynamicArrayInt& other);
    
    int getLength() const { return arrayLength_; }
    bool isEmpty() const { return arrayLength_ == 0; }
    bool insertAt(int index, int value);
    bool removeAt(int index);
    void print() const;
    void swap(DynamicArrayInt& other);
    int findReturnIndex(int value) const;
    void sort();
    bool removeByValue(int value);
    int removeAllByValue(int value);
    DynamicArrayInt& operator+=(int value);
    
    int& findMax();
    int& findMin();
    const int& findMax() const;
    const int& findMin() const;
    
    iterator begin() { return iterator(arrayData_, 0); }
    iterator end() { return iterator(arrayData_, arrayLength_); }
    
    const_iterator begin() const { return const_iterator(arrayData_, 0); }
    const_iterator end() const { return const_iterator(arrayData_, arrayLength_); }
    
    iterator insert(iterator position, int value);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    
    friend std::ostream& operator<<(std::ostream& os, const DynamicArrayInt& arr);
    friend std::istream& operator>>(std::istream& is, DynamicArrayInt& arr);
    
private:
    int* arrayData_;
    int arrayLength_;
};

std::ostream& operator<<(std::ostream& os, const DynamicArrayInt& arr)
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

std::istream& operator>>(std::istream& is, DynamicArrayInt& arr)
{
    delete[] arr.arrayData_;
    arr.arrayData_ = nullptr;
    arr.arrayLength_ = 0;
    
    int size;
    if (is >> size && size >= 0) {
        arr.arrayLength_ = size;
        if (size > 0) {
            arr.arrayData_ = new int[size];
            for (int i = 0; i < size; i++) {
                is >> arr.arrayData_[i];
            }
        }
    }
    return is;
}
