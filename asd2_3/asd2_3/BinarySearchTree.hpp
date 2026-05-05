//
//  BinarySearchTree.hpp
//  asd2_3
//
//  Created by srnody on 19.04.2026.
//

#pragma once
#include "BinaryTree.hpp"

class BinarySearchTree : public BinaryTree {
private:
    void inOrder(TreeNode* node, std::vector<int>& result) const;
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);

    BinarySearchTree& operator=(const BinarySearchTree& other);

    void insert(int key) override;
    TreeNode* find(int key) const override;

    int getMinKey() const override;
    int getMaxKey() const override;
    std::vector<int> getAllKeys() const override;

};
