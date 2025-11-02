//
//  booleanVector.hpp
//  oop3
//
//  Created by srnody on 02.11.2025.
//

#pragma once

#include <stdint.h>

class BooleanVector
{
private:
    class BitReference;

public:
    BooleanVector();
    BooleanVector(const uint32_t size, const bool value = false);
    BooleanVector(const char* str);
    BooleanVector(const BooleanVector& other);
    
    ~BooleanVector();

    uint32_t getLength() const { return numBits_; }
    void swap(BooleanVector& other);
    uint32_t getWeight() const;
    
    void invert();
    void invert(const uint32_t index);
    
    BitReference operator[](const uint32_t index) const;

private:
    class BitReference
    {
    public:
        BitReference(uint8_t* const bytePtr, const uint8_t bitIndex);
        operator bool() const;
        BitReference& operator=(const bool newValue);

    private:
        uint8_t* bytePtr_;
        uint8_t bitIndex_;
    };

    uint8_t* vectorData_ = nullptr;
    uint32_t numBits_ = 0;
    
    uint32_t getNumBytes() const;
};
