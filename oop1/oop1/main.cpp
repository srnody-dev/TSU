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
        double aInput,bInput,cInput;
        std::cout << "Введите коэффициенты a, b, c уравнения ax + by + c = 0: ";
        std::cin >> aInput >> bInput >> cInput;
        
        
        setA(aInput);
        setB(bInput);
        setC(cInput);
        
    }
    
    void output() const {
        cout << getA() << "x + " << getB() << "y + " << getC() << " = 0" << endl;
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
        return getC() == 0;
    }
    //5) проверка, перпендикулярна ли прямая оси Ox;
    bool isPerpendicular() const {
        return getB() == 0;
    }
    
    //6) нахождение углового коэффициента прямой;
    
    //k = -a/b
    
    void printSlopeInfo() const {
        if (getB() == 0) {
            cout << "Прямая вертикальная и угловой коэффициент не существует т.к b=0" << endl;
        } else {
            cout << "Угловой коэффициент: " << (-getA() / getB()) << endl;
        }
    }
    
    //7) проверка параллельности двух прямых (через операцию ||);
    
    //a1*b2=a2*b1
    bool operator || (const Line& other) const {
        return (getA() * other.getB() == other.getA() * getB());
    }
    
    //8) проверка перпендикулярности двух прямых;
    //a1*a2+b1*b2=0
    bool isPerpendicularTo(const Line& other) const {
        return (getA() * other.getA() + getB() * other.getB() == 0);
    }
    
    
    //9) нахождение расстояния от начала координат до прямой;
    // d=|c|/(sqrt(a^2 +b^2)
    double distance() const{
        return (abs(getC())/
                sqrt((getA()*getA()) + (getB()*getB()))
                );
    }
    
    //10) проверка принадлежности точки прямой;
    
    bool belongs(double x0, double y0) const {
        return abs(getA() * x0 + getB() * y0 + getC()) < 1e-9;
    }
    
    
    //11) нахождение острого угла между пересекающимися прямыми;
    
    //cos(ф)=|(aa1+bb1) / ( sqrt(a^2+b^2) sqrt(a1^2+b1^2) )|
    
    
    double spiceCornerTo(const Line& other) const{
        double numerator = abs(getA() * other.getA() + getB() * other.getB());
        double denominator = sqrt(getA() * getA() + getB() * getB()) * sqrt(other.getA() * other.getA() + other.getB() * other.getB());
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
        cout << "Введите координаты точки (x0, y0) для проверки принадлежности точки для прямой 1 : ";
        cin >> x0 >> y0;
        cout << "Точка (" << x0 << "," << y0 << ") принадлежит прямой 1 : "
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
