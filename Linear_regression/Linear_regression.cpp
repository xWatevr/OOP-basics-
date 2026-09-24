#include <iostream>


class ArithmeticProgression
{
private:
	double a1, d;

public:
	// конструктор за замовченням
	ArithmeticProgression() {
		a1 = 0;
		d = 1;
	}

	// конструктор ініціалізації
	ArithmeticProgression(double a, double diff) {
		a1 = a;
		d = diff;
	}

	// конструктор копіювання 
	ArithmeticProgression(const ArithmeticProgression& other)
	{
		a1 = other.a1;
		d = other.d;
	}

	// оператор присвоєння 
	ArithmeticProgression& operator=(const ArithmeticProgression& other) {
		a1 = other.a1;
		d = other.d;
		return *this;
	}

	// сума
	ArithmeticProgression operator+(const ArithmeticProgression& other) const {
		return ArithmeticProgression(a1 + other.a1, d + other.d);
	}

	// різниця
	ArithmeticProgression operator-(const ArithmeticProgression& other) const {
		return ArithmeticProgression(a1 - other.a1, d - other.d);
	}

	// множення на число
	ArithmeticProgression operator*(double k) const {
		return ArithmeticProgression(a1 * k, d * k);
	}

	// n-й елемент
	double operator[](int n) const {
		return a1 + (n - 1) * d;
	}

	// сумма перших n
	double operator()(int n) const {
		return (2 * a1 + d * (n - 1)) * n / 2;
	}

	// порівняння
	bool operator==(const ArithmeticProgression& other) const {
		return a1 == other.a1 && d == other.d;
	}

	bool operator!=(const ArithmeticProgression& other) const {
		return !(*this == other);
	}

	// ввід
	friend std::istream& operator>>(std::istream& in, ArithmeticProgression& p) {
		in >> p.a1 >> p.d;
		return in;
	}
	// вивід
	friend std::ostream& operator<<(std::ostream& out, const ArithmeticProgression& p) {
		out << "a1=" << p.a1 << " d=" << p.d;
		return out;
	}
};



int main() {
	ArithmeticProgression p1(1, 2);
	ArithmeticProgression p2(2, 1);

	std::cout << "--- TEST + (Addition) ---\n";
	std::cout << p1 + p2 << std::endl;
	std::cout << p1 + p1 << std::endl;

	std::cout << "\n--- TEST - (Subtraction) ---\n";
	std::cout << p1 - p2 << std::endl;
	std::cout << p2 - p1 << std::endl;

	std::cout << "\n--- TEST * (Multiplication by scalar) ---\n";
	std::cout << p1 * 2 << std::endl;
	std::cout << p2 * 3 << std::endl;

	std::cout << "\n--- TEST [] (n-th element) ---\n";
	std::cout << p1[1] << std::endl;
	std::cout << p1[5] << std::endl;

	std::cout << "\n--- TEST () (Sum of first n elements) ---\n";
	std::cout << p1(3) << std::endl;
	std::cout << p2(4) << std::endl;

	std::cout << "\n---TEST == and != (Comparison) ---\n";
	ArithmeticProgression p3(1, 2);
	std::cout << (p1 == p3) << std::endl;
	std::cout << (p1 != p2) << std::endl;

	std::cout << "\n--- TEST = (Assignment) ---\n";
	ArithmeticProgression p4;
	p4 = p1;
	std::cout << p4 << std::endl;

	ArithmeticProgression p5;
	p5 = p2;
	std::cout << p5 << std::endl;

	std::cout << "\n--- TEST Copy Constructor ---\n";
	ArithmeticProgression p6(p1);
	std::cout << p6 << std::endl;

	std::cout << "\n--- TEST Input/Output ---\n";
	ArithmeticProgression p7;
	std::cout << "Enter a1 and d: ";
	std::cin >> p7;
	std::cout << p7 << std::endl;

	return 0;
}
