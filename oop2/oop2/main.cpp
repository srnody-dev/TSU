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

    cout << endl << "4) Check element index:" << endl;
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

    cout << endl << "7) Тестирование операторов сравнения:" << endl;
    DynamicArray<int> arr5 = arr1;
    DynamicArray<int> arr6;
    arr6.insertAt(0, 100);
    arr6.insertAt(1, 40);
    
    cout << "arr1: ";
    arr1.print();
    cout << "arr5: ";
    arr5.print();
    cout << "arr6: ";
    arr6.print();
    
    cout << "arr1 == arr5: " << (arr1 == arr5) << endl;
    cout << "arr1 == arr6: " << (arr1 == arr6) << endl;
    cout << "arr1 != arr6: " << (arr1 != arr6) << endl;
    
    cout << endl << "8) Тестирование оператора +:" << endl;
    DynamicArray<int> arr7 = arr1 + arr6;
    cout << "arr1 + arr6: ";
    arr7.print();

    cout << endl << "9) Тестирование оператора +=:" << endl;
    cout << "arr1: ";
    arr1.print();
    cout << "arr6: ";
    arr6.print();
    arr1 += arr6;
    cout << "arr1 после += arr6: ";
    arr1.print();
    
    cout << endl << "10) Тестирование swap:" << endl;
        DynamicArray<int> arr8;
        arr8.insertAt(0, 1);
        arr8.insertAt(1, 2);
        arr8.insertAt(2, 3);
        
        DynamicArray<int> arr9;
        arr9.insertAt(0, 7);
        arr9.insertAt(1, 8);
        arr9.insertAt(2, 9);
        arr9.insertAt(3, 10);
        
        cout << "arr8 до swap: ";
        arr8.print();
        cout << "arr9 до swap: ";
        arr9.print();
        
        arr8.swap(arr9);
    cout << "arr8 после swap: ";
        arr8.print();
        cout << "arr9 после swap: ";
        arr9.print();
    
    cout << endl << "11) Тестирование find:" << endl;
       DynamicArray<int> arr10;
       arr10.insertAt(0, 5);
       arr10.insertAt(1, 10);
       arr10.insertAt(2, 15);
       arr10.insertAt(3, 10);
       arr10.insertAt(4, 20);
       
       cout << "arr10: ";
       arr10.print();
       cout << "find(10): " << arr10.find(10) << endl;
       cout << "find(15): " << arr10.find(15) << endl;
       cout << "find(99): " << arr10.find(99) << endl;

    cout << endl << "12) Тестирование removeByValue:" << endl;
        cout << "arr10 до removeByValue(10): ";
        arr10.print();
        bool removed = arr10.removeByValue(10);
        cout << "Удаление прошло: " << removed << endl;
    
    cout << endl << "13) Тестирование removeAllByValue:" << endl;
       DynamicArray<int> arr11;
       arr11.insertAt(0, 5);
       arr11.insertAt(1, 2);
       arr11.insertAt(2, 5);
       arr11.insertAt(3, 3);
       arr11.insertAt(4, 5);
       arr11.insertAt(5, 5);
       arr11.insertAt(6, 7);
       
       cout << "arr11 до removeAllByValue(5): ";
       arr11.print();
       int count = arr11.removeAllByValue(5);
       cout << "Удалено элементов: " << count << " (ожидается: 4)" << endl;
       cout << "arr11 после removeAllByValue(5): ";
       arr11.print();
    
    cout << endl << "14) Тестирование sort:" << endl;
        DynamicArray<int> arr12;
        arr12.insertAt(0, 34);
        arr12.insertAt(1, 7);
        arr12.insertAt(2, 23);
        arr12.insertAt(3, 1);
        arr12.insertAt(4, 56);
        arr12.insertAt(5, 12);
        
        cout << "arr12 до sort: ";
        arr12.print();
        arr12.sort();
        cout << "arr12 после sort: ";
        arr12.print();
    cout << endl << "15) Тестирование с другими типами данных:" << endl;
       DynamicArray<double> doubleArr;
       doubleArr.insertAt(0, 1.5);
       doubleArr.insertAt(1, 2.7);
       doubleArr.insertAt(2, 3.1);
       cout << "doubleArr: ";
       doubleArr.print();

       DynamicArray<float> floatArr;
       floatArr.insertAt(0, 1.1f);
       floatArr.insertAt(1, 2.2f);
       cout << "floatArr: ";
       floatArr.print();
    
    
    return 0;
}
