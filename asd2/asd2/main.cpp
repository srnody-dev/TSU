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
    badChar.resize(ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        badChar[i] = m;
    }
    for (int i = 0; i < m - 1; ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
}

std::vector<int> boyerMooreSearch(
    const std::string& text,
    const std::string& pattern,
    size_t left,
    size_t right
) {
    std::vector<int> result;

    size_t n = text.size();
    size_t m = pattern.size();

    if (m == 0 || left > right || right >= n) return result;
    if (right - left + 1 < m) return result;

    std::vector<int> badChar;
    buildBadTable(pattern, badChar);

    size_t shift = left;
    size_t bound = right - m + 1;

    while (shift <= bound) {
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

            shift += (badCharShift > 0 ? badCharShift : 1);
        }
    }

    return result;
}

int findFirstIndex(const std::string& text, const std::string& pattern) {
    auto res = boyerMooreSearch(text, pattern, 0, text.size() - 1);
    return res.empty() ? -1 : res[0];
}

std::vector<int> findAllIndex(
    const std::string& text,
    const std::string& pattern
) {
    return boyerMooreSearch(text, pattern, 0, text.size() - 1);
}

std::vector<int> findRangeIndex(
    const std::string& text,
    const std::string& pattern,
    int left,
    int right
) {
    if (left < 0 || right < 0) return {};
    return boyerMooreSearch(
        text,
        pattern,
        static_cast<size_t>(left),
        static_cast<size_t>(right)
    );
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
    
    auto ranged = findRangeIndex(text, pattern, 28, 36);
    std::cout << "Результат вхождения в диапозоне 28-36: " << std::endl;
    for (int i : ranged) std::cout << i << " ";
    std::cout << " (ожидается: 30)" << std::endl;
    return 0;
}
