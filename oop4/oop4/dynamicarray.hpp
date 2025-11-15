//
//  dynamicarray.hpp
//  oop2
//
//  Created by srnody on 21.10.2025.
//
#pragma once

#include <iostream>
#include <assert.h>
#include <stdexcept>

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
    
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<ItemType>& array)
    {
        os << "[";
        for (int i = 0; i < array.arrayLength_; i++) {
            os << array.arrayData_[i];
            if (i < array.arrayLength_ - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, DynamicArray<ItemType>& array)
    {
        delete[] array.arrayData_;
        array.arrayData_ = nullptr;
        array.arrayLength_ = 0;
        
        int size;
        std::cout << "Введите размер массива: ";
        is >> size;
        
        if (size > 0) {
            array.arrayData_ = new ItemType[size];
            array.arrayLength_ = size;
            
            std::cout << "Введите " << size << " элементов: ";
            for (int i = 0; i < size; i++) {
                is >> array.arrayData_[i];
            }
        }
        
        return is;
    }
    
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator+=(const DynamicArray& other);

    int getLength() const { return arrayLength_; }
    bool insertAt(const int index, const ItemType& value);
    bool removeAt(const int index);
    void swap(DynamicArray& other);
    int find(const ItemType& value) const;
    void sortShell();
    bool removeByValue(const ItemType& value);
    bool append(const ItemType& value);
    int removeAllByValue(const ItemType& value);
    ItemType getMax() const;
    ItemType getMin() const;

private:
    ItemType* arrayData_;
    int arrayLength_;
};

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{
    std::cout << "DynamicArray::DynamicArray()" << std::endl;
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    std::cout << "DynamicArray::DynamicArray(int)" << std::endl;

    arrayData_ = new ItemType[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = ItemType();
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const ItemType* array, int length) : arrayLength_(length)
{
    std::cout << "DynamicArray::DynamicArray(const ItemType*, int)" << std::endl;

    arrayData_ = new ItemType[length];
    for (int i = 0; i < length; i++)
    {
        arrayData_[i] = array[i];
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(const DynamicArray&)" << std::endl;

    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new ItemType[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(DynamicArray&&)" << std::endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

template<typename ItemType>
DynamicArray<ItemType>::~DynamicArray()
{
    std::cout << "DynamicArray::~DynamicArray()" << std::endl;

    delete[] arrayData_;
}

template<typename ItemType>
bool DynamicArray<ItemType>::append(const ItemType& value) {
    return insertAt(arrayLength_, value);
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::operator=(const DynamicArray&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        if (otherArray.arrayLength_ == 0)
        {
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
        else
        {
            arrayLength_ = otherArray.arrayLength_;
            arrayData_ = new ItemType[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::operator=(DynamicArray&&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        arrayData_ = otherArray.arrayData_;
        arrayLength_ = otherArray.arrayLength_;
        otherArray.arrayData_ = nullptr;
        otherArray.arrayLength_ = 0;
    }

    return *this;
}

template<typename ItemType>
bool DynamicArray<ItemType>::insertAt(const int index, const ItemType& value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new ItemType[1];
        arrayData_[0] = value;
        ++arrayLength_;
        return true;
    }

    if (index < 0 || index > arrayLength_) return false;

    ItemType* tempArrayData = new ItemType[arrayLength_ + 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx + 1] = arrayData_[curIdx];
    }

    tempArrayData[index] = value;

    ++arrayLength_;
    delete[] arrayData_;
    arrayData_ = tempArrayData;

    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;

    if (arrayLength_ == 1)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return true;
    }

    ItemType* tempArrayData = new ItemType[arrayLength_ - 1];

    for (int i = 0; i < index; i++)
        tempArrayData[i] = arrayData_[i];

    for (int i = index + 1; i < arrayLength_; i++)
        tempArrayData[i - 1] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_--;

    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_)
        return false;

    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    }
    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const DynamicArray& other) const
{
    DynamicArray<ItemType> result(arrayLength_ + other.arrayLength_);
    
    for (int i = 0; i < arrayLength_; i++)
        result[i] = arrayData_[i];
    
    for (int i = 0; i < other.arrayLength_; i++)
        result[arrayLength_ + i] = other.arrayData_[i];
    
    return result;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const DynamicArray& other)
{
    *this = *this + other;
    return *this;
}

template<typename ItemType>
void DynamicArray<ItemType>::swap(DynamicArray& other)
{
    ItemType* tempData = arrayData_;
    int tempLength = arrayLength_;

    arrayData_ = other.arrayData_;
    arrayLength_ = other.arrayLength_;

    other.arrayData_ = tempData;
    other.arrayLength_ = tempLength;
}

template<typename ItemType>
int DynamicArray<ItemType>::find(const ItemType& value) const
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == value)
            return i;
    }
    return -1;
}

template<typename ItemType>
void DynamicArray<ItemType>::sortShell()
{
    if (arrayLength_ <= 1)
        return;

    for (int interval = arrayLength_ / 2; interval > 0; interval = interval / 2)
    {
        for (int i = interval; i < arrayLength_; i++)
        {
            ItemType temp = arrayData_[i];
            int j;
            
            for (j = i; j >= interval && arrayData_[j - interval] > temp; j -= interval)
            {
                arrayData_[j] = arrayData_[j - interval];
            }
            arrayData_[j] = temp;
        }
    }
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeByValue(const ItemType& value)
{
    int index = find(value);
    if (index == -1)
        return false;
    
    return removeAt(index);
}

template<typename ItemType>
int DynamicArray<ItemType>::removeAllByValue(const ItemType& value)
{
    int count = 0;
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == value)
        {
            removeAt(i);
            i--;
            count++;
        }
    }
    return count;
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMax() const
{
    if (arrayLength_ == 0) {
        throw std::runtime_error("arrayLength_ == 0");
    }
    
    ItemType max = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] > max)
            max = arrayData_[i];
    }
    return max;
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMin() const
{
    if (arrayLength_ == 0) {
        throw std::runtime_error("arrayLength_ == 0");
    }
    
    ItemType min = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] < min)
            min = arrayData_[i];
    }
    return min;
}
