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
    
    generateCodes(root, "");
}

void Huffman::generateCodes(HuffmanNode* node, const std::string& code) {
    if (!node) return;

    if (!node->left && !node->right) {
        table[node->ch[0]] = code;
        std::cout << node->ch << " -> " << code << "\n";
        return;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}
    
double Huffman::encode(const std::string& in , std::string& out) {
    if (!root) build(in);
    
    out.clear();
    
    for (char c : in) {
        out += table[c];
    }

    double originalSize = in.size() * 8.0;
    double encodedSize = out.size();
    
    std::cout << "Encoded string:\n" << out << "\n";

    return encodedSize ? originalSize / encodedSize : 0;
}

bool Huffman::decode(const std::string& in, std::string& out) {
    out.clear();
    if (!root) {
        std::cout << "Huffman tree is empty\n";
        return false;
    }

    HuffmanNode* node = root;
    std::string code;

    for (char c : in) {
        code += c;
        node = (c == '0') ? node->left : node->right;

        if (!node) {
            std::cout << "Invalid code: " << code << "\n";
            return false;
        }

        if (!node->left && !node->right) {
            out += node->ch[0];
            node = root;
            code.clear();
        }
    }

    if (node != root) {
        std::cout << "Invalid code ending: " << out << "\n";
        return false;
    }

    std::cout << "Decoded string:\n" << out << "\n";
    return true;
}
