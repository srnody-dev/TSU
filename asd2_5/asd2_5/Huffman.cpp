//
//  Huffman.cpp
//  asd2_5
//
//  Created by srnody on 24.02.2026.
//

#include "Huffman.hpp"

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

void Huffman::build(const std::string&) {}
double Huffman::encode(const std::string&, const std::string&) { return -1; }
bool Huffman::decode(const std::string&, const std::string&) { return false; }
