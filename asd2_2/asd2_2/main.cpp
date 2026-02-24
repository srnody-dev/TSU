//
//  main.cpp
//  asd2_2
//
//  Created by srnody on 24.02.2026.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

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
    
    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    void printHorizont(TreeNode* node, int level) const {
        if (!node) return;
        
        printHorizont(node->right, level + 1);
        
        for (int i = 0; i < level; i++) std::cout << "      ";
        std::cout << node->key << std::endl;
        
        printHorizont(node->left, level + 1);
    }
    
    
public:
    
    BinaryTree() : root(nullptr) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }
    
    ~BinaryTree() {
        clear();
    }
    
    void clear() {
        clear(root);
        root = nullptr;
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }
    
    
    void insert(int key) {
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
    
    void print() const {
        printHorizont(root, 0);
    }
};


int main() {
    BinaryTree tree;

    tree.insert(799);
    tree.insert(77);
    tree.insert(777);
    tree.insert(97);
    tree.insert(197);
    
    std::cout << "Дерево:\n";
        tree.print();
}

