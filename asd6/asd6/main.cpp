//
//  main.cpp
//  asd6
//
//  Created by srnody on 11.11.2025.
//

#include <iostream>
#include <stdio.h>
#include <random>
#include <unistd.h>
#include <cstddef>

using namespace std;

const int test_Arrays = 9;

struct TestArray {
    int* data;
    size_t size;
    char filename[100];
};

TestArray testArrays[test_Arrays];
size_t testArraysCount = 0;

void bitSort(int A[], size_t n) {
    if (n <= 1) return;
    
    const size_t t = sizeof(int) * 8;
    int* A0 = new int[n];
    int* A1 = new int[n];
    size_t n0, n1;
    
    for (size_t k = 0; k < t - 1; k++) {
        n0 = 0; n1 = 0;
        
        for (size_t i = 0; i < n; i++) {
            if (A[i] & (1 << k)) {
                A1[n1] = A[i];
                n1++;
            } else {
                A0[n0] = A[i];
                n0++;
            }
        }
        
        for (size_t i = 0; i < n0; i++) {
            A[i] = A0[i];
        }
        for (size_t i = 0; i < n1; i++) {
            A[n0 + i] = A1[i];
        }
    }
    
    delete[] A0;
    delete[] A1;
}

void bitSortMix(int A[], size_t n) {
    if (n <= 1) return;
    
    int* Aminus = new int[n];
    int* Aplus = new int[n];
    size_t Nm = 0, Np = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (A[i] < 0) {
            Aminus[Nm] = A[i];
            Nm++;
        } else {
            Aplus[Np] = A[i];
            Np++;
        }
    }
    
    bitSort(Aminus, Nm);
    bitSort(Aplus, Np);
    
    for (size_t i = 0; i < Nm; i++) {
        A[i] = Aminus[i];
    }
    for (size_t i = 0; i < Np; i++) {
        A[Nm + i] = Aplus[i];
    }
    
    delete[] Aminus;
    delete[] Aplus;
}

void bitSortInvert(int A[], size_t n) {
    if (n <= 1) return;
    
    const size_t t = sizeof(int) * 8;
    int* A0 = new int[n];
    int* A1 = new int[n];
    size_t n0, n1;
    
    for (size_t i = 0; i < n; i++) {
        A[i] ^= (1 << (t-1));
    }
    
    for (size_t k = 0; k < t; k++) {
        n0 = 0; n1 = 0;
        
        for (size_t i = 0; i < n; i++) {
            if (A[i] & (1 << k)) {
                A1[n1] = A[i];
                n1++;
            } else {
                A0[n0] = A[i];
                n0++;
            }
        }
        
        for (size_t i = 0; i < n0; i++) {
            A[i] = A0[i];
        }
        for (size_t i = 0; i < n1; i++) {
            A[n0 + i] = A1[i];
        }
    }
    
    for (size_t i = 0; i < n; i++) {
        A[i] ^= (1 << (t-1));
    }
    
    delete[] A0;
    delete[] A1;
}

inline bool isSorted(const int arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

size_t loadArrayFromFile(int arr[], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }
    
    int n;
    fscanf(file, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    
    fclose(file);
    return n;
}

void loadAllTestArrays() {
    int sizes[] = {10000, 100000, 1000000};
    const char* rangeNames[] = {"-10_10", "-1000_1000", "-100000_100000"};
    
    testArraysCount = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (testArraysCount >= test_Arrays) break;
            
            char filename[100];
            snprintf(filename, sizeof(filename),
                    "testArray_size_%d_range_%s.txt", sizes[i], rangeNames[j]);
            
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                printf("Файл %s не найден, пропускаем\n", filename);
                continue;
            }
            fclose(file);
            
            int* arr = (int*)malloc(sizes[i] * sizeof(int));
            if (arr == NULL) {
                printf("Ошибка памяти для %s\n", filename);
                continue;
            }
            
            size_t n = loadArrayFromFile(arr, filename);
            if (n > 0) {
                testArrays[testArraysCount].data = arr;
                testArrays[testArraysCount].size = n;
                strcpy(testArrays[testArraysCount].filename, filename);
                testArraysCount++;
            } else {
                free(arr);
            }
        }
    }
}
 
void testSorting(const TestArray* testArray, int runs) {
    printf("Тест: %s (%zu элементов)\n", testArray->filename, testArray->size);
    
    double totalBitMix = 0, totalBitInvert = 0;
    bool totalBitMixCorrect = true, totalBitInvertCorrect = true;

    int* arrBitMix = (int*)malloc(testArray->size * sizeof(int));
    int* arrBitInvert = (int*)malloc(testArray->size * sizeof(int));
    
    if (arrBitMix == NULL || arrBitInvert == NULL) {
        printf("Ошибка памяти для теста\n");
        if (arrBitMix) free(arrBitMix);
        if (arrBitInvert) free(arrBitInvert);
        return;
    }
    
    // Bit Mix Sort
    for (int i = 0; i < runs; i++) {
        memcpy(arrBitMix, testArray->data, testArray->size * sizeof(int));
        
        clock_t start = clock();
        bitSortMix(arrBitMix, testArray->size);
        clock_t end = clock();
        
        totalBitMix += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arrBitMix, testArray->size)) {
            totalBitMixCorrect = false;
            printf("Ошибка: массив totalBitMix не отсортирован!\n");
        }
    }
    
    // Bit Invert Sort
    for (int i = 0; i < runs; i++) {
        memcpy(arrBitInvert, testArray->data, testArray->size * sizeof(int));
        
        clock_t start = clock();
        bitSortInvert(arrBitInvert, testArray->size);
        clock_t end = clock();
        
        totalBitInvert += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arrBitMix, testArray->size)) {
            totalBitInvertCorrect = false;
            printf("Ошибка: массив bitSortInvert не отсортирован!\n");
        }
    }
    
    free(arrBitMix);
    free(arrBitInvert);
    
    double avgBitMix = totalBitMix / runs;
    double avgBitInvert = totalBitInvert / runs;
    
    printf("Результаты %d запусков:\n", runs);
    printf("Bit Mix Sort: %.6f секунд (Отсортирован: %s)\n",
           avgBitMix, totalBitMixCorrect ? "Да" : "НЕТ!");
    printf("Bit Invert Sort: %.6f секунд (Отсортирован: %s)\n",
           avgBitInvert, totalBitInvertCorrect ? "Да" : "НЕТ!");
    printf("\n");
}

void freeAllTestArrays() {
    for (size_t i = 0; i < testArraysCount; i++) {
        if (testArrays[i].data != NULL) {
            free(testArrays[i].data);
            testArrays[i].data = NULL;
        }
    }
    testArraysCount = 0;
}

void testAllArraysOptimized() {
    
    loadAllTestArrays();
    for (size_t i = 0; i < testArraysCount; i++) {
        testSorting(&testArrays[i], 5);
    }
    freeAllTestArrays();
    
}

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Текущая директория: %s\n\n", cwd);
    testAllArraysOptimized();
}
