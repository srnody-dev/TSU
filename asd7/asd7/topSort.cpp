//
//  topSort.cpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#include "topSort.hpp"

TopSort::TopSort(const BooleanMatrix& nodeLinkMatrix)
    : nodeLinkMatrix(nodeLinkMatrix)
    , nodeCount_(nodeLinkMatrix.numColumns())
{
    if (nodeLinkMatrix.numRows() != nodeLinkMatrix.numColumns()) {
        throw std::invalid_argument("Matrix must be squar");
    }
}

TopSort::TopSort(uint32_t nodeCount)
    : nodeLinkMatrix(nodeCount, nodeCount, false)
    , nodeCount_(nodeCount)
{
}

void TopSort::addEdge(uint32_t from, uint32_t to) {
    if (from >= nodeCount_ || to >= nodeCount_) {
        throw std::out_of_range("Index out of range");
    }
    nodeLinkMatrix.setBit(from, to, true);
}

void TopSort::printNodeLinkMatrix() const {
    std::cout << "Матрица смежности:" << std::endl;
    std::cout << "  ";
    for (uint32_t i = 0; i < nodeCount_; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    for (uint32_t i = 0; i < nodeCount_; ++i) {
        std::cout << i << " ";
        for (uint32_t j = 0; j < nodeCount_; ++j)
            std::cout << (nodeLinkMatrix[i][j] ? "1 " : "0 ");
        std::cout << std::endl;
    }
}
void TopSort::printSortTopResult(const DynamicArray<uint32_t>& result) const {
    std::cout << "Топологический порядок: ";
    for (int i = 0; i < result.getLength(); ++i) {
        std::cout << result[i];
        if (i < result.getLength() - 1) {
            std::cout << " -> " ;
        }
    }
    std::cout << std::endl;
}

BooleanVector TopSort::BuildV1(const BooleanMatrix& currentMatrix) const { //ищем вершины которые достигаются тоесть имеют входящие ребра
    BooleanVector v1(nodeCount_, false); //вектор вершин имеющих входящие ребра
    
    for (uint32_t i = 0; i < nodeCount_; ++i) {
        for (uint32_t j = 0; j < nodeCount_; ++j) {
            if (currentMatrix[i][j]) {
                v1.set1(j);
            }
        }
    }
    
    return v1;
}

DynamicArray<uint32_t> TopSort::sortTop() const {
    DynamicArray<uint32_t> result;
    BooleanMatrix currentMatrix = nodeLinkMatrix;
    BooleanVector v0(nodeCount_, false); //вектор обработанных вершин
    
    while (result.getLength() < nodeCount_) {
        BooleanVector v1 = BuildV1(currentMatrix);
        BooleanVector not_v1 = ~v1; //вектор не имеющий входящих ребер
        BooleanVector v2 = not_v1 & (~v0); // доступные для добавление
    
        
        if (v2.getWeight() == 0) {
            throw std::runtime_error("Граф содержит цикл");
        }
        
        for (uint32_t node = 0; node < nodeCount_; ++node) {
            if (v2[node] && !v0[node]) {
                result.append(node);
                v0.set1(node);
                for (uint32_t j = 0; j < nodeCount_; ++j) {
                    currentMatrix.setBit(node, j, false);
                }
            }
        }
    }
    
    return result;
}
