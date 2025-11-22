//
//  main.cpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#include "topSort.hpp"
#include <iostream>

int main() {
    
    TopSort graph(7);
    
    graph.addEdge(1, 3);
    graph.addEdge(3, 5);
    graph.addEdge(1, 2);
    graph.addEdge(2, 4);
    graph.addEdge(4, 5);
    graph.addEdge(4, 6);
    
    graph.printNodeLinkMatrix();
    
    DynamicArray<uint32_t> order = graph.sortTop();
    std::cout << std::endl;
    graph.printSortTopResult(order);
    std::cout << std::endl;
    
    return 0;
}
