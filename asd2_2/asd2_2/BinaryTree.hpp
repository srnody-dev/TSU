//
//  BinaryTree.hpp
//  asd2_2
//
//  Created by srnody on 25.02.2026.
//

#pragma once
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : key(0), left(nullptr), right(nullptr) {}

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
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
};

