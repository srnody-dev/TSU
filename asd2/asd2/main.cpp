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
    int m = pattern.length();
    badChar.assign(ALPHABET_SIZE, m);
    
    for (int i = 0; i < m - 1; ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
}

int findFirstIndex(const std::string& text, const std::string& pattern) {
    size_t n = text.size();
    size_t m = pattern.size();

    if (m == 0) return 0;
    if (m > n) return -1;

    std::vector<int> badChar;
    buildBadTable(pattern, badChar);

    int shift = 0;
    while (shift <= static_cast<int>(n - m)) {
        int j = static_cast<int>(m) - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            return shift;
        }

        unsigned char mismatchChar = static_cast<unsigned char>(text[shift + j]);
        int badCharShift = badChar[mismatchChar] - (static_cast<int>(m) - 1 - j);
        shift += std::max(1, badCharShift);
    }

    return -1;
}


int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string pattern = "tor";
    
    std::cout << "поиск 'tor'" << std::endl;
    int result = findFirstIndex(text, pattern);
    std::cout << "Результат: " << result << " (ожидается: 15)" << std::endl;
    
    return 0;
}
