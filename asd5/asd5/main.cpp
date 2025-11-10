//
//  main.cpp
//  asd5
//
//  Created by srnody on 30.10.2025.
//

#include <iostream>
#include <stdio.h>
#include <random>
#include <unistd.h>

using namespace std;

const int test_Arrays = 9;

struct TestArray {
    int* data;
    int size;
    char filename[100];
};

TestArray testArrays[test_Arrays];
int testArraysCount = 0;

int findMedian(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    } else {
        return c;
    }
}

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

typedef int (*PivotSelector)(int[], int, int);
int partition(int arr[], int startIndex, int endIndex, PivotSelector pivotSelector) {
    int pivotIndex = pivotSelector(arr, startIndex, endIndex);
    swapValues(arr[pivotIndex], arr[endIndex]);
    
    int pivot = arr[endIndex];
    int leftBorder = startIndex - 1;
    
    for (int currentIndex = startIndex; currentIndex < endIndex; currentIndex++) {
        if (arr[currentIndex] <= pivot) {
            leftBorder++;
            swapValues(arr[leftBorder], arr[currentIndex]);
        }
    }
    
    swapValues(arr[leftBorder + 1], arr[endIndex]);
    return leftBorder + 1;
}

int selectFirst(int arr[], int startIndex, int endIndex) {
    return startIndex;
}

int selectMiddle(int arr[], int startIndex, int endIndex) {
    return startIndex + (endIndex - startIndex) / 2;
}

int selectLast(int arr[], int startIndex, int endIndex) {
    return endIndex;
}

int selectMedian(int arr[], int startIndex, int endIndex) {
    int middleIndex = startIndex + (endIndex - startIndex) / 2;
    int pivotValue = findMedian(arr[startIndex], arr[middleIndex], arr[endIndex]);
    
    if (pivotValue == arr[startIndex]) return startIndex;
    else if (pivotValue == arr[middleIndex]) return middleIndex;
    else return endIndex;
}

void quickSort(int arr[], int startIndex, int endIndex, PivotSelector pivotSelector) {
    if (startIndex < endIndex) {
        int partitionIndex = partition(arr, startIndex, endIndex, pivotSelector);
        quickSort(arr, startIndex, partitionIndex - 1, pivotSelector);
        quickSort(arr, partitionIndex + 1, endIndex, pivotSelector);
    }
}

void quickSortFirst(int arr[], int startIndex, int endIndex) {
    quickSort(arr, startIndex, endIndex, selectFirst);
}

void quickSortMiddle(int arr[], int startIndex, int endIndex) {
    quickSort(arr, startIndex, endIndex, selectMiddle);
}

void quickSortLast(int arr[], int startIndex, int endIndex) {
    quickSort(arr, startIndex, endIndex, selectLast);
}

void quickSortMedian(int arr[], int startIndex, int endIndex) {
    quickSort(arr, startIndex, endIndex, selectMedian);
}

void partitionThreeZone(int arr[], int startIndex, int endIndex) {
    if (startIndex >= endIndex) return;
    int pivotIndex = selectMedian(arr, startIndex, endIndex);
    int pivot = arr[pivotIndex];
        
    int left = startIndex;
    int right = endIndex;
    int current = startIndex;
        
    while (current <= right) {
        if (arr[current] < pivot) {
            swapValues(arr[current], arr[left]);
            left++;
            current++;
        } else if (arr[current] > pivot) {
            swapValues(arr[current], arr[right]);
            right--;
        } else {
            current++;
        }
    }
    
    partitionThreeZone(arr, startIndex, left - 1);
    partitionThreeZone(arr, right + 1, endIndex);
}

void quickSortThreeZone(int arr[], int startIndex, int endIndex) {
    partitionThreeZone(arr, startIndex, endIndex);
}

inline void printArray(int arr[], int n) {
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
    
    double totalMedian = 0, totalFirst = 0, totalLast = 0, totalMiddle = 0,totalThreeZone = 0;
    bool totaMedianCorrect = true, totalFirstCorrect = true, totalLastCorrect = true, totalMiddleCorrect = true,totalThreeZoneCorrect = true;
    
    // Median pivot
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        quickSortMedian(arr,0 ,testArray->size-1);
        clock_t end = clock();
        
        totalMedian += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totaMedianCorrect = false;
            printf("Ошибка: массив Median не отсортирован!\n");
        }
        
        free(arr);
    }
    
    // First pivot
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        quickSortFirst(arr,0 ,testArray->size-1);
        clock_t end = clock();
        
        totalFirst += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalFirstCorrect = false;
            printf("Ошибка: массив First не отсортирован!\n");
        }
        
        free(arr);
    }
    
    
    // Middle
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        quickSortMiddle(arr,0 ,testArray->size-1);
        clock_t end = clock();
        
        totalMiddle += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalMiddleCorrect = false;
            printf("Ошибка: массив Middle не отсортирован!\n");
        }
        
        free(arr);
    }
      
      
    
    // Last
    for (int i = 0; i < runs; i++) {
        int* arr = (int*)malloc(testArray->size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка памяти для теста\n");
            continue;
        }
        
        copyArray(arr, testArray->data, testArray->size);
        
        clock_t start = clock();
        quickSortLast(arr,0 ,testArray->size-1);
        clock_t end = clock();
        
        totalLast += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!isSorted(arr, testArray->size)) {
            totalLastCorrect = false;
            printf("Ошибка: массив Middle не отсортирован!\n");
        }
        
        free(arr);
    }
    
    
    // ThreeZone pivot
        for (int i = 0; i < runs; i++) {
            int* arr = (int*)malloc(testArray->size * sizeof(int));
            if (arr == NULL) {
                printf("Ошибка памяти для теста\n");
                continue;
            }
            
            copyArray(arr, testArray->data, testArray->size);
            
            clock_t start = clock();
            quickSortThreeZone(arr, 0, testArray->size-1);
            clock_t end = clock();
            
            totalThreeZone += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            if (!isSorted(arr, testArray->size)) {
                totalThreeZoneCorrect = false;
                printf("Ошибка: массив ThreeZone не отсортирован!\n");
            }
            
            free(arr);
        }
    
    double avgtotalMedian = totalMedian / runs;
    double avgtotalFirst = totalFirst / runs;
    double avgtotalMiddle = totalMiddle / runs;
    double avgtotalLast = totalLast / runs;
    double avgtotalThreeZone = totalThreeZone / runs;
    
    
    printf("Результаты %d запусков:\n", runs);
    printf("Median pivot: %.6f секунд (Отсортирован: %s)\n",
           avgtotalMedian, totaMedianCorrect ? "Да" : "НЕТ!");
    printf("First pivor:  %.6f секунд (Отсортирован: %s)\n",
           avgtotalFirst, totalFirstCorrect ? "Да" : "НЕТ!");
    printf("Middle pivot: %.6f секунд (Отсортирован: %s)\n",
           avgtotalMiddle, totalMiddleCorrect ? "Да" : "НЕТ!");
    printf("Last pivot:  %.6f секунд (Отсортирован: %s)\n",
           avgtotalLast, totalLastCorrect ? "Да" : "НЕТ!");
    printf("ThreeZone:  %.6f секунд (Отсортирован: %s)\n",
           avgtotalThreeZone, totalThreeZoneCorrect ? "Да" : "НЕТ!");
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
