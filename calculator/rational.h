#pragma once
#include <cstdint>
#include <compare>
#include <iostream>
#include <numeric>
#include <cstdlib>



class Rational{
public:
    //Конструкторы
    Rational() = default;

    Rational(int numerator): numerator_(numerator){
        denominator_ = 1;
    }

    Rational(int numerator, int denominator): numerator_(numerator), denominator_(denominator){
        Reduction();
    };

    Rational(const Rational& r): numerator_(r.numerator_), denominator_(r.denominator_) {
        Reduction();
    }

    //Перегрузка операторов
    friend std::ostream& operator<<(std::ostream &os, const Rational& rational);
    friend std::istream& operator>>(std::istream &is,  Rational& rational);


    Rational operator+(const Rational& r) const{
        int new_numerator = numerator_ * r.denominator_ + r.numerator_ * denominator_;
        int new_denominator = denominator_ * r.denominator_;

        Rational result(new_numerator, new_denominator);
        result.Reduction();

        return result;
    }

    Rational operator-(const Rational& r) const{
        int new_numerator = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        int new_denominator = denominator_ * r.denominator_;

        Rational result(new_numerator, new_denominator);
        result.Reduction();

        return result;
    }

    Rational operator*(const Rational& r) const{
        int new_numerator = numerator_ * r.numerator_;
        int new_denominator = denominator_ * r.denominator_;

        Rational result(new_numerator, new_denominator);
        result.Reduction();

        return result;
    }

    Rational operator/(const Rational& r) const{
        Rational result(*this);
        result *= r.Inv();
        result.Reduction();

        return result;
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + r.numerator_ * denominator_;
        denominator_ = denominator_ * r.denominator_;
        Reduction();

        return *this;
    }

    Rational& operator-=(const Rational& r){
        numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        denominator_ = denominator_ * r.denominator_;
        Reduction();

        return *this;
    }

    Rational& operator*=(const Rational& r){
        numerator_ = numerator_ * r.numerator_;
        denominator_ = denominator_ * r.denominator_;

        Reduction();

        return *this;
    }

    Rational& operator/=(const Rational& r){
        numerator_ = numerator_ * r.denominator_;
        denominator_ = denominator_ * r.numerator_;

        Reduction();

        return *this;
    }

    Rational& operator=(const Rational& r){
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;

        Reduction();

        return *this;
    }

    const Rational& operator+() const{
        return *this;
    }

    Rational operator-() const{
        return Rational(-numerator_, denominator_);
    }


    bool operator==(const Rational& r) const = default;

    auto operator<=>(const Rational& r2) const{

        auto ls = static_cast<std::int64_t>(GetNumerator()) * static_cast<std::int64_t>(r2.GetDenominator());
        auto rs = static_cast<std::int64_t>(r2.GetNumerator()) * static_cast<std::int64_t>(GetDenominator());

        return ls <=> rs;
    }

    // методы
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    Rational Inv() const{
        Rational result(denominator_, numerator_);

        return result;
    }

    int GetNumerator() const{
        return numerator_;
    }

    int GetDenominator() const{
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};


inline std::ostream& operator<<(std::ostream &os, const Rational &rational){
    int numerator = rational.GetNumerator();
    int denominator = rational.GetDenominator();


    if(denominator == 1){
        os << numerator;
    }else {
        os << numerator << " / " << denominator;
    }

    return os;
}

inline std::istream& operator>>(std::istream &is, Rational &rational){
    int numerator, denominator;
    char div;

    if (!(is >> numerator)) {
        is.setstate(std::ios::failbit);
        return is; // Ошибка ввода числителя
    }

    // Проверка наличия разделителя
    if (!(is >> std::ws >> div) || div != '/') {
        denominator = 1; // Если разделитель не найден, знаменатель по умолчанию равен 1
        is.clear();      // Сброс состояния ошибки потока
    } else if  (!(is >> std::ws >> denominator) || denominator == 0){
        is.setstate(std::ios::failbit);
        return is; // Ошибка ввода знаменателя
    }

    rational.numerator_ = numerator;
    rational.denominator_ = denominator;

    rational.Reduction();

    return is;
}
