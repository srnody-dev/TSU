//
//  main.cpp
//  asd3
//
//  Created by srnody on 08.10.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//алгоритм флойда построение кучи снизу-вверх

void bubbleBottom(int arr[], int n, int i) {
    int biggest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[biggest])
        biggest = left;

    if (right < n && arr[right] > arr[biggest])
        biggest = right;

    if (biggest != i) {
        int temp = arr[i];
        arr[i] = arr[biggest];
        arr[biggest] = temp;
        bubbleBottom(arr, n, biggest);
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


//построение сверху вниз

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
        
        for (int j = 1; j < i; j++) {
            bubbleTop(arr, j);
        }
    }
}

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

void randomArray(int arr[], int n, int minValue, int maxValue) {
    for (int i = 0; i < n; i++) {
        arr[i] = random(minValue, maxValue);
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

int main() {
    
    //не забудь реализовать сравнение построения куч
    
    srand((unsigned int)time(NULL));
    
    const int n = 10;
    int minValue = -100;
    int maxValue = 100;
    
    int* originalArray = (int*)malloc(n * sizeof(int));
    int* arr1 = (int*)malloc(n * sizeof(int));
    int* arr2 = (int*)malloc(n * sizeof(int));
    
    randomArray(originalArray, n, minValue, maxValue);
    
    copyArray(arr1, originalArray, n);
    
    copyArray(arr2, originalArray, n);
    
    printArray(originalArray, n, "Исходный массив ");
    
    heapSortTopBottom(arr1, n);
    
    heapSortBottomTop(arr2, n);
    
    printArray(arr1, n, "Сверху вниз ");
    
    printArray(arr2, n, "Снизу вверх ");
   
    free(originalArray);
    free(arr1);
    free(arr2);
    
    return 0;
}
