//
//  main.cpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#include "topSort.hpp"
#include <iostream>

int main() {
    
    TopSort graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    
    graph.printNodeLinkMatrix();
    
    try {
        DynamicArray<uint32_t> order = graph.sortTop();
        graph.printSortTopResult(order);
    } catch (const std::exception& e) {
        std::cout << "Ошибка сортировки: " << e.what() << std::endl;
    }
    
    return 0;
}
