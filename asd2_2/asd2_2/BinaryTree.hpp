//
//  BinaryTree.hpp
//  asd2_2
//
//  Created by srnody on 25.02.2026.
//

#pragma once
#include <functional>
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : key(0), left(nullptr), right(nullptr) {}

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}

    int getKey() const { return key; }
    TreeNode* getLeft() const { return left; }
    TreeNode* getRight() const { return right; }
};

class BinaryTree {
private:
    TreeNode* root;
    
    void clear(TreeNode* node);
    void printHorizont(TreeNode* node, int level) const;
    TreeNode* copyTree(TreeNode* node);
    int countNodes(TreeNode* node) const;
    TreeNode* findNode(TreeNode* node,int key) const;
    bool removeNode(TreeNode*& node,int key);
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* findMax(TreeNode* node) const;
    TreeNode* findExtremum(TreeNode* node, std::function<bool(int, int)> compare) const;
    int getHeight(TreeNode* node) const;
    
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);
    
    void clear();
    bool isEmpty() const;
    void insert(int key);
    void print() const;
    int getNodesCount() const;
    TreeNode* getRoot() const;
    TreeNode* find(int key) const;
    bool remove(int key);
    int getHeight() const;
};

