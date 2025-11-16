//
//  booleanMatrix.cpp
//  oop4
//
//  Created by srnody on 14.11.2025.
//

#include "booleanMatrix.hpp"
#include <stdexcept>

BooleanMatrix::BooleanMatrix(uint32_t numRows, uint32_t numColumns, bool initialValue)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_.append(BooleanVector(numColumns, initialValue));
    }
}

BooleanMatrix::BooleanMatrix(const char** charMatrix, uint32_t numRows, uint32_t numColumns)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        BooleanVector rowVector(numColumns, false);
        if (charMatrix[rowIndex] != nullptr)
        {
            const char* rowStr = charMatrix[rowIndex];
            for (uint32_t col = 0; col < numColumns && rowStr[col] != '\0'; ++col)
            {
                if (rowStr[col] == '1')
                {
                    rowVector.set1(col);
                }
            }
        }
        matrixData_.append(rowVector);
    }
}

uint32_t BooleanMatrix::numRows() const
{
    return matrixData_.getLength();
}

uint32_t BooleanMatrix::numColumns() const
{
    return matrixData_.getLength() > 0 ? matrixData_[0].getLength() : 0;
}

void BooleanMatrix::swap(BooleanMatrix& other)
{
    matrixData_.swap(other.matrixData_);
}

uint32_t BooleanMatrix::getWeight() const
{
    uint32_t totalWeight = 0;
    for (uint32_t i = 0; i < numRows(); ++i)
    {
        totalWeight += matrixData_[i].getWeight();
    }
    return totalWeight;
}

BooleanVector& BooleanMatrix::operator[](uint32_t rowIndex)
{
    if (rowIndex >= numRows())
        throw std::runtime_error("Invalid row index");
    
    return matrixData_[rowIndex];
}

const BooleanVector& BooleanMatrix::operator[](uint32_t rowIndex) const
{
    if (rowIndex >= numRows())
        throw std::runtime_error("Invalid row index");
    
    return matrixData_[rowIndex];
}



std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix)
{
    uint32_t numRows = matrix.numRows();
    
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        os << matrix[rowIndex];
        if (rowIndex < numRows - 1)
            os << std::endl;
    }
    
    return os;
}

std::istream& operator>>(std::istream& is, BooleanMatrix& matrix)
{
    uint32_t rows, cols;
    
    std::cout << "Введите количество строк: ";
    is >> rows;
    std::cout << "Введите количество столбцов: ";
    is >> cols;
    
    BooleanMatrix temp(rows, cols);
    
    std::cout << "Введите матрицу построчно: "<< std::endl;
    
    for (uint32_t i = 0; i < rows; ++i)
    {
        char buffer[1000];
        is >> buffer;
        BooleanVector rowVector(buffer);
        temp[i] = rowVector;
    }
    
    matrix = temp;
    return is;
}

uint32_t BooleanMatrix::getRowWeight(uint32_t rowIndex) const
{
    if (rowIndex >= numRows())
        throw std::runtime_error("Invalid row index");
    
    return matrixData_[rowIndex].getWeight();
}

BooleanVector BooleanMatrix::rowAnd() const
{
    if (numRows() == 0) return BooleanVector();
    
    BooleanVector result = matrixData_[0];
    for (uint32_t i = 1; i < numRows(); ++i)
    {
        result &= matrixData_[i];
    }
    return result;
}

BooleanVector BooleanMatrix::rowOr() const
{
    if (numRows() == 0) return BooleanVector();
    
    BooleanVector result = matrixData_[0];
    for (uint32_t i = 1; i < numRows(); ++i)
    {
        result |= matrixData_[i];
    }
    return result;
}
