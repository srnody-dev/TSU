//
//  BinaryTree.hpp
//  asd2_2
//
//  Created by srnody on 25.02.2026.
//

#pragma once
#include <functional>
#include <vector>
#include <queue>
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : key(0), left(nullptr), right(nullptr) {}

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}

    int getKey() const { return key; }
    void setKey(int k) { key = k; }
    TreeNode* getLeft() const { return left; }
    TreeNode* getRight() const { return right; }
    void setLeft(TreeNode* node) { left = node; }
    void setRight(TreeNode* node) { right = node; }
};

class BinaryTree {
protected:
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
    void getAllKeys(TreeNode* node, std::vector<int>& keys) const;
    
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    virtual ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);
    
    void clear();
    bool isEmpty() const;
    virtual void insert(int key);
    void print() const;
    int getNodesCount() const;
    TreeNode* getRoot() const;
    virtual TreeNode* find(int key) const;
    virtual bool remove(int key);
    int getHeight() const;
    virtual int getMinKey() const;
    virtual int getMaxKey() const;
    virtual std::vector<int> getAllKeys() const;
    
    class iterator {
    private:
        std::queue<TreeNode*> q;
    public:
        iterator(TreeNode* root) {
            if (root) q.push(root);
        }
        
        int& operator*() const {
            return q.front()->key;
        }
        
        iterator& operator++() {
            TreeNode* current = q.front();
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
            return *this;
        }
        
        bool operator==(const iterator& other) const {
            if (q.empty() && other.q.empty()) return true;
            if (q.empty() || other.q.empty()) return false;
            return q.front() == other.q.front();
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
    
    class const_iterator {
    private:
        std::queue<const TreeNode*> q;
    public:
        const_iterator(const TreeNode* root) {
            if (root) q.push(root);
        }
        
        const int& operator*() const {
            return q.front()->key;
        }
        
        const_iterator& operator++() {
            const TreeNode* current = q.front();
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
            return *this;
        }
        
        bool operator==(const const_iterator& other) const {
            if (q.empty() && other.q.empty()) return true;
            if (q.empty() || other.q.empty()) return false;
            return q.front() == other.q.front();
        }
        
        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };
    
    iterator begin() { return iterator(root); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(root); }
    const_iterator end() const { return const_iterator(nullptr); }
};
