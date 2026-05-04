//
//  main.cpp
//  asd2_3
//
//  Created by srnody on 23.02.2026.
//

#include "BinarySearchTree.hpp"
#include <iostream>

int main() {
    
    BinaryTree* tree = new BinarySearchTree();

    tree->insert(6);
    tree->insert(1);
    tree->insert(3);
    tree->insert(11);
    tree->insert(5);
    tree->insert(4);
    tree->insert(8);

    std::cout << "Дерево:\n";
    tree->print();

    std::cout << "Минимальный ключ: " << tree->getMinKey() << std::endl;
    std::cout << "Максимальный ключ: " << tree->getMaxKey() << std::endl;
    
    int key = 97;
    if (tree->find(key))
        std::cout << "Найден узел " << key << std::endl;
    else
        std::cout << "Узел " << key << " не найден" << std::endl;

    delete tree;
}
