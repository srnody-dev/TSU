//
//  main.cpp
//  asd2_2
//
//  Created by srnody on 11.02.2026.
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

    TreeNode* copyTree(TreeNode* node) {
        if (!node) return nullptr;
        TreeNode* newNode = new TreeNode(node->key);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    
    int countNodes(TreeNode* node) const {
            if (!node) return 0;
            return 1 + countNodes(node->left) + countNodes(node->right);
        }


public:

    BinaryTree() : root(nullptr) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    BinaryTree(const BinaryTree& other) {
        root = copyTree(other.root);
    }

    ~BinaryTree() {
        clear();
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this == &other) return *this;

        clear();
        root = copyTree(other.root);
        return *this;
    }

    TreeNode* getRoot() const {
        return root;
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
    
    int getNodesCount() const {
            return countNodes(root);
        }

};


int main() {
    BinaryTree tree;

    tree.insert(799);
    tree.insert(77);
    tree.insert(777);
    tree.insert(97);
    tree.insert(197);
    
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;

}

