//
//  main.cpp
//  oop4
//
//  Created by srnody on 14.11.2025.
//

#include <iostream>
#include "booleanMatrix.hpp"

int main() {
    
    std::cout << "Конструкторы: " << std::endl;
    BooleanMatrix m1(2, 3, true);
    std::cout << "Конструктор с параметрами: " << std::endl << m1 << std::endl;
    const char* chars[] = {"101", "010"};
    BooleanMatrix m2(chars, 2, 3);
    std::cout << "Конструктор из char: " << std::endl << m2 << std::endl;
    
    std::cout << "Тест методов: " << std::endl;
    std::cout << "m2.rows() = " << m2.numRows() << std::endl;
    std::cout << "m2.columns() = " << m2.numColumns() << std::endl;
    std::cout << "m2.weight() = " << m2.getWeight() << std::endl;
    
    std::cout << "Вес строки 0: " << m2.getRowWeight(0) << std::endl;
    std::cout << "rowAND: " << m2.rowAnd() << std::endl;
    std::cout << "rowOR: " << m2.rowOr() << std::endl;
    
    std::cout << "До invertBit(0, 1): " << std::endl << m2 << std::endl;
    m2.invertBit(0, 1);
    std::cout << "После invertBit(0, 1): " << std::endl << m2 << std::endl;
        
    std::cout << "До invertBits(1, 1, 2): " << std::endl << m2 << std::endl;
    m2.invertBits(1, 1, 2);
    std::cout << "После invertBits(1, 1, 2): " << std::endl << m2 << std::endl;
        
    std::cout << "До setBit(0, 1, false): " << std::endl << m2 << std::endl;
    m2.setBit(0, 1, false);
    std::cout << "После setBit(0, 1, false): " << std::endl << m2 << std::endl;
        
    std::cout << "До setBits(1, 1, 2, true): " << std::endl << m2 << std::endl;
    m2.setBits(1, 0, 2, true);
    std::cout << "После setBits(1, 1, 2, true): " << std::endl << m2 << std::endl;
        
    std::cout << "Оператор []: " << std::endl;
    m2[0][1] = false;
    m2[1][0] = true;
    std::cout << "after: " << std::endl << m2 << std::endl;
    
    std::cout << "Swap:" << std::endl;
    m1.swap(m2);
    std::cout << "after swap m1: " << std::endl << m1 << std::endl;
    std::cout << "after swap m2: " << std::endl << m2 << std::endl;
    
    std::cout << "Введите матрицу: " << std::endl;
    
    BooleanMatrix inputMatrix;
    std::cin >> inputMatrix;
    
    std::cout << "Введенная матрица: " << std::endl;
    std::cout << inputMatrix << std::endl;
    
    return 0;
    
    
    
}
