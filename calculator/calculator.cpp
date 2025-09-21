#include "calculator.h"

#include <cmath>


void Calculator::Set(Number n){
    number_ = n;
}

Number Calculator::GetNumber() const{
    return number_;
}

void Calculator::Add(Number n){
    number_ += n;
}

void Calculator::Sub(Number n){
    number_ -= n;
}

void Calculator::Div(Number n){
    number_ /= n;
}

void Calculator::Mul(Number n){
    number_ *= n;
}

void Calculator::Pow(Number n){
    number_ = std::pow(number_,n);
}

void Calculator::Save(){
    is_save_ = true;
    save_number_ = number_;
}

void Calculator::Load(){
    if(HasMem())
        number_ = save_number_;
}

bool Calculator::HasMem() const{
    return is_save_;
}

std::string Calculator::GetNumberRepr() const{
    return std::to_string(number_);
}
