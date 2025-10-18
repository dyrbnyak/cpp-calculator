#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;


// Реализация шаблонного калькулятора.

template <typename T>
class Calculator{
public:
    void Set(T n){
        number_ = n;
    }

    T GetNumber() const{
        return number_;
    }



    //Методы вычисления
    std::optional<Error> Add(T n){
        number_ += n;
        return std::nullopt;
    }


    std::optional<Error> Sub(T n){
        number_ -= n;
        return std::nullopt;
    }


    std::optional<Error> Div(T n){

        if constexpr (std::is_integral<T>::value || std::is_same<T, Rational>::value){
            if(n == 0){
                return "Division by zero";
            }
        }

        number_ /= n;
        return std::nullopt;
    }


    std::optional<Error> Mul(T n){
        number_ *= n;
        return std::nullopt;
    }


    std::optional<Error> Pow(T n){
        if (number_ == 0 && n == 0) {
            return "Zero power to zero";

        } else if constexpr (std::is_integral<T>::value) {
            if(n < 0){
                return "Integer negative power";
            }
            number_ = IntegerPow(number_,n);

        } else if constexpr (std::is_same<T, Rational>::value) {
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_, n);

        } else{
            number_ = pow(number_, n);

        }

        return std::nullopt;
    }



    //Операции над памятью
    void Save(){
        save_number_ = number_;
    }


    void Load(){
        if(GetHasMem())
            number_ = save_number_.value();
    }


    bool GetHasMem() const{
        return save_number_.has_value();
    }


    std::string GetNumberRepr() const{
        return std::to_string(number_);
    }

private:
    T number_ = 0;
    std::optional<T> save_number_;
};
