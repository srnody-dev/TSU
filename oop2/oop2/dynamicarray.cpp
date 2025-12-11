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
int DynamicArray<ItemType>::findReturnIndex(const ItemType& value) const
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == value)
            return i;
    }
    return -1;
}
template<typename ItemType>
void DynamicArray<ItemType>::sort()
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
    int index = findReturnIndex(value);
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
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const ItemType& value)
{
    insertAt(arrayLength_, value);
    return *this;
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::insert(iterator position, const ItemType& value)
{
    int index = position - begin();
    
    if (index < 0 || index > arrayLength_) {
        return end();
    }
    
    if (insertAt(index, value)) {
        return iterator(arrayData_, index);
    }
    
    return end();
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::erase(iterator position)
{
    if (position == end() || arrayLength_ == 0) {
        return end();
    }
    
    int index = position - begin();
    
    if (index < 0 || index >= arrayLength_) {
        return end();
    }
    
    if (removeAt(index)) {
        if (index == arrayLength_) {
            return end();
        }
        return iterator(arrayData_, index);
    }
    
    return end();
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::erase(iterator first, iterator last)
{
    if (first == last || arrayLength_ == 0) {
        return last;
    }
    
    int startIndex = first - begin();
    int endIndex = last - begin();
    int count = endIndex - startIndex;
    
    if (count <= 0) return last;
    
    if (startIndex < 0 || endIndex > arrayLength_) {
        return end();
    }
    
    for (int i = 0; i < count; i++) {
        if (!removeAt(startIndex)) {
            return iterator(arrayData_, startIndex);
        }
    }
    
    return iterator(arrayData_, startIndex);
}

template<typename ItemType>
ItemType& DynamicArray<ItemType>::fingMax()
{
    if (arrayLength_ == 0)
    {
        throw std::runtime_error("Array is empty");
    }
    
    int maxIndex = 0;
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] > arrayData_[maxIndex])
        {
            maxIndex = i;
        }
    }
    return arrayData_[maxIndex];
}

template<typename ItemType>
const ItemType& DynamicArray<ItemType>::fingMax() const
{
    if (arrayLength_ == 0)
    {
        throw std::runtime_error("Array is empty");
    }
    
    int maxIndex = 0;
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] > arrayData_[maxIndex])
        {
            maxIndex = i;
        }
    }
    return arrayData_[maxIndex];
}

template<typename ItemType>
ItemType& DynamicArray<ItemType>::findMin()
{
    if (arrayLength_ == 0)
    {
        throw std::runtime_error("Array is empty");
    }
    
    int minIndex = 0;
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] < arrayData_[minIndex])
        {
            minIndex = i;
        }
    }
    return arrayData_[minIndex];
}

template<typename ItemType>
const ItemType& DynamicArray<ItemType>::findMin() const
{
    if (arrayLength_ == 0)
    {
        throw std::runtime_error("Array is empty");
    }
    
    int minIndex = 0;
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] < arrayData_[minIndex])
        {
            minIndex = i;
        }
    }
    return arrayData_[minIndex];
}

template class DynamicArray<int>;
template class DynamicArray<double>;
template class DynamicArray<float>;
