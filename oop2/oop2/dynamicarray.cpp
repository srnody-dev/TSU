//
//  dynamicarray.cpp
//  oop2
//
//  Created by srnody on 21.10.2025.
//

#include "dynamicarray.hpp"
#include <iostream>


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
void DynamicArray<ItemType>::print() const
{
    std::cout << "[";
    for (int i = 0; i < arrayLength_; i++)
    {
        std::cout << arrayData_[i];
        if (i < arrayLength_ - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template class DynamicArray<int>;
