//
//  topSort.hpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#pragma once
#include <iostream>
#include "booleanMatrix.hpp"
#include "dynamicarray.hpp"

class TopSort {
public:
    TopSort(const BooleanMatrix& nodeLinkMatrix);
    TopSort(uint32_t nodeCount);

    void addEdge(uint32_t from, uint32_t to);
    void printNodeLinkMatrix() const;
    
    BooleanVector findStartNodes() const; //только для тестирования удали потом
    
private:
    BooleanMatrix nodeLinkMatrix;
    uint32_t nodeCount_;
    
    //BooleanVector findStartNodes(const BooleanMatrix& matrix) const;
    void disconnectNode(uint32_t node, BooleanMatrix& matrix) const;
};
