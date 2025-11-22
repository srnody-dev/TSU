//
//  main.cpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#include "topSort.hpp"
#include <iostream>

int main() {
    
    TopSort graph = TopSort::input();
    
    std::cout << std::endl;
    graph.printNodeLinkMatrix();
    DynamicArray<uint32_t> result = graph.sortTop();
    graph.printSortTopResult(result);
    return 0;
}
