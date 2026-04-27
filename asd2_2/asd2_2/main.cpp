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
    
    int key = 97;
    if (tree.find(key))
        std::cout << "Найден узел " << key << std::endl;
    else
        std::cout << "Узел " << key << " не найден" << std::endl;
    
    std::vector<int> keys = tree.getAllKeys();
    std::cout << "\nВсе ключи по возрастанию: ";
    for (int key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    
    int key2 = 777;
    tree.remove(key2);
    std::cout << "\nПосле удаления узла "<< key2 << ":\n";
    tree.print();
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
    std::cout << "\nВысота дерева: " << tree.getHeight() << std::endl;
    
    std::cout << "Минимальный ключ: " << tree.getMinKey() << std::endl;
    std::cout << "Максимальный ключ: " << tree.getMaxKey() << std::endl;
    
    BinaryTree tree2=tree;
    std::cout << "\nКопия дерева:\n";
    tree2.print();
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
}

