//
//  main.cpp
//  asd5
//
//  Created by srnody on 30.10.2025.
//

#include <iostream>
#include <stdio.h>
#include <random>

using namespace std;

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

int partition(int arr[], int startIndex, int endIndex, int pivotIndex) {
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
    int pivotIndex = startIndex;
    return partition(arr, startIndex, endIndex, pivotIndex);
}

int selectMiddle(int arr[], int startIndex, int endIndex) {
    int pivotIndex = startIndex + (endIndex - startIndex) / 2;
    return partition(arr, startIndex, endIndex, pivotIndex);
}

int selectLast(int arr[], int startIndex, int endIndex) {
    int pivotIndex = endIndex;
    return partition(arr, startIndex, endIndex, pivotIndex);
}

int selectMedian(int arr[], int startIndex, int endIndex) {
    int middleIndex = startIndex + (endIndex - startIndex) / 2;
    int pivotValue = findMedian(arr[startIndex], arr[middleIndex], arr[endIndex]);
    
    int pivotIndex;
    if (pivotValue == arr[startIndex]) pivotIndex = startIndex;
    else if (pivotValue == arr[middleIndex]) pivotIndex = middleIndex;
    else pivotIndex = endIndex;
    
    return partition(arr, startIndex, endIndex, pivotIndex);
}

void quickSortFirst(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int partitionIndex = selectFirst(arr, startIndex, endIndex);
        quickSortFirst(arr, startIndex, partitionIndex - 1);
        quickSortFirst(arr, partitionIndex + 1, endIndex);
    }
}

void quickSortMiddle(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int partitionIndex = selectMiddle(arr, startIndex, endIndex);
        quickSortMiddle(arr, startIndex, partitionIndex - 1);
        quickSortMiddle(arr, partitionIndex + 1, endIndex);
    }
}

void quickSortLast(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int partitionIndex = selectLast(arr, startIndex, endIndex);
        quickSortLast(arr, startIndex, partitionIndex - 1);
        quickSortLast(arr, partitionIndex + 1, endIndex);
    }
}

void quickSortMedian(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int partitionIndex = selectMedian(arr, startIndex, endIndex);
        quickSortMedian(arr, startIndex, partitionIndex - 1);
        quickSortMedian(arr, partitionIndex + 1, endIndex);
    }
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

void testSorting() {
    cout << "Массивы 10000 эл" << endl;
    
    int arr1[10000];
    randomArray(arr1, 10000,-1000,1000);
    cout << "До сортировки: ";
    printArray(arr1, 10);
    quickSortLast(arr1, 0, 9999);
    cout << "Отсортирован quickSortLast: " << (isSorted(arr1, 10000) ? "Да" : "Нет") << endl;
    
    
    int arr2[10000];
    randomArray(arr2, 10000,-1000,1000);
    cout << "До сортировки: ";
    printArray(arr2, 10);
    quickSortMiddle(arr2, 0, 9999);
    cout << "Отсортирован quickSortMiddle: " << (isSorted(arr2, 10000) ? "Да" : "Нет") << endl;
    
    
    int arr3[10000];
    randomArray(arr3, 10000,-1000,1000);
    cout << "До сортировки: ";
    printArray(arr3, 10);
    quickSortMedian(arr3, 0, 9999);
    cout << "Отсортирован quickSortMedian: " << (isSorted(arr3, 10000) ? "Да" : "Нет") << endl;
    
    
    int arr4[10000];
    randomArray(arr4, 10000,-1000,1000);
    cout << "До сортировки: ";
    printArray(arr4, 10);
    quickSortFirst(arr4, 0, 9999);
    cout << "Отсортирован quickSortFirst: " << (isSorted(arr4, 10000) ? "Да" : "Нет") << endl;

}
int main() {
    testSorting();
    return 0;
}
