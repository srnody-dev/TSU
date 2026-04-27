//
//  Huffman.hpp
//  asd2_5
//
//  Created by srnody on 24.02.2026.
//

#pragma once
#include <unordered_map>
#include <string>

class Huffman {
private:
    struct HuffmanNode {
        std::string ch;
        size_t freq;
        HuffmanNode* left;
        HuffmanNode* right;

        HuffmanNode(const std::string& s, size_t f)
            : ch(s), freq(f), left(nullptr), right(nullptr) {}

        HuffmanNode(HuffmanNode* l, HuffmanNode* r)
            : ch(l->ch + r->ch), freq(l->freq + r->freq), left(l), right(r) {}
    };

    HuffmanNode* root = nullptr;
    std::unordered_map<char, std::string> table;

    void clear(HuffmanNode* n);
    void generateCodes(HuffmanNode* node, const std::string& code);
public:
    Huffman();
    ~Huffman();

    void build(const std::string& text);
    double encode(const std::string& in, std::string& out);
    bool decode(const std::string& in, std::string& out);
};
