#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    double a, b, c;

public:
    // Конструктор за замовчуванням
    Triangle() {
        a = 3;
        b = 3;
        c = 5;
    }

    // Конструктор з параметрами
    Triangle(double side1, double side2, double side3) {
        if ((side1 > 0) && (side2 > 0) && (side3 > 0) &&
            (side1 + side2 > side3) &&
            (side1 + side3 > side2) &&
            (side2 + side3 > side1)) {
            a = side1;
            b = side2;
            c = side3;
        }
        else {
            a = 3;
            b = 3;
            c = 5;
            cout << "Incorrect sides. Triangle 3, 3, 5 was created.\n";
        }
    }

    // Конструктор копіювання
    Triangle(const Triangle& other) {
        a = other.a;
        b = other.b;
        c = other.c;
    }

    // Виведення на консоль
    void Print() const {
        cout << "Sides: " << a << ", " << b << ", " << c << endl;
    }

    // Функції доступу
    double GetA() const {
        return a;
    }

    double GetB() const {
        return b;
    }

    double GetC() const {
        return c;
    }

    // Функції ініціалізації
    void SetSides(double side1, double side2, double side3) {
        if ((side1 > 0) && (side2 > 0) && (side3 > 0) &&
            (side1 + side2 > side3) &&
            (side1 + side3 > side2) &&
            (side2 + side3 > side1)) {
            a = side1;
            b = side2;
            c = side3;
        }
        else {
            cout << "Incorrect sides. Values were not changed.\n";
        }
    }

    // Перевірка існування трикутника
    bool IsValid() const {
        return (a > 0) && (b > 0) && (c > 0) &&
            (a + b > c) &&
            (a + c > b) &&
            (b + c > a);
    }

    // Периметр
    double Perimetr() const {
        return a + b + c;
    }

    // Площа за формулою Герона
    double Square() const {
        double p = Perimetr() / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    // Порівняння двох трикутників на рівність за сторонами
    bool IsEqual(const Triangle& other) const {
        return (a == other.a && b == other.b && c == other.c) ||
            (a == other.a && b == other.c && c == other.b) ||
            (a == other.b && b == other.a && c == other.c) ||
            (a == other.b && b == other.c && c == other.a) ||
            (a == other.c && b == other.a && c == other.b) ||
            (a == other.c && b == other.b && c == other.a);
    }

    // Чи є трикутник прямокутним
    bool IsRightAngled() const {
        double x = a, y = b, z = c;

        if (x > z) swap(x, z);
        if (y > z) swap(y, z);

        return fabs(x * x + y * y - z * z) < 1e-9;
    }

    // Чи є трикутник рівнобедреним
    bool IsIsosceles() const {
       return (a == b) || (a == c) || (b == c);
    }

    // Чи є трикутник рівностороннім
    bool IsEquilateral() const {
        return (a == b) && (b == c);
    }
};

void CheckTriangle(const Triangle& t, int number) {
    cout << "Triangle " << number << ":\n";
    t.Print();

    if (!t.IsValid()) {
        cout << "Triangle doesn't exist.\n\n";
        return;
    }

    cout << "Perimeter: " << t.Perimetr() << endl;
    cout << "Square: " << t.Square() << endl;

    if (t.IsRightAngled())
        cout << "This is a right-angled triangle.\n";
    else
        cout << "This is not a right-angled triangle.\n";

    if (t.IsIsosceles())
        cout << "This is an isosceles triangle.\n";
    else
        cout << "This is not an isosceles triangle.\n";

    if (t.IsEquilateral())
        cout << "This is an equilateral triangle.\n";
    else
        cout << "This is not an equilateral triangle.\n";

    cout << endl;
}

int main() {
    Triangle t1(3, 4, 5);
    Triangle t2(3, 3, 3);
    Triangle t3(5, 5, 7);
    Triangle t4;              // конструктор за замовчуванням
    Triangle t5(t1);          // конструктор копіювання

    cout << "-------------------------\n";
    CheckTriangle(t1, 1);
    CheckTriangle(t2, 2);
    CheckTriangle(t3, 3);
    CheckTriangle(t4, 4);
    CheckTriangle(t5, 5);

    cout << "Comparison:\n";
    if (t1.IsEqual(t5))
        cout << "Triangle 1 and Triangle 5 are equal.\n";
    else
        cout << "Triangle 1 and Triangle 5 are not equal.\n";

    cout << "-------------------------\n";

    return 0;
}