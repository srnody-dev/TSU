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
    
    std::cout << "operator=:" << std::endl;
    BooleanMatrix m3 = m2;
    std::cout << "m3 = m2: " << std::endl << m3 << std::endl;
        
    std::cout << "operator&:" << std::endl;
    const char* data1[] = {"101", "110"};
    const char* data2[] = {"110", "011"};
    BooleanMatrix a(data1, 2, 3);
    BooleanMatrix b(data2, 2, 3);
    std::cout << "a: " << std::endl << a << std::endl;
    std::cout << "b: " << std::endl << b << std::endl;
    std::cout << "a & b: " << std::endl << (a & b) << std::endl;
        
    std::cout << "operator&=:" << std::endl;
    a &= b;
    std::cout << "a &= b: " << std::endl << a << std::endl;
        
    std::cout << "operator~:" << std::endl;
    std::cout << "~m2: " << std::endl << (~m2) << std::endl;
    
    std::cout << "operator|:" << std::endl;
    const char* data3[] = {"101", "010"};
    const char* data4[] = {"110", "101"};
    BooleanMatrix c(data3, 2, 3);
    BooleanMatrix d(data4, 2, 3);
    std::cout << "c: " << std::endl << c << std::endl;
    std::cout << "d: " << std::endl << d << std::endl;
    std::cout << "c | d: " << std::endl << (c | d) << std::endl;
        
    std::cout << "operator|=:" << std::endl;
    c |= d;
    std::cout << "c |= d: " << std::endl << c << std::endl;
        
    std::cout << "operator^:" << std::endl;
    const char* data5[] = {"101", "110"};
    const char* data6[] = {"110", "011"};
    BooleanMatrix e(data5, 2, 3);
    BooleanMatrix f(data6, 2, 3);
    std::cout << "e: " << std::endl << e << std::endl;
    std::cout << "f: " << std::endl << f << std::endl;
    std::cout << "e ^ f: " << std::endl << (e ^ f) << std::endl;
        
    std::cout << "operator^=:" << std::endl;
    e ^= f;
    std::cout << "e ^= f: " << std::endl << e << std::endl;
        
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
    
    std::cout << "Размеры: " << inputMatrix.numRows() << "x" << inputMatrix.numColumns() << std::endl;
    std::cout << "Вес матрицы: " << inputMatrix.getWeight() << std::endl;
            
    if (inputMatrix.numRows() > 0) {
    std::cout << "Вес строки 0: " << inputMatrix.getRowWeight(0) << std::endl;
        }
            
    std::cout << "rowAND: " << inputMatrix.rowAnd() << std::endl;
    std::cout << "rowOR: " << inputMatrix.rowOr() << std::endl;
            
    if (inputMatrix.numRows() > 0 && inputMatrix.numColumns() > 0) {
        std::cout << "invertBit(0,0):" << std::endl;
        inputMatrix.invertBit(0, 0);
        std::cout << inputMatrix << std::endl;
        
        std::cout << "setBit(0,0,true):" << std::endl;
        inputMatrix.setBit(0, 0, true);
        std::cout << inputMatrix << std::endl;
    }
    
    BooleanMatrix copyMatrix = inputMatrix;
    std::cout << "Копия матрицы: " << std::endl << copyMatrix << std::endl;
            
    std::cout << "Инверсия (~): " << std::endl << (~inputMatrix) << std::endl;
            
    std::cout << "inputMatrix & inputMatrix: " << std::endl << (inputMatrix & inputMatrix) << std::endl;
    std::cout << "inputMatrix | inputMatrix: " << std::endl << (inputMatrix | inputMatrix) << std::endl;
    std::cout << "inputMatrix ^ inputMatrix: " << std::endl << (inputMatrix ^ inputMatrix) << std::endl;
        
    return 0;
}
