#pragma once

#include <string>

using Number = double;

class Calculator{
public:
    //Заменяет текущее число (результат) на число n
    void Set(Number n);

    //Возвращает текущий результат вычислений калькулятора.
    //В только что сконструированном калькуляторе этот метод возвращает 0.
    Number GetNumber() const;

    //сложение
    void Add(Number n);

    //разность
    void Sub(Number n);

    //разделение
    void Div(Number n);

    //умножение
    void Mul(Number n);

    //возведение в степень
    void Pow(Number n);

    //Сохраняет текущий результат в ячейку памяти калькулятора
    void Save();

    //Загружает число из памяти калькулятора в текущий результат
    void Load();

    //Возвращает true, если ячейка памяти непустая.
    bool HasMem() const;

    //Возвращает текущее число,
    //преобразуя его в std::string функцией std::to_string.
    std::string GetNumberRepr() const;

private:

    Number number_ = 0;
    Number save_number_ = 0;
    bool is_save_ = false;
};


