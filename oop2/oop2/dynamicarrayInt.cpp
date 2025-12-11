//
//  dynamicarrayInt.cpp
//  oop2
//
//  Created by srnody on 11.12.2025.
//

#include "dynamicarrayInt.hpp"
#include <iostream>
#include <algorithm>

DynamicArrayInt::DynamicArrayInt() : arrayData_(nullptr), arrayLength_(0)
{
    std::cout << "DynamicArrayInt::DynamicArrayInt()" << std::endl;
}

DynamicArrayInt::DynamicArrayInt(int initialLength) : arrayLength_(initialLength)
{
    std::cout << "DynamicArrayInt::DynamicArrayInt(int)" << std::endl;

    arrayData_ = new int[initialLength];
    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = 0;
    }
}

DynamicArrayInt::DynamicArrayInt(const int* array, int length) : arrayLength_(length)
{
    std::cout << "DynamicArrayInt::DynamicArrayInt(const int*, int)" << std::endl;

    arrayData_ = new int[length];
    for (int i = 0; i < length; i++)
    {
        arrayData_[i] = array[i];
    }
}

DynamicArrayInt::DynamicArrayInt(const DynamicArrayInt& otherArray)
{
    std::cout << "DynamicArrayInt::DynamicArrayInt(const DynamicArrayInt&)" << std::endl;

    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new int[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

DynamicArrayInt::DynamicArrayInt(DynamicArrayInt&& otherArray)
{
    std::cout << "DynamicArrayInt::DynamicArrayInt(DynamicArrayInt&&)" << std::endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

DynamicArrayInt::~DynamicArrayInt()
{
    std::cout << "DynamicArrayInt::~DynamicArrayInt()" << std::endl;
    delete[] arrayData_;
}

DynamicArrayInt& DynamicArrayInt::operator=(const DynamicArrayInt& otherArray)
{
    std::cout << "DynamicArrayInt::operator=(const DynamicArrayInt&)" << std::endl;

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
            arrayData_ = new int[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

DynamicArrayInt& DynamicArrayInt::operator=(DynamicArrayInt&& otherArray)
{
    std::cout << "DynamicArrayInt::operator=(DynamicArrayInt&&)" << std::endl;

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

bool DynamicArrayInt::operator==(const DynamicArrayInt& other) const
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

bool DynamicArrayInt::operator!=(const DynamicArrayInt& other) const
{
    return !(*this == other);
}

DynamicArrayInt DynamicArrayInt::operator+(const DynamicArrayInt& other) const
{
    DynamicArrayInt result(arrayLength_ + other.arrayLength_);
    
    for (int i = 0; i < arrayLength_; i++)
        result[i] = arrayData_[i];
    
    for (int i = 0; i < other.arrayLength_; i++)
        result[arrayLength_ + i] = other.arrayData_[i];
    
    return result;
}

DynamicArrayInt& DynamicArrayInt::operator+=(const DynamicArrayInt& other)
{
    *this = *this + other;
    return *this;
}

bool DynamicArrayInt::insertAt(int index, int value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new int[1];
        arrayData_[0] = value;
        ++arrayLength_;
        return true;
    }

    if (index < 0 || index > arrayLength_) return false;

    int* tempArrayData = new int[arrayLength_ + 1];

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

bool DynamicArrayInt::removeAt(int index)
{
    if (index < 0 || index >= arrayLength_) return false;

    if (arrayLength_ == 1)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return true;
    }

    int* tempArrayData = new int[arrayLength_ - 1];

    for (int i = 0; i < index; i++)
        tempArrayData[i] = arrayData_[i];

    for (int i = index + 1; i < arrayLength_; i++)
        tempArrayData[i - 1] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_--;

    return true;
}

void DynamicArrayInt::print() const
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

void DynamicArrayInt::swap(DynamicArrayInt& other)
{
    int* tempData = arrayData_;
    int tempLength = arrayLength_;

    arrayData_ = other.arrayData_;
    arrayLength_ = other.arrayLength_;

    other.arrayData_ = tempData;
    other.arrayLength_ = tempLength;
}

int DynamicArrayInt::findReturnIndex(int value) const
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == value)
            return i;
    }
    return -1;
}

void DynamicArrayInt::sort()
{
    if (arrayLength_ <= 1)
        return;

    for (int interval = arrayLength_ / 2; interval > 0; interval = interval / 2)
    {
        for (int i = interval; i < arrayLength_; i++)
        {
            int temp = arrayData_[i];
            int j;
            
            for (j = i; j >= interval && arrayData_[j - interval] > temp; j -= interval)
            {
                arrayData_[j] = arrayData_[j - interval];
            }
            arrayData_[j] = temp;
        }
    }
}

bool DynamicArrayInt::removeByValue(int value)
{
    int index = findReturnIndex(value);
    if (index == -1)
        return false;
    
    return removeAt(index);
}

int DynamicArrayInt::removeAllByValue(int value)
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

DynamicArrayInt& DynamicArrayInt::operator+=(int value)
{
    insertAt(arrayLength_, value);
    return *this;
}

DynamicArrayInt::iterator DynamicArrayInt::insert(iterator position, int value)
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

DynamicArrayInt::iterator DynamicArrayInt::erase(iterator position)
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

DynamicArrayInt::iterator DynamicArrayInt::erase(iterator first, iterator last)
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

int& DynamicArrayInt::findMax()
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

const int& DynamicArrayInt::findMax() const
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

int& DynamicArrayInt::findMin()
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

const int& DynamicArrayInt::findMin() const
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
