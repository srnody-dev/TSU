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
    return findMinNode(root)->key;
}

int BinarySearchTree::getMaxKey() const {
    if (!root) throw std::runtime_error("Tree is empty");
    return findMaxNode(root)->key;
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

TreeNode* BinarySearchTree::findMinNode(TreeNode* node) const {
    while (node && node->left)
        node = node->left;
    return node;
}

TreeNode* BinarySearchTree::findMaxNode(TreeNode* node) const {
    while (node && node->right)
        node = node->right;
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int key) {
    if (!node) return nullptr;
    
    if (key < node->key) {
        node->left = removeRecursive(node->left, key);
    }
    else if (key > node->key) {
        node->right = removeRecursive(node->right, key);
    }
    else {
        
        if (!node->left) {
            TreeNode* rightChild = node->right;
            delete node;
            return rightChild;
        }
        
        if (!node->right) {
            TreeNode* leftChild = node->left;
            delete node;
            return leftChild;
        }
        
        TreeNode* minRight = findMinNode(node->right);
        node->key = minRight->key;
        node->right = removeRecursive(node->right, minRight->key);
    }
    
    return node;
}

bool BinarySearchTree::remove(int key) {
    if (!find(key)) return false;
    root = removeRecursive(root, key);
    return true;
}
