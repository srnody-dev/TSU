#include "hashTable.h"
#include <iostream>

using namespace std;

int main() {
    
    HashFunc3 hashFunc;
    HashTable table(&hashFunc, 5);
    cout << "create table size 5 " << endl;
    table.print();
    cout << endl;
  
    table.insert(10, "Bently");
    table.insert(20, "BMW");
    table.insert(30, "Mecredes");
    table.print();
    cout << endl;
  
    table.insert(15, "Ferrari");
    table.insert(25, "Renault");
    table.print();
    cout << endl;
    
    table.insert(10, "Maserati");
    cout << "Update  10: Bently -> Maserati" << endl;
    table.print();
    cout << endl;
    
    cout << "contains(10): " << (table.contains(10) ? "ДА" : "НЕТ") << endl;
    cout << "contains(20): " << (table.contains(20) ? "ДА" : "НЕТ") << endl;
    cout << "contains(99): " << (table.contains(99) ? "ДА" : "НЕТ") << endl;
    cout << endl;
  
    table.remove(20);
    cout << "Delete 20" << endl;
    table.print();
    cout << endl;
    
    table.remove(15);
    cout << "Delete 15" << endl;
    table.print();
    cout << endl;
    
    cout << "Текущий размер: 5" << endl;
    table.resize(10);
    cout << "Изменен размер на 10" << endl;
    table.print();
    cout << endl;
  
    HashFunc2 hashFunc2;
    HashTable table3(&hashFunc2, 3);
    table3.insert(1, "One");
    table3.insert(2, "Two");
    cout << "Таблица 3 до swap:" << endl;
    table3.print();
    
    table.swap(table3);
    cout << "После swap(table, table3):" << endl;
    cout << "Таблица (бывшая table3):" << endl;
    table.print();
    cout << "Таблица 3 (бывшая table):" << endl;
    table3.print();
    cout << endl;
    
    cout << "swap HashFunc3 на HashFunc2" << endl;
    table.changeHashFunc(&hashFunc2);
    table.print();
    cout << endl;

    cout << "table[30] = " << table[30] << endl;
    table[40] = "Lamborghini";
    cout << "Добавлен table[40] = 'Lamborghini'" << endl;
    table[10] = "Bugatti";
    cout << "Изменен table[10] = 'Bugatti'" << endl;
    table.print();
    cout << endl;
  
    return 0;
}
