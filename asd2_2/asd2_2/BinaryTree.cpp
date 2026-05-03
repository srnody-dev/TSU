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
        TreeNode*& slot = (std::rand() % 2 == 0) ? current->left : current->right;
        if (!slot) {
            slot = newNode;
            return;
        }
        current = slot;
    }
}

bool BinaryTree::removeNode(TreeNode*& node, int key) {
    if (!node) return false;

    if (node->key == key) {
        clear(node);
        node = nullptr;
        return true;
    }

    return removeNode(node->left, key) || removeNode(node->right, key);
}

bool BinaryTree::remove(int key) {
    return removeNode(root, key);
}

TreeNode* BinaryTree::findNode(TreeNode* node, int key) const {
    if (!node || node->key == key)
        return node;

    TreeNode* result = findNode(node->left, key);
    return result ? result : findNode(node->right, key);
}

TreeNode* BinaryTree::find(int key) const {
    return findNode(root, key);
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

TreeNode* BinaryTree::findExtremum(TreeNode* node, std::function<bool(int, int)> compare) const {
    if (!node) return nullptr;
    
    TreeNode* extremumNode = node;
    TreeNode* leftExtremum = findExtremum(node->getLeft(), compare);
    TreeNode* rightExtremum = findExtremum(node->getRight(), compare);
    
    if (leftExtremum && compare(leftExtremum->getKey(), extremumNode->getKey()))
        extremumNode = leftExtremum;
    if (rightExtremum && compare(rightExtremum->getKey(), extremumNode->getKey()))
        extremumNode = rightExtremum;
    
    return extremumNode;
}

TreeNode* BinaryTree::findMin(TreeNode* node) const {
    return findExtremum(node, [](int a, int b) { return a < b; });
}

TreeNode* BinaryTree::findMax(TreeNode* node) const {
    return findExtremum(node, [](int a, int b) { return a > b; });
}

int BinaryTree::getHeight(TreeNode* node) const {
    if (!node) return -1;
    
    int leftHeight = getHeight(node->getLeft());
    int rightHeight = getHeight(node->getRight());
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int BinaryTree::getHeight() const {
    return getHeight(root);
}

int BinaryTree::getMinKey() const {
    TreeNode* minNode = findMin(root);
    if (!minNode) throw std::runtime_error("Дерево пустое");
    return minNode->getKey();
}

int BinaryTree::getMaxKey() const {
    TreeNode* maxNode = findMax(root);
    if (!maxNode) throw std::runtime_error("Дерево пустое");
    return maxNode->getKey();
}


void BinaryTree::getAllKeys(TreeNode* node, std::vector<int>& keys) const {
    if (!node) return;
    
    getAllKeys(node->getLeft(), keys);
    keys.push_back(node->getKey());
    getAllKeys(node->getRight(), keys);
}

std::vector<int> BinaryTree::getAllKeys() const {
    std::vector<int> keys;
    getAllKeys(root, keys);
    
    for (size_t i = 0; i < keys.size(); i++) {
        for (size_t j = i + 1; j < keys.size(); j++) {
            if (keys[i] > keys[j]) {
                int temp = keys[i];
                keys[i] = keys[j];
                keys[j] = temp;
            }
        }
    }
    
    return keys;
}
