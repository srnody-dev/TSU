//
//  main.cpp
//  asd4
//
//  Created by srnody on 22.10.2025.
//

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <unistd.h>

const int test_Arrays = 9;

struct TestArray {
    int* data;
    int size;
    char filename[100];
};

TestArray testArrays[test_Arrays];
int testArraysCount = 0;

void intervalShellSort(int arr[], int n, int interval) {
    for (int i = interval; i < n; i++) {
        int temp = arr[i];
        int j;
        for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
            arr[j] = arr[j - interval];
        }
        arr[j] = temp;
    }
}

// Сортировка Шелла с оригинальным интервалом n/2
//O(n2)
void OriginalSort(int arr[], int n) {
    for (int interval = n/2; interval > 0; interval = interval / 2) {
        intervalShellSort(arr, n, interval);
    }
}

// Сортировка Шелла с последовательностью Хиббарда
//O(n^(1,5))
void HibbardSort(int arr[], int n) {
    // интервал 2^k - 1
    int k = 1;
    while (pow(2, k) - 1 < n) {
        k++;
    }
    k--;
    
    while (k >= 1) {
        int interval = pow(2, k) - 1;
        intervalShellSort(arr, n, interval);
        k--;
    }
}
// Сортировка Шелла с последовательностью Седжвика
//O(n^(4/3))
void SedgewickSort(int arr[], int n) {
    int intervals[100];
    int intervalsCount = 0;
    int i = 0;
    //интервал 9*2^i — 9*2^(i/2) + 1 четное
    // интервал 8 *2^i -6*2^(i+1)/2 +1 нечетн
    while (true) {
        int interval;
        if (i % 2 == 0) {
            interval = 9 * (1 << i) - 9 * (1 << (i/2)) + 1;
        } else {
            interval = 8 * (1 << i) - 6 * (1 << ((i+1)/2)) + 1;
        }
        
        if (interval > n) break;
        intervals[intervalsCount++] = interval;
        i++;
    }
    
    for (int i = intervalsCount - 1; i >= 0; i--) {
        intervalShellSort(arr, n, intervals[i]);
    }
}

//Сортировка Шелла с последовательностью Циура
//O(n (log n)^2).
void CiuraSort(int arr[], int n) {
    int intervals[50];
    int intervalCount = 0;
    
    int ciuraIntervals[] = {1, 4, 10, 23, 57, 132, 301, 701};
    for (int i = 0; i < 8; i++) {
        intervals[intervalCount++] = ciuraIntervals[i];
    }
    
    int nextInterval = 701;
    while (nextInterval * 2.25 < n) {
        nextInterval = nextInterval * 2.25;
        intervals[intervalCount++] = nextInterval;
    }
    
    for (int i = intervalCount - 1; i >= 0; i--) {
        intervalShellSort(arr, n, intervals[i]);
    }
}

inline void printArray(int arr[], int n, const char* label) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

inline bool isSorted(const int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void randomArray(int arr[], int n, int minValue, int maxValue) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }
}

int loadArrayFromFile(int arr[], const char* filename) {
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
            
            int n = loadArrayFromFile(arr, filename);
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

void copyArray(int copy[], int original[], int n) {
    for (int i = 0; i < n; i++) {
        copy[i] = original[i];
    }
}

void testSorting(const TestArray* testArray, int runs) {
    printf("Тест: %s (%d элементов)\n", testArray->filename, testArray->size);
    
    double totalOriginal = 0, totalHibbard = 0, totalSedgewick = 0, totalCiura = 0;
    bool totalOriginalCorrect = true, totalHibbardCorrect = true, totalSedgewickCorrect = true, totalCiuraCorrect = true;
    
    // Оригинальная
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        OriginalSort(arr, testArray->size);
        clock_t end = clock();
        
        totalOriginal += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalOriginalCorrect = false;
            printf("Ошибка: массив Оригинальной не отсортирован!\n");
        }
        
        free(arr);
    }
    
    // Хиббард
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        HibbardSort(arr, testArray->size);
        clock_t end = clock();
        
        totalHibbard += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalHibbardCorrect = false;
            printf("Ошибка: массив Хиббарда отсортирован!\n");
        }
        
        free(arr);
    }
    
    // Циура
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        CiuraSort(arr, testArray->size);
        clock_t end = clock();
        
        totalCiura += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalCiuraCorrect = false;
            printf("Ошибка: массив Циура отсортирован!\n");
        }
        
        free(arr);
    }
    
    // Седжвик
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        SedgewickSort(arr, testArray->size);
        clock_t end = clock();
        
        totalSedgewick += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalSedgewickCorrect = false;
            printf("Ошибка: массив Седжвика отсортирован!\n");
        }
        
        free(arr);
    }
    
    
    
    double avgtotalOriginal = totalOriginal / runs;
    double avgtotalHibbard = totalHibbard / runs;
    double avgtotalCiura = totalCiura / runs;
    double avgtotalSedgewick = totalSedgewick / runs;
    
    printf("Результаты %d запусков:\n", runs);
    printf("Оригинальная: %.6f секунд (Отсортирован: %s)\n",
           avgtotalOriginal, totalOriginalCorrect ? "Да" : "НЕТ!");
    printf("Хиббарда:  %.6f секунд (Отсортирован: %s)\n",
           avgtotalHibbard, totalHibbardCorrect ? "Да" : "НЕТ!");
    printf("Циура: %.6f секунд (Отсортирован: %s)\n",
           avgtotalCiura, totalCiuraCorrect ? "Да" : "НЕТ!");
    printf("Седжвика:  %.6f секунд (Отсортирован: %s)\n",
           avgtotalSedgewick, totalSedgewickCorrect ? "Да" : "НЕТ!");
    printf("\n");
    
}

void freeAllTestArrays() {
    for (int i = 0; i < testArraysCount; i++) {
        if (testArrays[i].data != NULL) {
            free(testArrays[i].data);
            testArrays[i].data = NULL;
        }
    }
    testArraysCount = 0;
}

void testAllArraysOptimized() {
    
    loadAllTestArrays();
    for (int i = 0; i < testArraysCount; i++) {
        testSorting(&testArrays[i], 3);
    }
    freeAllTestArrays();
    
}

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Текущая директория: %s\n\n", cwd);
    testAllArraysOptimized();
}
