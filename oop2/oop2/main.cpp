//
//  dynamicarray.cpp
//  oop2
//
//  Created by srnody on 21.10.2025.
//

#include <iostream>
#include "dynamicarray.hpp"

using namespace std;

int main()
{
    cout << "1) Создание массивов:" << endl;
    DynamicArray<int> arr1;
    cout << "arr1(empty): ";
    arr1.print();
    cout << "Размер массива: " << arr1.getLength() << endl;

    DynamicArray<int> arr2(3);
    cout << "arr2(3): ";
    arr2.print();
    cout << "Размер: " << arr2.getLength() << endl;

    cout << endl << "2. Добавление элементов:" << endl;
    arr1.insertAt(0, 10);
    cout << "После insertAt(0, 10): ";
    arr1.print();

    arr1.insertAt(1, 20);
    arr1.insertAt(2, 30);
    arr1.insertAt(3, 40);
    cout << "После добавления 20,30,40: ";
    arr1.print();

    cout << endl << "3) Удаляем элементы:" << endl;
    arr1.removeAt(2);
    cout << "После removeAt(2): ";
    arr1.print();

    arr1.removeAt(0);
    cout << "После removeAt(0): ";
    arr1.print();

    cout << endl << "4 Check element index:" << endl;
    cout << "arr1[0] = " << arr1[0] << endl;
    cout << "arr1[1] = " << arr1[1] << endl;
    
    arr1[0] = 100;
    cout << "После arr1[0] = 100: ";
    arr1.print();

    cout << endl << "5) Копирование массива:" << endl;
    DynamicArray<int> arr3 = arr1;
    cout << "arr3 (копия arr1): ";
    arr3.print();

    cout << endl << "6) Присваивание массива:" << endl;
    DynamicArray<int> arr4;
    arr4 = arr1;
    cout << "arr4 (после присваивания): ";
    arr4.print();

    return 0;
}
