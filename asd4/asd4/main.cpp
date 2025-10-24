//
//  main.cpp
//  asd4
//
//  Created by srnody on 22.10.2025.
//

#include <iostream>
#include <random>

using namespace std;


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
void OriginalSort(int arr[], int n) {
    for (int interval = n/2; interval > 0; interval = interval / 2) {
        intervalShellSort(arr, n, interval);
    }
}

// Сортировка Шелла с последовательностью Хиббарда
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
void SedgewickSort(int arr[], int n) {
    int intervals[100];
    int intervalsCount = 0;
    int i = 0;
    //интервал 9*2^i — 9*2^(i/2) + 1 четное
    // интервал 8 *2^i -6*2^(i+1)/2 +1 нечетн
    while (true) {
        int interval;
        if (i % 2 == 0) {
            interval = 9 * (pow(2, i) - pow(2, i/2)) + 1;
        } else {
            interval = 8 * pow(2, i) - 6 * pow(2, (i+1)/2) + 1;
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

inline void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
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
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<int> dist(minValue, maxValue);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }
}
void testSorts() {
    const int sizeArray = 100000000;
        int* arr = new int[sizeArray];
    
    cout << "Тест сортировок Шелла с различным шагом" << endl;
    // Тест Хиббарда
    randomArray(arr, sizeArray, -999999, 999999);
    clock_t start = clock();
    HibbardSort(arr, sizeArray);
    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Хиббард: " << duration << " мкс" << endl;
        
    // Тест оригинальной
    randomArray(arr, sizeArray, -999999, 999999);
    start = clock();
    OriginalSort(arr, sizeArray);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Оригинальная: " << duration << " мкс" << endl;
        
    // Тест Седжвика
    randomArray(arr, sizeArray, -999999, 999999);
    start = clock();
    SedgewickSort(arr, sizeArray);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Седжвик: " << duration << " мкс" << endl;
    
    // Тест Циура
    randomArray(arr, sizeArray, -999999, 999999);
    start = clock();
    CiuraSort(arr, sizeArray);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Циур: " << duration << " мкс" << endl;
    
    delete[] arr;
    
}

int main() {
    testSorts();
    return 0;
}
