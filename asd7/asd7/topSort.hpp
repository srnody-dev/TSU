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
    
    DynamicArray<uint32_t> sortTop() const;
    void printSortTopResult(const DynamicArray<uint32_t>& result) const;

    static TopSort input();
    
private:
    BooleanMatrix nodeLinkMatrix;
    uint32_t nodeCount_;
    BooleanVector BuildV1(const BooleanMatrix& currentMatrix) const;
};
