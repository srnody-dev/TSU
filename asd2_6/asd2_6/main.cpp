//
//  main.cpp
//  asd2_6
//
//  Created by srnody on 19.02.2026.
//

#include <iostream>
#include "hashTable.h"

using namespace std;

int main() {
    
    HashFunc3 hf3;

    HashTable table(&hf3);

    table.insert(197, "Bentley");
    table.insert(178, "Jaguar");
    table.insert(77, "BMW");
    table.insert(777, "Mercedes");
    table.insert(78, "Nissan");
    table.insert(99, "Audi");
    table.insert(70, "Toyota");
    table.insert(78, "Tesla");

    table.print();

    cout << "\nContains 77? "
         << (table.contains(77) ? "Yes" : "No") << endl;
    
    table.remove(70);
    cout << "\nAfter remove:\n";
    table.print();
    
    table[777]="Mercedes-Benz";
    cout << "\nAfter operator[]:\n";
    table.print();
    
    
    table.resize(20);
    cout << "\nAfter resize:\n";
    table.print();
}

