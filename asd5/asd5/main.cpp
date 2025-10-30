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

int partitionArray(int arr[], int startIndex, int endIndex) {
    int middleIndex = startIndex + (endIndex - startIndex) / 2;
    int pivotValue = findMedian(arr[startIndex], arr[middleIndex], arr[endIndex]);
    
    int pivotIndex;
    if (pivotValue == arr[startIndex]) pivotIndex = startIndex;
    else if (pivotValue == arr[middleIndex]) pivotIndex = middleIndex;
    else pivotIndex = endIndex;
    
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

void quickSort(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int partitionIndex = partitionArray(arr, startIndex, endIndex);
        quickSort(arr, startIndex, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, endIndex);
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
    cout << "Массив 10000 эл" << endl;
    int arr2[10000];
    randomArray(arr2, 10000, -99999, 99999);
    cout << "До сортировки: ";
    printArray(arr2, 100);
    
    quickSort(arr2, 0, 9999);
    cout << "После сортировки: ";
    printArray(arr2, 100);
    cout << "Отсортирован: " << (isSorted(arr2, 10000) ? "Да" : "Нет") << endl;

}
int main() {
    testSorting();
    return 0;
}
