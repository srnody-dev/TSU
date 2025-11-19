//
//  main.cpp
//  asd7
//
//  Created by srnody on 18.11.2025.
//

#include "topSort.hpp"
#include <iostream>

int main() {
    
    TopSort graph(9);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(6, 7);
    graph.addEdge(7, 8);
    
    graph.printNodeLinkMatrix();
    std::cout << std::endl;
    
    BooleanVector starts = graph.findStartNodes();
            
    std::cout << "Стартовые узлы: ";
    for (uint32_t i = 0; i < 9; ++i) {
        if (starts[i]) std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
