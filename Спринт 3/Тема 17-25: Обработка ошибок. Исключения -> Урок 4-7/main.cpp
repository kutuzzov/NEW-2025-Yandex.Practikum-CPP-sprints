#include <iostream>
#include <numeric>
#include <stdexcept>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int value)
        : numerator_(value)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator)
    {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational& operator+=(Rational right) {
        numerator_ = numerator_ * right.denominator_ + right.numerator_ * denominator_;
        denominator_ *= right.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator-=(Rational right) {
        numerator_ = numerator_ * right.denominator_ - right.numerator_ * denominator_;
        denominator_ *= right.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator*=(Rational right) {
        numerator_ *= right.numerator_;
        denominator_ *= right.denominator_;
        Normalize();
        return *this;
    }

    Rational& operator/=(Rational right) {
        numerator_ *= right.denominator_;
        denominator_ *= right.numerator_;
        if (denominator_ == 0) {
            throw invalid_argument("деление на ноль!"s);
        }
        Normalize();
        return *this;
    }

private:
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int n = gcd(numerator_, denominator_);
        numerator_ /= n;
        denominator_ /= n;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

ostream& operator<<(ostream& output, Rational rational) {
    return output << rational.Numerator() << '/' << rational.Denominator();
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator;
    int denominator;
    char slash;
    if ((input >> numerator) && (input >> slash) && (slash == '/') && (input >> denominator)) {
        rational = Rational{ numerator, denominator };
    }
    return input;
}

// Unary plus and minus

Rational operator+(Rational value) {
    return value;
}

Rational operator-(Rational value) {
    return { -value.Numerator(), value.Denominator() };
}

// Binary arithmetic operations

Rational operator+(Rational left, Rational right) {
    return left += right;
}

Rational operator-(Rational left, Rational right) {
    return left -= right;
}

Rational operator*(Rational left, Rational right) {
    return left *= right;
}

Rational operator/(Rational left, Rational right) {
    return left /= right;
}

// Comparison operators

bool operator==(Rational left, Rational right) {
    return left.Numerator() == right.Numerator() &&
        left.Denominator() == right.Denominator();
}

bool operator!=(Rational left, Rational right) {
    return !(left == right);
}

bool operator<(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() <
        left.Denominator() * right.Numerator();
}

bool operator>(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() >
        left.Denominator() * right.Numerator();
}

bool operator>=(Rational left, Rational right) {
    return !(left < right);
}

bool operator<=(Rational left, Rational right) {
    return !(left > right);
}

int main() {
#ifdef _WIN32
    system("chcp 1251");
    std::cout << std::endl;
#endif

    try {
        const Rational three_fifth{ 3, 5 };
        const Rational zero;
        cout << three_fifth << " / " << zero << " = " << (three_fifth / zero) << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: "s << e.what() << endl;
    }
    try {
        Rational value{ 3, 5 };
        value /= Rational();
        // Следующая строка не должна выполниться
        cout << value << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: "s << e.what() << endl;
    }
}
