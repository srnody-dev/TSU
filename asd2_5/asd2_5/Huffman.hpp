//
//  Huffman.hpp
//  asd2_5
//
//  Created by srnody on 24.02.2026.
//

#pragma once
#include <unordered_map>
#include <string>
#include "booleanVector.hpp"

class Huffman {
private:
    struct HuffmanNode {
        char ch;
        size_t freq;
        HuffmanNode* left;
        HuffmanNode* right;

        HuffmanNode(char c, size_t f)
            : ch(c), freq(f), left(nullptr), right(nullptr) {}

        HuffmanNode(HuffmanNode* l, HuffmanNode* r)
            : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
    };

    HuffmanNode* root = nullptr;
    std::unordered_map<char, BooleanVector> table;

    void clear(HuffmanNode* n);

public:
    Huffman();
    ~Huffman();

    void build(const std::string& text);
    double encode(const std::string& in, const std::string& out);
    bool decode(const std::string& in, const std::string& out);
};
