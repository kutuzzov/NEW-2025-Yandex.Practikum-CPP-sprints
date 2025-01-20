#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

// Напишите функции перегрузок здесь.
istream& operator>>(istream& in, Rational& r) {
    int x, y;
    char slash;
    in >> x >> slash >> y;
    r = Rational(x, y);
    return in;
}

ostream& operator<<(ostream& out, Rational r) {
    out << r.Numerator() << "/" << r.Denominator();
    return out;
}

int main() {
    Rational r1{ 1, 2 };
    cout << r1 << endl; // Вывод: 1/2.

    Rational r2;
    cin >> r2;
    cout << r2;
}
