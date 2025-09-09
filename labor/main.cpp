//
//  main.cpp
//  labor
//
//  Created by srnody on 03.09.2025.
//

#include <iostream>
#include <vector>
#include <random>

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
    std::cout << "\n Матрица смежности" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << costMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
