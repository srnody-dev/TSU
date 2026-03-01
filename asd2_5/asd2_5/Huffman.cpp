//
//  Huffman.cpp
//  asd2_5
//
//  Created by srnody on 24.02.2026.
//

#include "Huffman.hpp"
#include <iostream>

Huffman::Huffman() {}

Huffman::~Huffman() {
    clear(root);
}

void Huffman::clear(HuffmanNode* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

void Huffman::build(const std::string& text) {
    clear(root);
    root = nullptr;
    table.clear();
    
    if (text.empty()) return;
    
    std::unordered_map<char, size_t> freq;
    for (char c : text)
        freq[c]++;
    
    std::cout << "Частота:\n";
    for (auto& pair : freq)
        std::cout << "'" << pair.first << "' : " << pair.second << "\n";
    
    auto compareNodes = [](HuffmanNode* a, HuffmanNode* b)
    {
        return a->freq > b->freq;
    };
    
    std::priority_queue<HuffmanNode*,std::vector<HuffmanNode*>,decltype(compareNodes)> nodeQueue(compareNodes);
    
    for (auto& pair : freq){
        HuffmanNode* node = new HuffmanNode(std::string(1, pair.first), pair.second);
        nodeQueue.push(node);
    }
    
    while (nodeQueue.size() > 1)
    {
        HuffmanNode* left = nodeQueue.top(); nodeQueue.pop();
        HuffmanNode* right = nodeQueue.top(); nodeQueue.pop();
        nodeQueue.push(new HuffmanNode(left, right));
    }
    
    root = nodeQueue.top();
    std::cout << "Root node: [" << root->ch << ":" << root->freq << "]\n";
}
    
double Huffman::encode(const std::string&, std::string&) { return -1; }
bool Huffman::decode(const std::string&, std::string&) { return false; }
