//
//  BinarySearchTree.cpp
//  asd2_3
//
//  Created by srnody on 19.04.2026.
//

#include "BinarySearchTree.hpp"

BinarySearchTree::BinarySearchTree() : BinaryTree() {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : BinaryTree(other) {}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this == &other) return *this;
    BinaryTree::operator=(other);
    return *this;
}

void BinarySearchTree::insert(int key) {
    TreeNode* newNode = new TreeNode(key);

    if (!root) {
        root = newNode;
        return;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr;

    while (current) {
        parent = current;

        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
}

TreeNode* BinarySearchTree::find(int key) const {
    TreeNode* current = root;
    
    while (current) {
        if (key == current->key)
            return current;
        current = (key < current->key) ? current->left : current->right;
    }
    
    return nullptr;
}

int BinarySearchTree::getMinKey() const {
    if (!root) throw std::runtime_error("Tree is empty");

    TreeNode* current = root;
    while (current->left)
        current = current->left;

    return current->key;
}

int BinarySearchTree::getMaxKey() const {
    if (!root) throw std::runtime_error("Tree is empty");

    TreeNode* current = root;
    while (current->right)
        current = current->right;

    return current->key;
}

void BinarySearchTree::inOrder(TreeNode* node, std::vector<int>& result) const {
    if (!node) return;
    inOrder(node->left, result);
    result.push_back(node->key);
    inOrder(node->right, result);
}

std::vector<int> BinarySearchTree::getAllKeys() const {
    std::vector<int> result;
    inOrder(root, result);
    return result;
}
