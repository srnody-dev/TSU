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
    
    TreeNode* findNode(TreeNode* node, int key) const {
            if (!node) return nullptr;
            if (node->key == key) return node;

            TreeNode* left = findNode(node->left, key);
            if (left) return left;

            return findNode(node->right, key);
        }
    
    bool removeNode(TreeNode*& node, int key) {
            if (!node) return false;

            if (node->key == key) {
                clear(node);
                node = nullptr;
                return true;
            }

            return removeNode(node->left, key) || removeNode(node->right, key);
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
    
    bool remove(int key) {
            return removeNode(root, key);
        }

        TreeNode* find(int key) const {
            return findNode(root, key);
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
    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
    
    int key = 97;
        if (tree.find(key))
            std::cout << "Найден узел " << key << std::endl;
        else
            std::cout << "Узел " << key << " не найден" << std::endl;

        tree.remove(97);

        std::cout << "\nПосле удаления:\n";
        tree.print();

    
    std::cout << "\nКоличество узлов: " << tree.getNodesCount() << std::endl;
}

