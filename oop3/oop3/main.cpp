//
//  main.cpp
//  oop3
//
//  Created by srnody on 02.11.2025.
//

#include <iostream>
#include <cassert>
#include "booleanvector.hpp"

int main()
{
    std::cout << "Тест конструкторов" << std::endl;
    BooleanVector empty;
    BooleanVector vec1(8, true);
    BooleanVector vec2(8,false);
    BooleanVector vec3("11001100");
    BooleanVector vec4(vec3);
    
    std::cout << "empty: " << empty << " len=" << empty.getLength() << " weight=" << empty.getWeight() << std::endl;
    std::cout << "vec1(all true): " << vec1 << " weight=" << vec1.getWeight() << std::endl;
    std::cout << "vec2(all false): " << vec2 << " weight=" << vec2.getWeight() << std::endl;
    std::cout << "vec3(string): " << vec3 << " weight=" << vec3.getWeight() << std::endl;
    std::cout << "vec4(copy vec3): " << vec4 << " weight=" << vec4.getWeight() << std::endl;
    
    std::cout << "vec2 & vec3: " << (vec2 & vec3) << std::endl;
    std::cout << "vec2 | vec3: " << (vec2 | vec3) << std::endl;
    std::cout << "~vec2: " << (~vec2) << std::endl;

    std::cout << "\nТест операций с битами" << std::endl;
    vec3.invert(0);
    vec3.set1(1);
    vec3.set0(2);
    std::cout << "After bit ops: " << vec3 << std::endl;
    
    
    std::cout << "\nТест BitReference" << std::endl;
    vec3[3] = true;
    vec3[4] = vec3[5] = false;
    std::cout << "After ref ops: " << vec3 << std::endl;
    
    
    std::cout << "\nТест полной инверсии" << std::endl;
    vec3.invert();
    std::cout << "After full invert: " << vec3 << std::endl;

    std::cout << "\nТест логических операций" << std::endl;
    BooleanVector a("11001100");
    BooleanVector b("10101010");
    
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a & b: " << (a & b) << std::endl;
    std::cout << "a | b: " << (a | b) << std::endl;
    std::cout << "~a: " << (~a) << std::endl;

    
    std::cout << "\nТест составных операций" << std::endl;
    a &= b;
    std::cout << "a after &= b: " << a << std::endl;
    
    BooleanVector c("11110000");
    c |= b;
    std::cout << "c after |= b: " << c << std::endl;

    std::cout << "\nТест присваивания" << std::endl;
    BooleanVector d("11111111");
    d = b;
    std::cout << "d после = b: " << d << std::endl;

    // Тест swap
    std::cout << "\nТест swap" << std::endl;
    BooleanVector x("11110000");
    BooleanVector y("00001111");
    
    std::cout << "До swap x: " << x << " y: " << y << std::endl;
    x.swap(y);
    std::cout << "После swap  x: " << x << " y: " << y << std::endl;
    
    BooleanVector user1, user2;
    
    
    std::cout << "\nВведите значения векторов" << std::endl;
        
    std::cout << "Вектор 1: ";
    std::cin >> user1;
        
    std::cout << "Вектор 2: ";
    std::cin >> user2;

    std::cout << "user1: " << user1 << " длина=" << user1.getLength() << " вес=" << user1.getWeight() << std::endl;
    std::cout << "user2: " << user2 << " длина=" << user2.getLength() << " вес=" << user2.getWeight() << std::endl;

    std::cout << "\nТест операций с битами (user1)" << std::endl;
    if (user1.getLength() > 0) {
        user1.invert(0);
        std::cout << "После invert(0): " << user1 << std::endl;
    }
    if (user1.getLength() > 1) {
        user1.set1(1);
        std::cout << "После set1(1): " << user1 << std::endl;
    }
    if (user1.getLength() > 2) {
        user1.set0(2);
        std::cout << "После set0(2): " << user1 << std::endl;
    }

    std::cout << "\nТест BitReference (user1)" << std::endl;
    if (user1.getLength() > 3) {
        user1[3] = true;
        std::cout << "После user1[3] = true: " << user1 << std::endl;
    }
    if (user1.getLength() > 5) {
        user1[4] = user1[5] = false;
        std::cout << "После user1[4] = user1[5] = false: " << user1 << std::endl;
    }

    std::cout << "\nТест полной инверсии (user2)" << std::endl;
    user2.invert();
    std::cout << "После полной инверсии: " << user2 << std::endl;

    std::cout << "\nТест логических операций" << std::endl;
    std::cout << "user1: " << user1 << std::endl;
    std::cout << "user2: " << user2 << std::endl;
        
    try {
        std::cout << "user1 & user2: " << (user1 & user2) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "user1 & user2: невозможно (разная длина)" << std::endl;
    }
        
    try {
        std::cout << "user1 | user2: " << (user1 | user2) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "user1 | user2: невозможно (разная длина)" << std::endl;
    }
        
    std::cout << "~user1: " << (~user1) << std::endl;

    std::cout << "\nТест составных операций" << std::endl;
    BooleanVector user3 = user1;
        
    try {
        user3 &= user2;
        std::cout << "user3 после &= user2: " << user3 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "user3 &= user2: невозможно (разная длина)" << std::endl;
    }

    BooleanVector user4 = user1;
    try {
        user4 |= user2;
        std::cout << "user4 после |= user2: " << user4 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "user4 |= user2: невозможно (разная длина)" << std::endl;
    }

    std::cout << "\nТест присваивания" << std::endl;
    BooleanVector user5("1111");
    user5 = user1;
    std::cout << "user5 после = user1: " << user5 << std::endl;

    std::cout << "\nТест swap" << std::endl;
    BooleanVector user6 = user1;
    BooleanVector user7 = user2;
        
    std::cout << "До swap user6: " << user6 << " user7: " << user7 << std::endl;
    user6.swap(user7);
    std::cout << "После swap user6: " << user6 << " user7: " << user7 << std::endl;


    return 0;
}
