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

enum class MergeSortType {
    Direct,
    Natural
};

bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream out(fileName);
    if (!out.is_open()) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, maxNumberValue);

    for (int i = 0; i < numbersCount; i++) {
        out << dist(gen) << " ";
    }
    out.close();
    return true;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream in(fileName);
    if (!in.is_open()) return false;

    int prev, cur;
    if (!(in >> prev)) return true;
    while (in >> cur) {
        if (cur < prev) return false;
        prev = cur;
    }

    in.close();
    return true;
}

void splitFileDirect(const std::string &inputFile, const std::string &outputFile1, const std::string &outputFile2, int p) {
    std::ifstream in(inputFile);
    std::ofstream out[2] = { std::ofstream(outputFile1), std::ofstream(outputFile2) };
    
    int current,outIndex = 0;

    while (in >> current) {
        for (int i = 0; i < p; i++) {
            out[outIndex] << current << " ";
            if (!(in >> current)) break;
        }
        outIndex = (outIndex == 0) ? 1 : 0;
    }
    
    in.close();
    out[0].close();
    out[1].close();
}

void mergeFilesDirect(const std::string &inputFile1, const std::string &inputFile2,
                const std::string &outputFile1, const std::string &outputFile2, int p) {
    std::ifstream in[2] = { std::ifstream(inputFile1), std::ifstream(inputFile2) };
    std::ofstream out[2] = { std::ofstream(outputFile1), std::ofstream(outputFile2) };

    int current[2];
    bool hasValue[2];
    hasValue[0] = (in[0] >> current[0]) ? 1 : 0;
    hasValue[1] = (in[1] >> current[1]) ? 1 : 0;

    int outIndex = 0;
    while (hasValue[0] || hasValue[1]) {
        int i = 0, j = 0;
        while (i < p && j < p && hasValue[0] && hasValue[1]) {
            if (current[0] <= current[1]) {
                out[outIndex] << current[0] << " ";
                hasValue[0] = (in[0] >> current[0]) ? 1 : 0;
                i++;
            } else {
                out[outIndex] << current[1] << " ";
                hasValue[1] = (in[1] >> current[1]) ? 1 : 0;
                j++;
            }
        }
        while (i < p && hasValue[0]) {
            out[outIndex] << current[0] << " ";
            hasValue[0] = (in[0] >> current[0]) ? 1 : 0;
            i++;
        }
        while (j < p && hasValue[1]) {
            out[outIndex] << current[1] << " ";
            hasValue[1] = (in[1] >> current[1]) ? 1 : 0;
            j++;
        }
        outIndex = (outIndex == 0) ? 1 : 0;
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
    splitFileDirect(A, C, D, p);

    while (true) {
        mergeFilesDirect(C, D, A, B, p);
        p *= 2;
        std::ifstream checkFileB(B);
        if (checkFileB.peek() == std::ifstream::traits_type::eof()) break;

        mergeFilesDirect(A, B, C, D, p);
        p *= 2;
        std::ifstream chechFileD(D);
        if (chechFileD.peek() == std::ifstream::traits_type::eof()) break;
    }
}


void splitFileNatural(const std::string &input, const std::string &out1, const std::string &out2) {
    std::ifstream in(input);
    std::ofstream out[2] = { std::ofstream(out1), std::ofstream(out2) };


    int current, next;
    if (!(in >> current)) return;

    int outIndex = 0;

    while (true) {
        out[outIndex] << current << " ";
        if (!(in >> next)) break;

        if (current > next)
            outIndex = (outIndex == 0) ? 1 : 0;
        current = next;
    }

    in.close();
    out[0].close();
    out[1].close();
}

void mergeFilesNatural(const std::string &in1, const std::string &in2,
                  const std::string &out1, const std::string &out2) {
    std::ifstream in[2] = { std::ifstream(in1), std::ifstream(in2) };
    std::ofstream out[2] = { std::ofstream(out1), std::ofstream(out2) };


    int current[2], nextValuee[2];
    bool hasValue[2];

    hasValue[0] = (in[0] >> current[0]) ? 1 : 0;
    hasValue[1] = (in[1] >> current[1]) ? 1 : 0;

    int outIndex = 0;

    while (hasValue[0] && hasValue[1]) {
        int inputIndex = (current[0] <= current[1]) ? 0 : 1;

        out[outIndex] << current[inputIndex] << " ";

        if (in[inputIndex] >> nextValuee[inputIndex]) {
            if (nextValuee[inputIndex] < current[inputIndex]) {
                inputIndex = (inputIndex == 0) ? 1 : 0;


                out[outIndex] << current[inputIndex] << " ";
                if (!(in[inputIndex] >> nextValuee[inputIndex]))
                    hasValue[inputIndex] = 0;

                while (hasValue[inputIndex] && nextValuee[inputIndex] >= current[inputIndex]) {
                    current[inputIndex] = nextValuee[inputIndex];
                    out[outIndex] << current[inputIndex] << " ";
                    if (!(in[inputIndex] >> nextValuee[inputIndex])) {
                        hasValue[inputIndex] = 0; break;
                    }
                }

                if (hasValue[0]) current[0] = nextValuee[0];
                if (hasValue[1]) current[1] = nextValuee[1];

                outIndex = (outIndex == 0) ? 1 : 0;

            } else {
                current[inputIndex] = nextValuee[inputIndex];
            }
        } else {
            hasValue[inputIndex] = 0;
        }
    }

    for (int i = 0; i < 2; ++i) {
        while (hasValue[i]) {
            out[outIndex] << current[i] << " ";
            if (in[i] >> nextValuee[i]) {
                if (nextValuee[i] < current[i]) outIndex = (outIndex == 0) ? 1 : 0;
                current[i] = nextValuee[i];
            } else {
                hasValue[i] = 0;
            }
        }
    }

    in[0].close();
    in[1].close();
    out[0].close();
    out[1].close();
}

void naturalMergeSort(const std::string &inputFile) {
    std::string A = inputFile;
    std::string B = "B.txt";
    std::string C = "C.txt";
    std::string D = "D.txt";

    splitFileNatural(A, C, D);

    
    std::ifstream check(D);
    if (check.peek() == std::ifstream::traits_type::eof())
        return;
    

    while (true) {
        mergeFilesNatural(C, D, A, B);

        std::ifstream checkB(B);
        if (checkB.peek() == std::ifstream::traits_type::eof())
            break;

        mergeFilesNatural(A, B, C, D);

        std::ifstream checkD(D);
        if (checkD.peek() == std::ifstream::traits_type::eof())
            break;
    }
}

void mergeSort(const std::string& fileName, MergeSortType type) {
    if (type == MergeSortType::Direct)
           directMergeSort(fileName);
       else
           naturalMergeSort(fileName);
}


int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Текущая директория: %s\n\n", cwd);
    std::string fileName = "file.txt";
    int numbersCount = 10000;
    int maxNumberValue = 100000;

    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        std::cerr << "Ошибка создания файла\n";
        return -1;
    }
    
    //mergeSort(fileName, MergeSortType::Natural);
    
    mergeSort(fileName, MergeSortType::Direct);


    if (isFileContainsSortedArray(fileName))
        std::cout << "Файл успешно отсортирован \n";
    else
        std::cout << "Ошибка сортировки \n";

    return 0;
    
}
