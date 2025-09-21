#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION,  // Операция не задана
    ADDITION,      // Плюс
    SUBTRACTION,   // Минус
    MULTIPLICATION,// Умножить
    DIVISION,      // Поделить
    POWER          // Возведение в степень
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //сохраняет результат в input_number_ и помещает его в l_result.
    void SetText(const QString& text);


    //допишет к input_number_ нужный текст и вызовет SetText.
    void AddText(const QString& suffix);


    //Устанвока операции
    void SetOperation(Operation op);

    //Установка активнго числа
    void SetActiveNumber(double number);

private slots:
    //Кнопка цифры "0"
    void on_tb_zero_clicked();

    //Кнопка цифры "1"
    void on_tb_one_clicked();

    //Кнопка цифры "2"
    void on_tb_two_clicked();

    //Кнопка цифры "3"
    void on_tb_three_clicked();

    //Кнопка цифры "4"
    void on_tb_four_clicked();

    //Кнопка цифры "5"
    void on_tb_five_clicked();

    //Кнопка цифры "6"
    void on_tb_six_clicked();

    //Кнопка цифры "7"
    void on_tb_seven_clicked();

    //Кнопка цифры "8"
    void on_tb_eight_clicked();

    //Кнопка цифры "9"
    void on_tb_nine_clicked();



    //Кнопка ".". Вызывает AddText(".").
    //При этом, если в input_number_ уже есть точка, кнопка ничего не должна делать.
    void on_tb_comma_clicked();

    //Кнопка "±". Добавляет или убирает минус в начале
    void on_tb_negate_clicked();

    //Кнопка "⌫" убирает последний символ.
    //Она ничего не делает, если число и так пустое.
    void on_tb_backspace_clicked();


    //Кнопка "xʸ" возводит в степень. Operation::POWER
    void on_tb_power_clicked();

    //Кнопка "÷" делит число. Operation::DIVISION
    void on_tb_divide_clicked();

    //Кнопка "×" умножает. Operation::MULTIPLICATION
    void on_tb_multiplicate_clicked();

    //Кнопка "-" вычитает. Operation::SUBTRACTION
    void on_tb_substract_clicked();

    //Кнопка "+" складывает. Operation::ADDITION
    void on_tb_add_clicked();

    //Кнопка "=" выводит результат.
    void on_tb_equal_clicked();

    //Кнопка "C" очищает калькулятор
    void on_tb_reset_clicked();

    //Кнопка "MS" сохраняет в память число active_number_
    void on_tb_ms_clicked();

    //Кнопка "MC" очищает память
    void on_tb_mc_clicked();

    //Кнопка "MR" помещает сохранённое значение в active_number_ и l_result.
    //При этом input_number_ очищается.
    void on_tn_mr_clicked();

private:
    Ui::MainWindow* ui;

    //Выполнение операции
    void Calculate(double number);

    //Введенное число хранится ввиде строки
    QString input_number_;

    //Число, которое используется в вычислениях
    double active_number_;

    //Действующая операция. Значение по умолчанию Operation::NO_OPERATION
    Operation current_operation_ = Operation::NO_OPERATION;

    //Калькулятор хранит некоторое число.
    //Это число будет использоваться как левая часть выражения.
    Calculator calculator_;

    //Число, хранящиеся в памяти
    double number_in_memory_;

    //Флаг указывающий, было ли сохранено какое-либо число в память
    bool was_save_number_in_memory_ = false;

    //Убирает лишние нули перед 0
    QString RemoveTrailingZeroes(const QString &text);

    //Нормализирует числа
    QString NormalizeNumber(const QString &text);


    //Переводит операцию в QString
    QString OpToString(Operation op);
};
