#include "rational.h"

int Nod(int first, int second) {
    while (first * second != 0) {
        if (first > second) {
            first %= second;
        } else {
            second %= first;
        }
    }
    return first + second;
}

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {
}

Rational::Rational(int numer, int denom) {
    if (!denom) {
        throw RationalDivisionByZero{};
    }

    denom_ = abs(denom);
    numer_ = numer * (denom / abs(denom));

    int nod = Nod(abs(numer_), denom_);

    denom_ /= nod;
    numer_ /= nod;
}

void Rational::Set(int64_t numer, int64_t denom) {
    SetNumerator(static_cast<int>(numer));
    SetDenominator(static_cast<int>(denom));
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {

    numer_ = value * (denom_ / std::abs(denom_));

    int nod = Nod(std::abs(numer_), denom_);

    denom_ /= nod;
    numer_ /= nod;
}

void Rational::SetDenominator(int value) {

    if (!value) {
        throw RationalDivisionByZero{};
    }

    denom_ = abs(value);
    numer_ = numer_ * (value / std::abs(value));

    int n = Nod(std::abs(numer_), denom_);

    denom_ /= n;
    numer_ /= n;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int lm = (lhs.denom_ * rhs.denom_) / Nod(lhs.denom_, rhs.denom_);

    lhs.numer_ = (lhs.numer_ * (lm / lhs.denom_)) + (rhs.numer_ * (lm / rhs.denom_));
    lhs.denom_ = lm;

    int n = Nod(abs(lhs.numer_), lhs.denom_);
    if (!n) {
        throw RationalDivisionByZero{};
    }
    lhs.denom_ /= n;
    lhs.numer_ /= n;

    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.numer_ = lhs.numer_ * rhs.numer_;
    lhs.denom_ = lhs.denom_ * rhs.denom_;

    int nod = Nod(abs(lhs.numer_), lhs.denom_);
    if (!nod) {
        throw RationalDivisionByZero{};
    }
    lhs.denom_ /= nod;
    lhs.numer_ /= nod;

    return lhs;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += (-rhs);
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }

    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetNumerator());

    int n = Nod(abs(lhs.GetNumerator()), abs(lhs.GetDenominator()));
    if (!n) {
        throw RationalDivisionByZero{};
    }
    lhs.SetDenominator(lhs.GetDenominator() / n);
    lhs.SetNumerator(lhs.GetNumerator() / n);

    if (lhs.GetDenominator() < 0) {
        lhs.SetNumerator(-lhs.GetNumerator());
        lhs.SetDenominator(-lhs.GetDenominator());
    }

    return lhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result -= rhs;
    return result;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result /= rhs;
    return result;
}

Rational& operator++(Rational& ratio) {
    ratio += 1;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio -= 1;
    return ratio;
}

Rational operator++(Rational& ratio, int) {
    Rational result = ratio;
    ++ratio;
    return result;
}

Rational operator--(Rational& ratio, int) {
    Rational result = ratio;
    --ratio;
    return result;
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    int lcm = (lhs.GetDenominator() * rhs.GetDenominator()) / Nod(lhs.GetDenominator(), rhs.GetDenominator());
    int lhs_numer = lhs.GetNumerator() * (lcm / lhs.GetDenominator());
    int rhs_numer = rhs.GetNumerator() * (lcm / rhs.GetDenominator());

    return lhs_numer < rhs_numer;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() == rhs.GetNumerator()) && (lhs.GetDenominator() == rhs.GetDenominator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string in;
    is >> in;

    size_t slash_pos = in.find('/');

    if (slash_pos == std::string::npos) {
        int numerator = std::stoi(in);
        ratio.SetNumerator(numerator);
        ratio.SetDenominator(1);
    } else {
        int num = std::stoi(in.substr(0, slash_pos));
        int denom = std::stoi(in.substr(slash_pos + 1));
        if (denom == 0) {
            throw RationalDivisionByZero{};
        }
        ratio.SetNumerator(num);
        ratio.SetDenominator(denom);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    }
    return os;
}