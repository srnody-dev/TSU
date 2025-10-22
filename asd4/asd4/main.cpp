//
//  main.cpp
//  asd4
//
//  Created by srnody on 22.10.2025.
//

#include <iostream>
#include <random>

using namespace std;

// Сортировка Шелла с оригинальным шагом n/2
void shellInsertionSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j = j - gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void randomArray(int arr[], int n, int minValue, int maxValue) {
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<int> dist(minValue, maxValue);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }
}

void testSorting() {
    
    cout << "Массив 100 эл" << endl;
    int arr2[100];
    randomArray(arr2, 100, -999, 999);
    cout << "До сортировки: ";
    printArray(arr2, 100);
    
    shellInsertionSort(arr2, 100);
    cout << "После сортировки: ";
    printArray(arr2, 100);
    cout << "Отсортирован: " << (isSorted(arr2, 100) ? "Да" : "Нет") << endl << endl;
    
   
}

int main() {
    testSorting();
    return 0;
}
