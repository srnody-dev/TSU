//
//  main.cpp
//  asd2
//
//  Created by srnody on 16.12.2025.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

static const int ALPHABET_SIZE = 256;

void buildBadTable(const std::string& pattern, std::vector<int>& badChar) {
    int m = static_cast<int>(pattern.length());
    badChar.assign(ALPHABET_SIZE, m);
    
    for (int i = 0; i < m - 1; ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
}

int findFirstIndex(const std::string& text, const std::string& pattern) {
    size_t n = text.size();
    size_t m = pattern.size();

    if (m == 0 || m > n) {
        return -1;
    }

    std::vector<int> badChar;
    buildBadTable(pattern, badChar);

    size_t shift = 0;
    while (shift <= static_cast<int>(n - m)) {
        int j = static_cast<int>(m) - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            return static_cast<int>(shift);
        }

        unsigned char mismatchChar = static_cast<unsigned char>(text[shift + j]);
        int badCharShift = badChar[mismatchChar] - (static_cast<int>(m) - 1 - j);
        if (badCharShift < 1) {
            shift += 1;
        } else {
            shift += badCharShift;
        }
    }

    return -1;
}

std::vector<int> findAllIndex(const std::string& text, const std::string& pattern) {
    std::vector<int> result;

    size_t n = text.size();
    size_t m = pattern.size();

    if (m == 0 || m > n) {
        return {};
    }

    std::vector<int> badChar;
    buildBadTable(pattern, badChar);

    size_t shift = 0;
    while (shift <= static_cast<int>(n - m)) {
        int j = static_cast<int>(m) - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            result.push_back(static_cast<int>(shift));
            shift += 1;
        } else {
            unsigned char mismatchChar =
                static_cast<unsigned char>(text[shift + j]);

            int badCharShift =
                badChar[mismatchChar] - (static_cast<int>(m) - 1 - j);

            if (badCharShift < 1) {
                shift += 1;
            } else {
                shift += badCharShift;
            }
        }
    }

    return result;
}


int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string pattern = "tor";
    
    std::cout << "Text " << text<< std::endl;
    std::cout << "Search  " <<pattern << std::endl;
    int result = findFirstIndex(text, pattern);
    std::cout << "Результат первого вхождения: " << result << " (ожидается: 15)" << std::endl;
    
    std::vector<int> resultAll = findAllIndex(text, pattern);
    std::cout << "Результат всех вхождений: ";
    for (size_t i = 0; i < resultAll.size(); ++i) {
        std::cout << resultAll[i];
        std::cout << ", ";
    }
    std::cout << "(ожидается: 15, 30, 38, 89)" << std::endl;
    
    return 0;
}
