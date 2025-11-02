//
//  booleanVector.cpp
//  oop3
//
//  Created by srnody on 02.11.2025.
//

#include "booleanvector.hpp"
#include <stdexcept>
#include <cstring>
#include <algorithm>

BooleanVector::BooleanVector() : vectorData_(nullptr), numBits_(0) {}

BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
    : numBits_(numBits)
{
    if (numBits == 0) return;
    
    uint32_t numBytes = numBits / (8 * sizeof(uint8_t));
    if (numBits % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    vectorData_ = new uint8_t[numBytes];
    uint8_t localInitialValue = initialValue ? 255 : 0;

    for (uint32_t byteIndex = 0; byteIndex < numBytes; byteIndex++)
    {
        vectorData_[byteIndex] = localInitialValue;
    }
}

BooleanVector::BooleanVector(const char* str)
{
    if (!str) return;
    
    uint32_t len = 0;
    while (str[len] != '\0') len++;
    
    numBits_ = len;
    if (numBits_ == 0) return;
    
    uint32_t numBytes = getNumBytes();
    vectorData_ = new uint8_t[numBytes]{0};
    
    for (uint32_t i = 0; i < numBits_; i++)
    {
        if (str[i] == '1')
        {
            uint32_t byteIndex = i / (8 * sizeof(uint8_t));
            uint32_t bitIndex = i % (8 * sizeof(uint8_t));
            vectorData_[byteIndex] |= (1 << bitIndex);
        }
    }
}

BooleanVector::BooleanVector(const BooleanVector& other) : numBits_(other.numBits_)
{
    if (other.numBits_ == 0) return;
    
    uint32_t numBytes = getNumBytes();
    vectorData_ = new uint8_t[numBytes];
    memcpy(vectorData_, other.vectorData_, numBytes);
}

BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
}

void BooleanVector::swap(BooleanVector& other)
{
    uint8_t* tempData = vectorData_;
    uint32_t tempBits = numBits_;
        
    vectorData_ = other.vectorData_;
    numBits_ = other.numBits_;
        
    other.vectorData_ = tempData;
    other.numBits_ = tempBits;
}

uint32_t BooleanVector::getWeight() const
{
    uint32_t weight = 0;
    for (uint32_t bit = 0; bit < numBits_; bit++)
    {
        uint32_t byteIndex = bit / (8 * sizeof(uint8_t));
        uint32_t bitIndex = bit % (8 * sizeof(uint8_t));
        if (vectorData_[byteIndex] & (1 << bitIndex))
            weight++;
    }
    return weight;
}

void BooleanVector::invert()
{
    uint32_t numBytes = getNumBytes();
    for (uint32_t i = 0; i < numBytes; i++)
        vectorData_[i] = ~vectorData_[i];
}

void BooleanVector::invert(const uint32_t index)
{
    if (index >= numBits_) throw std::runtime_error("Index out of bounds");
    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));
    vectorData_[byteIndex] ^= (1 << bitIndex);
}

BooleanVector::BitReference BooleanVector::operator[](const uint32_t index) const
{
    if (index >= numBits_) throw std::runtime_error("Index out of bounds");
    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));
    return BooleanVector::BitReference(&vectorData_[byteIndex], bitIndex);
}

BooleanVector::BitReference::BitReference(uint8_t* const bytePtr, const uint8_t bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex) {}

BooleanVector::BitReference::operator bool() const
{
    return *bytePtr_ & (1 << bitIndex_);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const bool newValue)
{
    if (newValue)
        *bytePtr_ |= (1 << bitIndex_);
    else
        *bytePtr_ &= ~(1 << bitIndex_);
    return *this;
}

uint32_t BooleanVector::getNumBytes() const
{
    uint32_t numBytes = numBits_ / 8;
    if (numBits_ % 8 > 0) numBytes += 1;
    return numBytes;
}
