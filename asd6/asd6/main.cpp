//
//  main.cpp
//  asd6
//
//  Created by srnody on 11.11.2025.
//

#include <iostream>

using namespace std;

void bitSort(int A[], int n) {
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

void bitSortMix(int A[], int n) {
    if (n <= 1) return;
    
    int* Aminus = new int[n];
    int* Aplus = new int[n];
    int Nm = 0, Np = 0;
    
    for (int i = 0; i < n; i++) {
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
    
    for (int i = 0; i < Nm; i++) {
        A[i] = Aminus[i];
    }
    for (int i = 0; i < Np; i++) {
        A[Nm + i] = Aplus[i];
    }
    
    delete[] Aminus;
    delete[] Aplus;
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
    
    bitSort(arr1, n1);
    
    cout << "После сортировки: ";
    printArray(arr1, n1);
    cout << endl;
    
    int arr2[] = {-3, -1, -4, -2, -5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    cout << "Отрицательные числа" << endl;
    cout << "До сортировки: ";
    printArray(arr2, n2);
    
    bitSort(arr2, n2);
    
    cout << "После сортировки: ";
    printArray(arr2, n2);
    cout << endl;
    
    int arr3[] = {0,1,2,3,4,5,6,7,12,54,55,7,2,8,-3, -1, -4,0, -2, -5,-6,-234,-99,543,-53,543,-87,-987};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    cout << "Оба диапозона чисел" << endl;
    cout << "До сортировки: ";
    printArray(arr3, n3);
    
    bitSortMix(arr3, n3);
    
    cout << "После сортировки: ";
    printArray(arr3, n3);
    cout << endl;
    
    return 0;
}
