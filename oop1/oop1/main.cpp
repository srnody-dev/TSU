//  oop1
//
//  Created by srnody on 23.09.2025.
//

#include <iostream>
#include <cmath>
using namespace std;

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
        cout << a << "x + " << b << "y + " << c << " = 0" << endl;
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
    
    //6) нахождение углового коэффициента прямой;
    
    //k = -a/b
    
    void printSlopeInfo() const {
        if (b == 0) {
            cout << "Прямая вертикальная и угловой коэффициент не существует т.к b=0" << endl;
        } else {
            cout << "Угловой коэффициент: " << (-a / b) << endl;
        }
    }
    
    //7) проверка параллельности двух прямых (через операцию ||);
    
    //a1*b2=a2*b1
    bool operator||(const Line& other) const {
        return (a * other.b == other.a * b);
    }
    
    //8) проверка перпендикулярности двух прямых;
    //a1*a2+b1*b2=0
    bool isPerpendicularTo(const Line& other) const {
        return (a * other.a + b * other.b == 0);
    }
    
    
    //9) нахождение расстояния от начала координат до прямой;
    // d=|c|/(sqrt(a^2 +b^2)
    double distance() const{
        return (abs(c)/
                sqrt((a*a) + (b*b))
                );
    }
    
    //10) проверка принадлежности точки прямой;
    
    bool belongs(double x0, double y0) const {
        return abs(a * x0 + b * y0 + c) < 1e-9;
    }
    
    
    //11) нахождение острого угла между пересекающимися прямыми;
    
    //cos(ф)=|(aa1+bb1) / ( sqrt(a^2+b^2) sqrt(a1^2+b1^2) )|
    
    
    double spiceCornerTo(const Line& other) const{
        double numerator = abs(a * other.a + b * other.b);
        double denominator = sqrt(a * a + b * b) * sqrt(other.a * other.a + other.b * other.b);
        double cosCorner = numerator / denominator;
        double cornerRad = acos(cosCorner);
        return cornerRad;
    }
    
}
    
    ;
    
    void testLineClass() {
        
        Line testLine;
        testLine.input();
        cout << "Прямая: "; testLine.output();
        cout << "Проходит через начало координат(0,0): " << (testLine.isStart() ? "да" : "нет") << endl;
        cout << "Перпендикулярна Ox: " << (testLine.isPerpendicular() ? "да" : "нет") <<endl;
        
        testLine.printSlopeInfo();
        
        cout << "\nВведите коэффициенты второй прямой для сравнения:" << endl;
        Line testLine2;
        testLine2.input();
        cout << "Вторая прямая: "; testLine2.output();
        
        cout << "Прямые параллельны: " << (testLine || testLine2 ? "да" : "нет") << endl;
        
        cout << "Прямые перпендикулярны: " << (testLine.isPerpendicularTo(testLine2) ? "да" : "нет") << endl;
        
        cout << "Расстояние от начала координат до прямой: " << testLine.distance() << endl;
        
        double x0, y0;
        cout << "Введите координаты точки (x0, y0) для проверки принадлежности точки: ";
        cin >> x0 >> y0;
        cout << "Точка (" << x0 << "," << y0 << ") принадлежит прямой: "
        << (testLine.belongs(x0,y0) ? "да" : "нет") << endl;
        
        if (!(testLine || testLine2)) {
            double cornerRad = testLine.spiceCornerTo(testLine2);
                double cornerDegree = cornerRad * (180 / M_PI);
            cout << "Угол между прямыми: " << "в радианах: "<< cornerRad  << " в градусах: " << cornerDegree<<endl;
        } else {
            cout << "Прямые параллельны" << endl;
        }
    }

int main() {
    testLineClass();
    return 0;
}
