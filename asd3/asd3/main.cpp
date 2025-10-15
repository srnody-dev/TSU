//  main.cpp
//  asd3
//
//  Created by srnody on 08.10.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

// Алгоритм флойда построение кучи снизу-вверх
void bubbleBottom(int arr[], int n, int i) {
    while (true) {
        int biggest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[biggest])
            biggest = left;
        if (right < n && arr[right] > arr[biggest])
            biggest = right;

        if (biggest == i) break;

        int temp = arr[i];
        arr[i] = arr[biggest];
        arr[biggest] = temp;
        
        i = biggest;
    }
}

void heapBuildBottomTop(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        bubbleBottom(arr, n, i);
    }
}

void heapSortBottomTop(int arr[], int n) {
    heapBuildBottomTop(arr, n);
    
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        bubbleBottom(arr, i, 0);
    }
}

// Построение сверху вниз
void bubbleTop(int arr[], int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (arr[i] > arr[parent]) {
            int temp = arr[i];
            arr[i] = arr[parent];
            arr[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

void heapBuildTopBottom(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        bubbleTop(arr, i);
    }
}

void heapSortTopBottom(int arr[], int n) {
    heapBuildTopBottom(arr, n);
    
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        bubbleBottom(arr, i, 0);
    }
}

void randomArray(int arr[], int n, int minValue, int maxValue) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }
}

void copyArray(int copy[], int original[], int n) {
    for (int i = 0; i < n; i++) {
        copy[i] = original[i];
    }
}

void printArray(int arr[], int n, const char* label) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void saveArrayToFile(int arr[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }
    
    fprintf(file, "%d\n", n);
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < n - 1) {
            fprintf(file, " ");
        }
    }
    fprintf(file, "\n");
    
    fclose(file);
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

void generateTestArrays() {
    int sizes[] = {10000, 100000, 1000000};
    int ranges[][2] = {{-10, 10}, {-1000, 1000}, {-100000, 100000}};
    const char* rangeNames[] = {"-10_10", "-1000_1000", "-100000_100000"};
    
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int n = sizes[i];
            int minValue = ranges[j][0];
            int maxValue = ranges[j][1];
            
            char filename[100];
            snprintf(filename, sizeof(filename), "testArray_size_%d_range_%s.txt", n, rangeNames[j]);
            
            int* arr = (int*)malloc(n * sizeof(int));
            if (arr == NULL) {
                printf("Ошибка памяти для массива %s\n", filename);
                continue;
            }
            
            randomArray(arr, n, minValue, maxValue);
            saveArrayToFile(arr, n, filename);
            
            free(arr);
        }
    }
}

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
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

void freeAllTestArrays() {
    for (int i = 0; i < testArraysCount; i++) {
        if (testArrays[i].data != NULL) {
            free(testArrays[i].data);
            testArrays[i].data = NULL;
        }
    }
    testArraysCount = 0;
}

void testSorting(const TestArray* testArray, int runs) {
    printf("Тест: %s (%d элементов)\n", testArray->filename, testArray->size);
    
    double totalBottomTop = 0, totalTopBottom = 0;
    bool bottomTopCorrect = true, topBottomCorrect = true;
    
    // Тестирование сортировки снизу-вверх
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        heapSortBottomTop(arr, testArray->size);
        clock_t end = clock();
        
        totalBottomTop += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            bottomTopCorrect = false;
            printf("Ошибка: массив снизу-вверх не отсортирован!\n");
        }
        
        free(arr);
    }
    
    // Тестирование сортировки сверху-вниз
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        heapSortTopBottom(arr, testArray->size);
        clock_t end = clock();
        
        totalTopBottom += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            topBottomCorrect = false;
            printf("Ошибка: массив сверху-вниз не отсортирован!\n");
        }
        
        free(arr);
    }
    
    double avgBottomTop = totalBottomTop / runs;
    double avgTopBottom = totalTopBottom / runs;
    
    printf("Результаты %d запусков:\n", runs);
    printf("Снизу-вверх: %.6f секунд (Отсортирован: %s)\n",
           avgBottomTop, bottomTopCorrect ? "Да" : "НЕТ!");
    printf("Сверху-вниз:  %.6f секунд (Отсортирован: %s)\n",
           avgTopBottom, topBottomCorrect ? "Да" : "НЕТ!");
    
    if (avgBottomTop < avgTopBottom) {
        printf("Снизу-вверх быстрее на: %.6f секунд (%.2f%%)\n",
               avgTopBottom - avgBottomTop,
               (avgTopBottom - avgBottomTop) / avgTopBottom * 100);
    } else if (avgTopBottom < avgBottomTop) {
        printf("Сверху-вниз быстрее на: %.6f секунд (%.2f%%)\n",
               avgBottomTop - avgTopBottom,
               (avgBottomTop - avgTopBottom) / avgBottomTop * 100);
    } else {
        printf("Обе сортировки заняли одинаковое время\n");
    }
    printf("\n");
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
    
    generateTestArrays();
    
    testAllArraysOptimized();
    
    return 0;
}
