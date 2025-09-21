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

private slots:
    //Объявление функций для обработки кнопок с цифрами
    void on_tb_zero_clicked();

    void on_tb_one_clicked();

    void on_tb_two_clicked();

    void on_tb_three_clicked();

    void on_tb_four_clicked();

    void on_tb_five_clicked();

    void on_tb_six_clicked();

    void on_tb_seven_clicked();

    void on_tb_eight_clicked();

    void on_tb_nine_clicked();


    // Объявлении функция для обработки кнопок операций
    void on_tb_comma_clicked();

    void on_tb_negate_clicked();

    void on_tb_backspace_clicked();

    void on_tb_power_clicked();

    void on_tb_divide_clicked();

    void on_tb_multiplicate_clicked();

    void on_tb_substract_clicked();

    void on_tb_add_clicked();

    void on_tb_equal_clicked();

    void on_tb_reset_clicked();

    void on_tb_ms_clicked();

    void on_tb_mc_clicked();

    void on_tn_mr_clicked();

private:
    Ui::MainWindow* ui;

    void Calculate(Number number);

    QString input_number_;

    Number active_number_;

    Operation current_operation_ = Operation::NO_OPERATION;

    //Калькулятор хранит некоторое число.
    //Это число будет использоваться как левая часть выражения.
    Calculator calculator_;

    Number number_in_memory_;

    bool was_save_number_in_memory_ = false;

    QString RemoveTrailingZeroes(const QString &text);

    QString NormalizeNumber(const QString &text);

    QString OpToString(Operation op);

    //сохраняет результат в input_number_ и помещает его в l_result.
    void SetText(const QString& text);

    //допишет к input_number_ нужный текст и вызовет SetText.
    void AddText(const QString& suffix);

    void SetOperation(Operation op);

    void SetActiveNumber(double number);
};
