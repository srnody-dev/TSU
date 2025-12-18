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

void findAccuracyRoute(int currentCity, int count, int cost,bool visited[],
                       int currentRoute[],int bestRoute[], int& bestCost,
                       int worstRoute[], int& worstCost,
                       int** matrix, int n, int startCity){
    
    if (count == n) {
        int finalCost = cost + matrix[currentCity][startCity];
        
        if (finalCost < bestCost) {
            bestCost = finalCost;
            for (int i = 0; i < n; i++) {
                bestRoute[i] = currentRoute[i];
            }
            bestRoute[n] = startCity;
        }
        
        if (finalCost > worstCost) {
            worstCost = finalCost;
            for (int i = 0; i < n; i++) {
                worstRoute[i] = currentRoute[i];
            }
            worstRoute[n] = startCity;
        }
        return;
    }
    
    for (int nextCity = 0; nextCity < n; nextCity++) {
        if (!visited[nextCity]) {
            visited[nextCity] = true;
            currentRoute[count] = nextCity;
    
            if (currentCity >= 0 && currentCity < n &&
                nextCity >= 0 && nextCity < n) {
                findAccuracyRoute(nextCity, count + 1,
                             cost + matrix[currentCity][nextCity],
                             visited, currentRoute, bestRoute, bestCost,
                             worstRoute, worstCost, matrix, n, startCity);
            }
            visited[nextCity] = false;
        }
    }
}

int nearestNeighbor(int** matrix, int n, int route[], int startCity) {
    bool* visited = new bool[n]();
    
    route[0] = startCity;
    visited[startCity] = true;
    int totalCost = 0;
    int currentCity = startCity;
    
    for (int i = 1; i < n; i++) {
        int nearest = -1;
        int minDist = INT_MAX;
        
        for (int next = 0; next < n; next++) {
                   if (currentCity >= 0 && currentCity < n &&
                       !visited[next] && matrix[currentCity][next] < minDist) {
                       minDist = matrix[currentCity][next];
                       nearest = next;
                   }
               }
        
        route[i] = nearest;
        visited[nearest] = true;
        totalCost += minDist;
        currentCity = nearest;
    }
    
    if (currentCity >= 0 && currentCity < n && startCity >= 0 && startCity < n) {
            totalCost += matrix[currentCity][startCity];
            route[n] = startCity;
        }
    
    delete[] visited;
    return totalCost;
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

double calculateQuality(int heuristicCost, int bestCost, int worstCost) {
    if (worstCost == bestCost) return 100;
    double quality = 100 * (double)(worstCost - heuristicCost) / (double)(worstCost - bestCost);
    
    if (quality > 100) quality = 100;
    if (quality < 0) quality = 0;
    
    return quality;
}


void runAndPrintExperiment(int matrixSize, int costMin, int costMax, int run,int startCity) {
    int** matrix = generateCostMatrix(matrixSize, costMin, costMax);
    
    cout << "\nМатрица размером " << matrixSize << " на " << matrixSize << endl;
    cout << "Диапазон стоимостей от " << costMin << " до " << costMax << endl;
    
    printMatrix(matrix,matrixSize);
    
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
    
    visited[startCity] = true;
    currentRoute[0] = startCity;
    
    int bestCost = INT_MAX;
    int worstCost = 0;
    
    auto startAccuracy = chrono::high_resolution_clock::now();
    findAccuracyRoute(startCity, 1, 0, visited, currentRoute, bestRoute, bestCost, worstRoute, worstCost, matrix, matrixSize,startCity);
    
    auto endAccuracy = chrono::high_resolution_clock::now();
    double AccuracyTime = chrono::duration<double>(endAccuracy - startAccuracy).count();
    
    int* NeighborRoute = new int[matrixSize + 1];
    
    auto startNeighbor = chrono::high_resolution_clock::now();
    int NeighborCost = nearestNeighbor(matrix, matrixSize, NeighborRoute, startCity);
    auto endNeighbor = chrono::high_resolution_clock::now();
    double NeighborTime = chrono::duration<double>(endNeighbor - startNeighbor).count();
    
    double quality = calculateQuality(NeighborCost, bestCost, worstCost);
    
    cout << "\nТочный Алгоритм:" << endl;
    cout << "Лучший маршрут: ";
    for (int i = 0; i <= matrixSize; i++) cout << bestRoute[i] << (i < matrixSize ? " -> " : "");
    cout << " Стоимость: " << bestCost << endl;
    
    cout << "Худший маршрут: ";
    for (int i = 0; i <= matrixSize; i++) cout << worstRoute[i] << (i < matrixSize ? " -> " : "");
    cout << " Стоимость: " << worstCost << endl;
    
    cout << "Время: " << fixed << setprecision(6) << AccuracyTime << " сек" << endl;
    
    cout << "\nМетод ближайшего соседа:" << endl;
    cout << "Маршрут: ";
    for (int i = 0; i <= matrixSize; i++) cout << NeighborRoute[i] << (i < matrixSize ? " -> " : "");
    cout << " Стоимость: " << NeighborCost << endl;
    cout << "Время: " << fixed << setprecision(6) << NeighborTime << " сек" << endl;
    
    cout << "Качество решения: " << setprecision(2) << quality << "%" << endl;
    
    deleteMatrix(matrix, matrixSize);
    delete[] bestRoute;
    delete[] worstRoute;
    delete[] currentRoute;
    delete[] visited;
    delete[] NeighborRoute;
}

int main() {
    
    int matrixSize;
    int costMin, costMax;
    int startCity;
    
    cout << "\nВведите количество городов (размер матрицы): ";
    cin >> matrixSize;
    
    if (matrixSize < 2) {
        cout << "Ошибка: количество городов должно быть >= 2 " << endl;
        return 1;
    }
    
    cout << "Введите начальный город";
    cin >> startCity;
        
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
    
    runAndPrintExperiment(matrixSize, costMin, costMax,10,startCity);
    
    
    runAndPrintExperiment(4, 1, 10,10,startCity);
    
    runAndPrintExperiment(6, 1, 10,10,startCity);
    
    runAndPrintExperiment(8, 1, 10,10,startCity);
    
    runAndPrintExperiment(10, 1, 10,10,startCity);
    
    runAndPrintExperiment(4, 1, 100,10,startCity);
    
    runAndPrintExperiment(6, 1, 100,10,startCity);
    
    runAndPrintExperiment(8, 1, 100,10,startCity);
    
    runAndPrintExperiment(10, 1, 100,10,startCity);
    
    
    return 0;
}

