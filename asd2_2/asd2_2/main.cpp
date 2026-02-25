//
//  main.cpp
//  asd2_2
//
//  Created by srnody on 24.02.2026.
//

#include <iostream>
#include "BinaryTree.hpp"

int main() {
    BinaryTree tree;

    tree.insert(799);
    tree.insert(77);
    tree.insert(777);
    tree.insert(97);
    tree.insert(197);
    
    std::cout << "Дерево:\n";
        tree.print();
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
    
    BinaryTree tree2=tree;
    std::cout << "\nКопия дерева:\n";
        tree2.print();
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
}

