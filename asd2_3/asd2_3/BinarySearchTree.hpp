//
//  BinarySearchTree.hpp
//  asd2_3
//
//  Created by srnody on 19.04.2026.
//

#pragma once
#include "BinaryTree.hpp"
#include <stack>

class BinarySearchTree : public BinaryTree {
  private:
    void inOrder(TreeNode *node, std::vector<int> &result) const;
    TreeNode *removeRecursive(TreeNode *node, int key);
    TreeNode *findMinNode(TreeNode *node) const;
    TreeNode *findMaxNode(TreeNode *node) const;

  public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &other);

    BinarySearchTree &operator=(const BinarySearchTree &other);

    void insert(int key) override;
    TreeNode *find(int key) const override;
    bool remove(int key) override;
    int getMinKey() const override;
    int getMaxKey() const override;
    std::vector<int> getAllKeys() const override;

    class Iterator {
      private:
        std::stack<TreeNode *> stack_;
        TreeNode *current_;

        void pushLeftPath(TreeNode *node) {
            while (node != nullptr) {
                stack_.push(node);
                node = node->getLeft();
            }
        }

      public:
        Iterator(TreeNode *root = nullptr, bool end = false) {
            if (end) {
                current_ = nullptr;
                return;
            }

            current_ = root;
            pushLeftPath(current_);

            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }
        }

        Iterator &operator++() {
            if (current_ == nullptr)
                return *this;

            if (current_->getRight() != nullptr) {
                TreeNode *node = current_->getRight();
                pushLeftPath(node);
            }

            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }

            return *this;
        }

        int operator*() const { return current_->getKey(); }

        bool operator==(const Iterator &other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }
    };

    class ConstIterator {
      private:
        std::stack<const TreeNode *> stack_;
        const TreeNode *current_;

        void pushLeftPath(const TreeNode *node) {
            while (node != nullptr) {
                stack_.push(node);
                node = node->getLeft();
            }
        }

      public:
        ConstIterator(const TreeNode *root = nullptr, bool end = false) {
            if (end) {
                current_ = nullptr;
                return;
            }

            current_ = root;
            pushLeftPath(current_);

            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }
        }

        ConstIterator &operator++() {
            if (current_ == nullptr)
                return *this;

            if (current_->getRight() != nullptr) {
                const TreeNode *node = current_->getRight();
                pushLeftPath(node);
            }

            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }

            return *this;
        }

        int operator*() const { return current_->getKey(); }

        bool operator==(const ConstIterator &other) const {
            return current_ == other.current_;
        }

        bool operator!=(const ConstIterator &other) const {
            return !(*this == other);
        }
    };

    Iterator begin() { return Iterator(root); }
    Iterator end() { return Iterator(root, true); }
    ConstIterator begin() const { return ConstIterator(root); }
    ConstIterator end() const { return ConstIterator(root, true); }
};
