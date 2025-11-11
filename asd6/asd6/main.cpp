//
//  main.cpp
//  asd6
//
//  Created by srnody on 11.11.2025.
//

#include <iostream>

using namespace std;

void BitSort(int A[], int n) {
    if (n <= 1) return;
    
    const int t = sizeof(int) * 8;
    int* A0 = new int[n];
    int* A1 = new int[n];
    int n0, n1;
    
    for (int k = 0; k < t - 1; k++) {
        n0 = 0; n1 = 0;
        
        for (int i = 0; i < n; i++) {
            if (A[i] & (1 << k)) {
                A1[n1] = A[i];
                n1++;
            } else {
                A0[n0] = A[i];
                n0++;
            }
        }
        
        for (int i = 0; i < n0; i++) {
            A[i] = A0[i];
        }
        for (int i = 0; i < n1; i++) {
            A[n0 + i] = A1[i];
        }
    }
    
    delete[] A0;
    delete[] A1;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr1[] = {5, 2, 3, 1, 4,9};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    cout << "Положительные числа" << endl;
    cout << "До сортировки: ";
    printArray(arr1, n1);
    
    BitSort(arr1, n1);
    
    cout << "После сортировки: ";
    printArray(arr1, n1);
    cout << endl;
    
    int arr2[] = {-3, -1, -4, -2, -5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    cout << "Отрицательные числа" << endl;
    cout << "До сортировки: ";
    printArray(arr2, n2);
    
    BitSort(arr2, n2);
    
    cout << "После сортировки: ";
    printArray(arr2, n2);
    cout << endl;
    
    return 0;
}
