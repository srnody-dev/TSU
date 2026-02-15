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

void splitFile(const std::string &inputFile, const std::string &outputFile1, const std::string &outputFile2, int p) {
    std::ifstream in(inputFile);
    std::ofstream out[2] = { std::ofstream(outputFile1), std::ofstream(outputFile2) };
    int n;
    in >> n;
    int currentOutputIndex = 0;
    int currentNumber;
    int numbersCount[2] = {0,0};

    while (in >> currentNumber) {
        for (int i = 0; i < p; i++) {
            if (in.eof()) break;
            out[currentOutputIndex] << currentNumber << " ";
            numbersCount[currentOutputIndex]++;
            if (!(in >> currentNumber)) break;
        }
        currentOutputIndex = 1 - currentOutputIndex;
    }

    out[0].close();
    out[1].close();
}

void mergeFiles(const std::string &inputFile1, const std::string &inputFile2,
                const std::string &outputFile1, const std::string &outputFile2, int p) {
    std::ifstream in[2] = { std::ifstream(inputFile1), std::ifstream(inputFile2) };
    std::ofstream out[2] = { std::ofstream(outputFile1), std::ofstream(outputFile2) };

    int currentNumbers[2], hasNumbers[2];
    hasNumbers[0] = (in[0] >> currentNumbers[0]) ? 1 : 0;
    hasNumbers[1] = (in[1] >> currentNumbers[1]) ? 1 : 0;

    int currentOutputIndex = 0;
    while (hasNumbers[0] || hasNumbers[1]) {
        int i = 0, j = 0;
        while (i < p && j < p && hasNumbers[0] && hasNumbers[1]) {
            if (currentNumbers[0] <= currentNumbers[1]) {
                out[currentOutputIndex] << currentNumbers[0] << " ";
                hasNumbers[0] = (in[0] >> currentNumbers[0]) ? 1 : 0;
                i++;
            } else {
                out[currentOutputIndex] << currentNumbers[1] << " ";
                hasNumbers[1] = (in[1] >> currentNumbers[1]) ? 1 : 0;
                j++;
            }
        }
        while (i < p && hasNumbers[0]) {
            out[currentOutputIndex] << currentNumbers[0] << " ";
            hasNumbers[0] = (in[0] >> currentNumbers[0]) ? 1 : 0;
            i++;
        }
        while (j < p && hasNumbers[1]) {
            out[currentOutputIndex] << currentNumbers[1] << " ";
            hasNumbers[1] = (in[1] >> currentNumbers[1]) ? 1 : 0;
            j++;
        }
        currentOutputIndex = 1 - currentOutputIndex;
    }

    in[0].close();
    in[1].close();
    out[0].close();
    out[1].close();
}

void directMergeSort(const std::string &inputFile) {
    std::string A = inputFile;
    std::string B = "B.txt";
    std::string C = "C.txt";
    std::string D = "D.txt";

    int p = 1;
    splitFile(A, C, D, p);

    bool sortingComplete = false;
    while (!sortingComplete) {
        mergeFiles(C, D, A, B, p);
        p *= 2;
        std::ifstream checkFileB(B);
        if (checkFileB.peek() == std::ifstream::traits_type::eof()) break;

        mergeFiles(A, B, C, D, p);
        p *= 2;
        std::ifstream chechFileD(D);
        if (chechFileD.peek() == std::ifstream::traits_type::eof()) break;
    }
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
    
    directMergeSort(fileName);

    if (isFileContainsSortedArray(fileName))
        std::cout << "Файл успешно отсортирован \n";
    else
        std::cout << "Ошибка сортировки \n";

    return 0;
    
}
