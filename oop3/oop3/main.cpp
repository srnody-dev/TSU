//
//  main.cpp
//  oop3
//
//  Created by srnody on 02.11.2025.
//

#include <iostream>
#include "booleanvector.hpp"

int main()
{

    BooleanVector vec1(8, true);
    BooleanVector vec2(8, false);
    BooleanVector vec3("10101010");
    
    std::cout << "vec1: "; for (uint32_t i = 0; i < vec1.getLength(); i++) std::cout << vec1[i];
    std::cout << " weight: " << vec1.getWeight() << std::endl;
    
    std::cout << "vec2: "; for (uint32_t i = 0; i < vec2.getLength(); i++) std::cout << vec2[i];
    std::cout << " weight: " << vec2.getWeight() << std::endl;
    
    std::cout << "vec3: "; for (uint32_t i = 0; i < vec3.getLength(); i++) std::cout << vec3[i];
    std::cout << " weight: " << vec3.getWeight() << std::endl;
    
    vec1.invert(2);
    vec1.invert(0);
    vec1.invert(6);
    
    std::cout << "vec1 ";
    for (uint32_t i = 0; i < vec1.getLength(); i++) std::cout << vec1[i];
    std::cout << std::endl;
    
    vec3.invert();
    std::cout << "vec3 после инверсии: ";
    for (uint32_t i = 0; i < vec3.getLength(); i++) std::cout << vec3[i];
    std::cout << std::endl;
    
    BooleanVector vec4(5, true);
    BooleanVector vec5(5, false);
    std::cout << "До swap - vec4: "; for (uint32_t i = 0; i < vec4.getLength(); i++) std::cout << vec4[i];
    std::cout << " vec5: "; for (uint32_t i = 0; i < vec5.getLength(); i++) std::cout << vec5[i];
    std::cout << std::endl;
    
    vec4.swap(vec5);
    std::cout << "После swap - vec4: "; for (uint32_t i = 0; i < vec4.getLength(); i++) std::cout << vec4[i];
    std::cout << " vec5: "; for (uint32_t i = 0; i < vec5.getLength(); i++) std::cout << vec5[i];
    std::cout << std::endl;
    
    return 0;
}
