#include <iostream>
#include <string>
#include <locale>

class Figure {
protected:
    std::string name;
    int sides_count;

public:
    Figure(const std::string& name, int sides_count) : name(name), sides_count(sides_count) {}

    virtual bool check() const {
        return sides_count == 0;  // У базовой фигуры всегда 0 сторон
    }

    virtual void print_info() const {
        std::cout << name << ":\n"
            << (check() ? "Правильная\n" : "Неправильная\n")
            << "Количество сторон: " << sides_count << "\n";
    }

    virtual ~Figure() = default;
};

// Класс для треугольников
class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : Figure("Треугольник", 3), a(a), b(b), c(c), A(A), B(B), C(C) {}

    bool check() const override {
        return (A + B + C == 180);  // Проверка суммы углов в треугольнике
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << "\n\n";
    }
};

// Прямоугольный треугольник
class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) {}

    bool check() const override {
        return (Triangle::check() && C == 90);  // Угол C всегда 90
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n"
            << "Углы: A=" << A << " B=" << B << " C=90\n\n";
    }
};

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {}

    bool check() const override {
        return (Triangle::check() && a == c && A == C);  // a == c и A == C
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << "\n\n";
    }
};

// Равносторонний треугольник
class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side) : Triangle(side, side, side, 60, 60, 60) {}

    bool check() const override {
        return (Triangle::check() && a == b && b == c && A == 60 && B == 60 && C == 60);
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n"
            << "Углы: A=60 B=60 C=60\n\n";
    }
};

// Класс для четырёхугольников
class Quadrangle : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure("Четырёхугольник", 4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    bool check() const override {
        return (A + B + C + D == 360);  // Сумма углов в четырёхугольнике равна 360
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n\n";
    }
};

// Прямоугольник
class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b) : Quadrangle(a, b, a, b, 90, 90, 90, 90) {}

    bool check() const override {
        return (Quadrangle::check() && a == c && b == d && A == 90 && B == 90 && C == 90 && D == 90);
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=90 B=90 C=90 D=90\n\n";
    }
};

// Квадрат
class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}

    bool check() const override {
        return (Rectangle::check() && a == b && b == c && c == d);
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=90 B=90 C=90 D=90\n\n";
    }
};

// Параллелограмм
class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B) : Quadrangle(a, b, a, b, A, B, A, B) {}

    bool check() const override {
        return (Quadrangle::check() && a == c && b == d && A == C && B == D);
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n\n";
    }
};

// Ромб
class Rhombus : public Parallelogram {
public:
    Rhombus(int side, int A, int B) : Parallelogram(side, side, A, B) {}

    bool check() const override {
        return (Parallelogram::check() && a == b && b == c && c == d);
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Figure* figures[] = {
        new Triangle(10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 90),
        new IsoscelesTriangle(10, 20, 50, 60),
        new EquilateralTriangle(30),
        new Quadrangle(10, 20, 30, 40, 50, 60, 70, 80),
        new Rectangle(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (const auto& figure : figures) {
        figure->print_info();
        delete figure;
    }

    return 0;
}
