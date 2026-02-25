//
//  BinaryTree.cpp
//  asd2_2
//
//  Created by srnody on 25.02.2026.
//

#include "BinaryTree.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

BinaryTree::BinaryTree() : root(nullptr) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

BinaryTree::BinaryTree(const BinaryTree& other) : root(nullptr) {
    root = copyTree(other.root);
}

BinaryTree::~BinaryTree() {
    clear();
}

void BinaryTree::clear(TreeNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BinaryTree::clear(){
    clear(root);
    root=nullptr;
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this == &other) return *this;
    
    clear();
    root = copyTree(other.root);
    return *this;
}

TreeNode* BinaryTree::copyTree(TreeNode* node) {
    if (!node) return nullptr;
    
    TreeNode* newNode = new TreeNode(node->key);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    
    return newNode;
}

int BinaryTree::countNodes(TreeNode* node) const {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BinaryTree::getNodesCount() const {
    return countNodes(root);
}

TreeNode* BinaryTree::getRoot() const {
    return root;
}

bool BinaryTree::isEmpty() const {
    return root == nullptr;
}

void BinaryTree::insert(int key) {
    TreeNode* newNode = new TreeNode(key);
    
    if (!root) {
        root = newNode;
        return;
    }
    
    TreeNode* current = root;
    
    while (true) {
        if (std::rand() % 2 == 0) {
            if (!current->left) {
                current->left = newNode;
                return;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

void BinaryTree::printHorizont(TreeNode* node, int level) const {
    if (!node) return;
    
    printHorizont(node->right, level + 1);
    
    for (int i = 0; i < level; i++) std::cout << "\t";
    std::cout << node->key << std::endl;
    
    printHorizont(node->left, level + 1);
}

void BinaryTree::print() const {
    printHorizont(root, 0);
}
