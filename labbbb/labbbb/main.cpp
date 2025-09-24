#include <iostream>
#include <vector>
#include <random>
#include <climits>

void findOptimalRoute(int currentCity, int count, int cost,
                  std::vector<bool>& visited,
                  std::vector<int>& currentPath,
                  std::vector<int>& bestPath, int& bestCost,
                  const std::vector<std::vector<int>>& matrix) {
    auto n = matrix.size();
    

    if (count == n) {
        cost += matrix[currentCity][0];
        if (cost < bestCost) {
            bestCost = cost;
            bestPath = currentPath;
            
        }
        return;
    }
    

    for (int nextCity = 0; nextCity < n; nextCity++) {
        if (!visited[nextCity]) {
            visited[nextCity] = true;
            currentPath[count] = nextCity;
            
            findOptimalRoute(nextCity, count + 1, cost + matrix[currentCity][nextCity],
                         visited, currentPath, bestPath, bestCost, matrix);
            
            visited[nextCity] = false;
        }
    }
}

std::pair<std::vector<int>, int> calculateOptimalRoute(int startCity, const std::vector<std::vector<int>>& matrix) {
    auto n = matrix.size();
    
    if (n <= 1) {
        return {{startCity}, 0};
    }

    std::vector<bool> visited(n, false);
    std::vector<int> currentPath(n);
    std::vector<int> bestPath;
    int bestCost = INT_MAX;
    
    visited[startCity] = true;
    currentPath[0] = startCity;
    
    findOptimalRoute(startCity, 1, 0, visited, currentPath, bestPath, bestCost, matrix);
    
    /*
    
    std::vector<int> fullBestPath = bestPath;
    fullBestPath.push_back(startCity);
    
    return {fullBestPath, bestCost};*/
    
    //проверь будет ли так быстрей без создания копий
    
    bestPath.push_back(startCity);
    return {bestPath, bestCost};
}

void printRoad(const std::vector<int>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
}

int main() {
    int n;
    std::cout << "Введите количество городов: ";
    std::cin >> n;


    std::vector<std::vector<int>> costMatrix(n, std::vector<int>(n, 0));
    
    int minCost, maxCost;
    std::cout << "Введите минимальную стоимость маршрута: ";
    std::cin >> minCost;
    std::cout << "Введите максимальную стоимость маршрута: ";
    std::cin >> maxCost;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(minCost, maxCost);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                costMatrix[i][j] = 0;
            } else {
                costMatrix[i][j] = dist(gen);
            }
        }
    }

    std::cout << "\nМатрица смежности:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << costMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    

    auto result = calculateOptimalRoute(0, costMatrix);
    
    std::cout << "Оптимальный путь: ";
    printRoad(result.first);
    std::cout << "\nМинимальная стоимость: " << result.second << std::endl;
    

    return 0;
}
