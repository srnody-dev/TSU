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


private:
    ItemType* arrayData_;
    int arrayLength_;
};

