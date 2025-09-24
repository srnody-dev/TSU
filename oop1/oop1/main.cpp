//  oop1
//
//  Created by srnody on 23.09.2025.
//

#include <iostream>
#include <cmath>

class Line {
private:
    double a, b, c;

public: //1) конструкторы: по умолчанию, с аргументами (или с аргументами по умолчанию);
    Line() : a(0), b(1), c(0) {}
    
    Line(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {
    
    }

    //2) ввод/вывод уравнения прямой;
    void input() {
        std::cout << "Введите коэффициенты a, b, c уравнения ax + by + c = 0: ";
        std::cin >> a >> b >> c;
        if (a == 0 && b == 0) { //сheck на прямую
                a = 0;
                b = 1;
                c = 0;
            }
        
    }
    
    void output() const {
        std::cout << a << "x + " << b << "y + " << c << " = 0" << std::endl;
    }
    
    
    //3) аксессоры для всех полей класса;

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    
    void setA(double new_a) {
        a = new_a;
        if (a == 0 && b == 0) b = 1;
    }
    
    void setB(double new_b) {
        b = new_b;
        if (a == 0 && b == 0) a = 1;
    }
    
    void setC(double new_c) { c = new_c; }

    
    //4) проверка, проходит ли прямая через начало координат;
    bool isStart() const {
        return c == 0;
    }
//5) проверка, перпендикулярна ли прямая оси Ox;
    bool isPerpendicular() const {
        return b == 0;
    }
};

void testLineClass() {
    
    Line testLine;
    testLine.input();
    std::cout << "Прямая: "; testLine.output();
    std::cout << "Проходит через начало координат(0,0): " << (testLine.isStart() ? "да" : "нет") << std::endl;
    std::cout << "Перпендикулярна Ox: " << (testLine.isPerpendicular() ? "да" : "нет") << std::endl;
}

int main() {
    testLineClass();
    return 0;
}
