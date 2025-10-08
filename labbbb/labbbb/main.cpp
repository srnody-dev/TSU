#include <iostream>
#include <random>
#include <chrono>
#include <climits>
#include <iomanip>

using namespace std;

void printRoad(int route[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << route[i];
        if (i < size - 1) {
            cout << " -> ";
        }
    }
}

void findAccuracyRoute(int currentCity, int count, int cost,
                  bool visited[], int currentRoute[],
                  int bestRoute[], int& bestCost,
                  int worstRoute[], int& worstCost,
                  int** matrix, int n) {
    
    if (count == n) {
        int finalCost = cost + matrix[currentCity][0];
        
        if (finalCost < bestCost) {
            bestCost = finalCost;
            for (int i = 0; i < n; i++) {
                bestRoute[i] = currentRoute[i];
            }
        }
        
        if (finalCost > worstCost) {
            worstCost = finalCost;
            for (int i = 0; i < n; i++) {
                worstRoute[i] = currentRoute[i];
            }
        }
        return;
    }
    
    for (int nextCity = 0; nextCity < n; nextCity++) {
        if (!visited[nextCity]) {
            visited[nextCity] = true;
            currentRoute[count] = nextCity;
            
            findAccuracyRoute(nextCity, count + 1, cost + matrix[currentCity][nextCity],
                         visited, currentRoute, bestRoute, bestCost, worstRoute, worstCost, matrix, n);
            
            visited[nextCity] = false;
        }
    }
}

int** createMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** generateCostMatrix(int n, int minCost, int maxCost) {
    int** matrix = createMatrix(n);
    
    random_device randomDevice;
    mt19937_64 generator(randomDevice());
    uniform_int_distribution<int> dist(minCost, maxCost);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = dist(generator);
            }
        }
    }
    
    return matrix;
}

void printMatrix(int** matrix, int n) {
    cout << "\nСгенерированная матрица стоимостей:" << endl;
    
    cout << "   \t";
    for (int i = 0; i < n; i++) {
        cout << i << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i << " |\t";
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << "0\t";
            } else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

void runAndPrintExperiment(int matrixSize, int costMin, int costMax) {
    int** matrix = generateCostMatrix(matrixSize, costMin, costMax);
    
    cout << "\nМатрица размером " << matrixSize << "на" << matrixSize << endl;
    cout << "Диапазон стоимостей от " << costMin << " до " << costMax << endl;
    
    printMatrix(matrix, matrixSize);
    
    int* bestRoute = new int[matrixSize + 1];
    int* worstRoute = new int[matrixSize + 1];
    int* currentRoute = new int[matrixSize];
    bool* visited = new bool[matrixSize];
    
    for (int i = 0; i < matrixSize; i++) {
        visited[i] = false;
        bestRoute[i] = -1;
        worstRoute[i] = -1;
        currentRoute[i] = -1;
    
    }
    
    bestRoute[matrixSize] = -1;
    worstRoute[matrixSize] = -1;
    
    
    visited[0] = true;
    currentRoute[0] = 0;
    
    int bestCost = INT_MAX;
    int worstCost = 0;
    
    auto start = chrono::high_resolution_clock::now();
    
    findAccuracyRoute(0, 1, 0, visited, currentRoute, bestRoute, bestCost, worstRoute, worstCost, matrix, matrixSize);
    
        if (bestCost != INT_MAX) {
            bestRoute[matrixSize] = 0;
        }
        if (worstCost > 0) {
            worstRoute[matrixSize] = 0;
        }
    
    auto end = chrono::high_resolution_clock::now();
    auto exactTime = chrono::duration<double>(end - start);
    double exactSeconds = exactTime.count();
    
    cout << "Точный алгоритм - лучший маршрут: " << bestCost << " Время: "<< fixed << setprecision(6) << exactSeconds << " cек" << endl;
    cout << "Точный алгоритм - худший маршрут: " << worstCost << endl;
    
    cout << "\nЛучший путь (точный): ";
    printRoad(bestRoute, matrixSize + 1);
    cout << "\nХудший путь (точный): ";
    printRoad(worstRoute, matrixSize + 1);
    cout << "\n" << endl;
    
    deleteMatrix(matrix, matrixSize);
    delete[] bestRoute;
    delete[] worstRoute;
    delete[] currentRoute;
    delete[] visited;
}

int main() {
    
    int matrixSize;
    int costMin, costMax;
    
    cout << "\nВведите количество городов (размер матрицы): ";
    cin >> matrixSize;
    
    if (matrixSize < 2) {
            cout << "Ошибка: количество городов должно быть >= 2 " << endl;
            return 1;
        }
        
    cout << "Введите минимальную стоимость маршрута: ";
    cin >> costMin;
    
    cout << "Введите максимальную стоимость маршрута: ";
    cin >> costMax;
    
    if (costMin < 0 || costMax <= costMin) {
        cout << "Ошибка: минимальная стоимость должна быть >= 0, а максимальная > минимальной!" << endl;
        return 1;
    }
    
    if (matrixSize > 11) {
        cout << "\nДля матрицы размером " << matrixSize << "x" << matrixSize
             << " точный алгоритм может работать долго" << endl;
    }
    
    runAndPrintExperiment(matrixSize, costMin, costMax);
    
    return 0;
}

