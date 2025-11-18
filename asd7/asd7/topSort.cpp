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
