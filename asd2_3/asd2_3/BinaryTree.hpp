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
protected:
    TreeNode* root;
    
    void clear(TreeNode* node);
    void printHorizont(TreeNode* node, int level) const;
    TreeNode* copyTree(TreeNode* node);
    int countNodes(TreeNode* node) const;
    virtual TreeNode* findNode(TreeNode* node, int key) const;
    virtual bool removeNode(TreeNode*& node, int key);
    
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    virtual ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);
        
    void clear();
    bool isEmpty() const;
    virtual void insert(int key);
    virtual void print() const;
    int getNodesCount() const;
    TreeNode* getRoot() const;
    virtual TreeNode* find(int key) const;
    virtual bool remove(int key);
};
