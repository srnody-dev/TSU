//
//  main.cpp
//  asd6
//
//  Created by srnody on 11.11.2025.
//

#include <iostream>
#include <random>

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

void bitSortInvert(int A[], int n) {
    if (n <= 1) return;
    
    const int t = sizeof(int) * 8;
    int* A0 = new int[n];
    int* A1 = new int[n];
    int n0, n1;
    
    for (int i = 0; i < n; i++) {
        A[i] ^= (1 << (t-1));
    }
    
    for (int k = 0; k < t; k++) {
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
    
    for (int i = 0; i < n; i++) {
        A[i] ^= (1 << (t-1));
    }
    
    delete[] A0;
    delete[] A1;
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

void copyArray(int copy[], int original[], int n) {
    for (int i = 0; i < n; i++) {
        copy[i] = original[i];
    }
}

void testSortingFunctions() {
    const int n = 1000000;
    int* originalArray = new int[n];
    int* testArray1 = new int[n];
    int* testArray2 = new int[n];
    
    randomArray(originalArray, n, -100000, 100000);
    copyArray(testArray1, originalArray, n);
    copyArray(testArray2, originalArray, n);
        
    clock_t start1 = clock();
    bitSortMix(testArray1, n);
    clock_t end1 = clock();
    double duration1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC;
        
    clock_t start2 = clock();
    bitSortInvert(testArray2, n);
    clock_t end2 = clock();
    double duration2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
        
    bool sorted1 = isSorted(testArray1, n);
    bool sorted2 = isSorted(testArray2, n);
        
    cout << "bitSortMix:" << endl;
    cout << "Отсортирован: " << (sorted1 ? "Да" : "НЕТ!") << endl;
    cout << "Время выполнения: " << duration1 << " секунд" << endl;
    cout << "bitSortInvert:" << endl;
    cout << "Отсортирован: " << (sorted2 ? "Да" : "НЕТ!") << endl;
    cout << "Время выполнения: " << duration2 << " секунд" << endl;
    
    delete[] originalArray;
    delete[] testArray1;
    delete[] testArray2;
}

int main() {
    testSortingFunctions();
    return 0;
}
