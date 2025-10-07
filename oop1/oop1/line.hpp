//
//  line.hpp
//  oop1
//
//  Created by srnody on 07.10.2025.
//

#pragma once

#include <iostream>
#include <cmath>

class Line {
private:
    double a, b, c;
    
public:
    
    Line(double a_val= 0 , double b_val = 1, double c_val= 0);
    
    void input();
    void output() const;
    
    double getA() const;
    double getB() const;
    double getC() const;
    
    void setA(double new_a);
    void setB(double new_b);
    void setC(double new_c);
    
    bool isStart() const;
    bool isPerpendicular() const;
    void printSlopeInfo() const;
    bool operator || (const Line& other) const;
    bool isPerpendicularTo(const Line& other) const;
    double distance() const;
    bool belongs(double x0, double y0) const;
    double spiceCornerTo(const Line& other) const;
};

void testLineClass();

