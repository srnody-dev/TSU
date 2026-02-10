//
//  main.cpp
//  asd2_1
//
//  Created by srnody on 05.02.2026.
//

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <unistd.h>

bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream out(fileName);
    if (!out.is_open()) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, maxNumberValue);

    out << numbersCount << "\n";
    for (int i = 0; i < numbersCount; i++) {
        out << dist(gen);
        if (i != numbersCount - 1) out << " ";
    }
    out << "\n";
    out.close();
    return true;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream in(fileName);
    if (!in.is_open()) return false;

    int n;
    in >> n;
    if (n <= 1) return true;

    int prev, cur;
    in >> prev;
    for (int i = 1; i < n; i++) {
        if (!(in >> cur)) return false;
        if (cur < prev) return false;
        prev = cur;
    }

    in.close();
    return true;
}

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Текущая директория: %s\n\n", cwd);
    std::string fileName = "file.txt";
    int numbersCount = 100000;
    int maxNumberValue = 1000;

    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        std::cerr << "Ошибка создания файла\n";
        return -1;
    }

    if (isFileContainsSortedArray(fileName))
        std::cout << "Файл успешно отсортирован \n";
    else
        std::cout << "Ошибка сортировки \n";

    return 0;
}
