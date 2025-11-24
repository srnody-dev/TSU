//
//  main.cpp
//  oop5
//
//  Created by srnody on 18.11.2025.
//

#include "linkedList.hpp"

int main()
{
    LinkedList<int> list1;
    std::cout << "Размер: " << list1.getSize() << std::endl;
    std::cout << "isEmpty?: " << (list1.isEmpty() ? "да" : "нет") << std::endl;

    std::cout << "\nДобавляем элементы в голову:" << std::endl;
    list1.addToHead(30);
    list1.addToHead(20);
    list1.addToHead(10);
    std::cout << "Размер после добавления: " << list1.getSize() << std::endl;

    std::cout << "\nДобавляем элементы в хвост:" << std::endl;
    list1.addToTail(40);
    list1.addToTail(50);
    std::cout << "Размер после добавления в хвост: " << list1.getSize() << std::endl;

    std::cout << "\nУдаляем из головы:" << std::endl;
    list1.removeFromHead();
    std::cout << "Размер после удаления из головы: " << list1.getSize() << std::endl;

    std::cout << "\nУдаляем из хвоста:" << std::endl;
    list1.removeFromTail();
    std::cout << "Размер после удаления из хвоста: " << list1.getSize() << std::endl;

    std::cout << "\nОчищаем список:" << std::endl;
    list1.clear();
    std::cout << "Размер после очистки: " << list1.getSize() << std::endl;
    std::cout << "isEmpty?: " << (list1.isEmpty() ? "да" : "нет") << std::endl;


    return 0;
}
