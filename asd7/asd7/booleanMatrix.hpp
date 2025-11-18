//
//  booleanMatrix.hpp
//  oop4
//
//  Created by srnody on 14.11.2025.
//

#pragma once
#include <stdint.h>
#include <iostream>
#include "dynamicarray.hpp"
#include "booleanVector.hpp"

class BooleanMatrix
{
public:
    BooleanMatrix() = default;
    BooleanMatrix(uint32_t numRows, uint32_t numColumns, bool initialValue = false);
    BooleanMatrix(const char** charMatrix, uint32_t numRows, uint32_t numColumns);
    BooleanMatrix(const BooleanMatrix& other);
    ~BooleanMatrix() = default;

    uint32_t numRows() const;
    uint32_t numColumns() const;
    void swap(BooleanMatrix& other);
    uint32_t getWeight() const;
    uint32_t getRowWeight(uint32_t rowIndex) const;
    
    BooleanVector rowAnd() const;
    BooleanVector rowOr() const;
    BooleanVector& operator[](uint32_t rowIndex);
    const BooleanVector& operator[](uint32_t rowIndex) const;
    
    BooleanMatrix& operator=(const BooleanMatrix& other);
    BooleanMatrix operator&(const BooleanMatrix& other) const;
    BooleanMatrix& operator&=(const BooleanMatrix& other);
    BooleanMatrix operator~() const;
    BooleanMatrix operator|(const BooleanMatrix& other) const;
    BooleanMatrix& operator|=(const BooleanMatrix& other);
    BooleanMatrix operator^(const BooleanMatrix& other) const;
    BooleanMatrix& operator^=(const BooleanMatrix& other);
    
    void invertBit(uint32_t rowIndex, uint32_t columnIndex);
    void invertBits(uint32_t rowIndex, uint32_t startColumn, uint32_t numBits);
    void setBit(uint32_t rowIndex, uint32_t columnIndex, bool value);
    void setBits(uint32_t rowIndex, uint32_t startColumn, uint32_t numBits, bool value);
    
    friend std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix);
    friend std::istream& operator>>(std::istream& is, BooleanMatrix& matrix);

private:
    DynamicArray<BooleanVector> matrixData_;
};

std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix);
std::istream& operator>>(std::istream& is, BooleanMatrix& matrix);

