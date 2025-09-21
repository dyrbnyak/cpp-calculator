#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString &text){
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::SetActiveNumber(Number number) {
    active_number_ = number;
    ui->l_result->setText(QString::number(active_number_));
}

void MainWindow::AddText(const QString &suffix){
    input_number_ += suffix;
    SetText(input_number_);
}


// Обработка кнопок с цифрами
void MainWindow::on_tb_zero_clicked(){
    AddText("0");
}


void MainWindow::on_tb_one_clicked(){
    AddText("1");
}


void MainWindow::on_tb_two_clicked(){
    AddText("2");
}


void MainWindow::on_tb_three_clicked(){
    AddText("3");
}


void MainWindow::on_tb_four_clicked(){
    AddText("4");
}


void MainWindow::on_tb_five_clicked(){
    AddText("5");
}


void MainWindow::on_tb_six_clicked(){
    AddText("6");
}


void MainWindow::on_tb_seven_clicked(){
    AddText("7");
}


void MainWindow::on_tb_eight_clicked(){
    AddText("8");
}


void MainWindow::on_tb_nine_clicked(){
    AddText("9");
}




// Обработка других кнопок ввода
void MainWindow::on_tb_comma_clicked()
{
    if(input_number_.indexOf(".") == -1){
        AddText(".");
    }
}


void MainWindow::on_tb_negate_clicked()
{

    if (input_number_.isEmpty()) {
        active_number_ = -active_number_;
        ui->l_result->setText(QString::number(active_number_));
    } else {
        if (input_number_.startsWith("-")) {
            SetText(input_number_.mid(1));
        } else if (!input_number_.startsWith("-") && !input_number_.isEmpty()) {
            SetText("-" + input_number_);
        }
    }
}


void MainWindow::on_tb_backspace_clicked()
{
    if(!input_number_.isEmpty()){
        input_number_.chop(1);
        SetText(input_number_);
    }
}




// Нормализация чисел
QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}



//Кнопки операций
void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = op;

    // Обновляем текст в поле l_formula
    ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber()).arg(OpToString(op)));


    // Сброс input_number_ для подготовки к вводу следующего числа
    input_number_.clear();
}

QString MainWindow::OpToString(Operation op) {
    switch (op) {
    case Operation::ADDITION: return "+";
    case Operation::SUBTRACTION: return "−";
    case Operation::MULTIPLICATION: return "×";
    case Operation::DIVISION: return "÷";
    case Operation::POWER: return "^";
    default: return "";
    }
}



void MainWindow::on_tb_power_clicked(){
    SetOperation(Operation::POWER);
}


void MainWindow::on_tb_divide_clicked(){
    SetOperation(Operation::DIVISION);
}


void MainWindow::on_tb_multiplicate_clicked(){
    SetOperation(Operation::MULTIPLICATION);
}


void MainWindow::on_tb_substract_clicked(){
    SetOperation(Operation::SUBTRACTION);
}


void MainWindow::on_tb_add_clicked(){
    SetOperation(Operation::ADDITION);
}


void MainWindow::on_tb_equal_clicked(){
    if(current_operation_ == Operation::NO_OPERATION){
        return;
    }

    ui->l_formula->setText(QString("%1 %2 %3 =").arg(calculator_.GetNumber()).arg(OpToString(current_operation_)).arg(active_number_));

    Calculate(active_number_); // Добавляем вызов метода Calculate
    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::Calculate(Number number) {
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(number);
        break;
    case Operation::DIVISION:
        calculator_.Div(number);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(number);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(number);
        break;
    case Operation::POWER:
        calculator_.Pow(number);
        break;
    default:
        break;
    }

    SetActiveNumber(calculator_.GetNumber());
}



void MainWindow::on_tb_reset_clicked(){
    SetOperation(Operation::NO_OPERATION);
    ui->l_formula->setText("");

    SetText("0");
}


void MainWindow::on_tb_ms_clicked(){
    number_in_memory_ = active_number_;
    was_save_number_in_memory_ = true;
    ui->l_memory->setText("M");
}


void MainWindow::on_tb_mc_clicked(){
    number_in_memory_ = 0;
    was_save_number_in_memory_ = false;
    ui->l_memory->setText("");
}


void MainWindow::on_tn_mr_clicked()
{
    if(was_save_number_in_memory_){
        active_number_ = number_in_memory_;
        ui->l_result->setText(QString::number(number_in_memory_));
        input_number_.clear();
    }
}



