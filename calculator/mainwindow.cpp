#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    ui->cmb_controller->clear();
    ui->cmb_controller->addItems({
        "double",
        "float",
        "uint8_t",
        "int",
        "int64_t",
        "size_t",
        "Rational"
    });

    ui->cmb_controller->setFixedSize(100, 25);

    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

}

MainWindow::~MainWindow() {
    delete ui;
}


//Установка значений в калькулятор
void MainWindow::SetInputText(const std::string &text){
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}


void MainWindow::SetErrorText(const std::string &text){
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}


void MainWindow::SetFormulaText(const std::string &text){
    ui->l_formula->setText(QString::fromStdString(text));
}


void MainWindow::SetMemText(const std::string &text){
    ui->l_memory->setText(QString::fromStdString(text));
}


void MainWindow::SetExtraKey(const std::optional<std::string> &key){
    if(!key.has_value()){
        ui->tb_extra->setVisible(false);
        return;
    }

    ui->tb_extra->setVisible(true);
    ui->tb_extra->setText(QString::fromStdString(key.value()));
}





// Callback операторы
void MainWindow::SetDigitKeyCallback(std::function<void (int)> cb){
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void (Operation)> cb){
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void (ControlKey)> cb){
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void (ControllerType)> cb){
    controller_cb_ = cb;
}




// Обработка кнопок с цифрами
void MainWindow::on_tb_zero_clicked(){
    if (digit_cb_) {
        digit_cb_(0);
    }
}


void MainWindow::on_tb_one_clicked(){
    if (digit_cb_) {
        digit_cb_(1);
    }
}


void MainWindow::on_tb_two_clicked(){
    if (digit_cb_) {
        digit_cb_(2);
    }
}


void MainWindow::on_tb_three_clicked(){
    if (digit_cb_) {
        digit_cb_(3);
    }
}


void MainWindow::on_tb_four_clicked(){
    if (digit_cb_) {
        digit_cb_(4);
    }
}


void MainWindow::on_tb_five_clicked(){
    if (digit_cb_) {
        digit_cb_(5);
    }
}


void MainWindow::on_tb_six_clicked(){
    if (digit_cb_) {
        digit_cb_(6);
    }
}

void MainWindow::on_tb_seven_clicked(){
    if (digit_cb_) {
        digit_cb_(7);
    }
}


void MainWindow::on_tb_eight_clicked(){
    if (digit_cb_) {
        digit_cb_(8);
    }
}


void MainWindow::on_tb_nine_clicked(){
    if (digit_cb_) {
        digit_cb_(9);
    }
}





// Обработка других кнопок ввода
void MainWindow::on_tb_extra_clicked()
{
    if(control_cb_){
        control_cb_(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::on_tb_negate_clicked()
{
    if(control_cb_){
        control_cb_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_tb_backspace_clicked()
{
    if(control_cb_){
        control_cb_(ControlKey::BACKSPACE);
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
void MainWindow::on_tb_power_clicked(){
    if(operation_cb_){
        operation_cb_(Operation::POWER);
    }
}


void MainWindow::on_tb_divide_clicked(){
    if(operation_cb_){
        operation_cb_(Operation::DIVISION);
    }
}


void MainWindow::on_tb_multiplicate_clicked(){
    if(operation_cb_){
        operation_cb_(Operation::MULTIPLICATION);
    }
}


void MainWindow::on_tb_substract_clicked(){
    if(operation_cb_){
        operation_cb_(Operation::SUBTRACTION);
    }
}


void MainWindow::on_tb_add_clicked(){
    if(operation_cb_){
        operation_cb_(Operation::ADDITION);
    }
}


void MainWindow::on_tb_equal_clicked(){
    if(control_cb_){
        control_cb_(ControlKey::EQUALS);
    }
}


void MainWindow::on_tb_reset_clicked(){
    if(control_cb_){
        control_cb_(ControlKey::CLEAR);
    }

    SetInputText("0");
}


void MainWindow::on_tb_ms_clicked(){
    if(control_cb_){
        control_cb_(ControlKey::MEM_SAVE);
    }

    ui->l_memory->setText("M");
}


void MainWindow::on_tb_mc_clicked(){
    if(control_cb_){
        control_cb_(ControlKey::MEM_CLEAR);
    }

    ui->l_memory->setText("");
}

//Не знаю, почему, но в видео примере эта кнопка MR,
//хотя в ControlKey - ML и, чисто логически, Memory Load - ML
//но оставлю, как есть в видео примере
void MainWindow::on_tn_mr_clicked()
{
    if(control_cb_){
        control_cb_(ControlKey::MEM_LOAD);
    }
}


void MainWindow::on_cmb_controller_currentIndexChanged(){
    if (controller_cb_) {
        QString selectedText = ui->cmb_controller->currentText();
        ControllerType controllerType;

        if (selectedText == "double") {
            controllerType = ControllerType::DOUBLE;
        } else if (selectedText == "float") {
            controllerType = ControllerType::FLOAT;
        } else if (selectedText == "uint8_t") {
            controllerType = ControllerType::UINT8_T;
        } else if (selectedText == "int") {
            controllerType = ControllerType::INT;
        } else if (selectedText == "int64_t") {
            controllerType = ControllerType::INT64_T;
        } else if (selectedText == "size_t") {
            controllerType = ControllerType::SIZE_T;
        } else if (selectedText == "Rational") {
            controllerType = ControllerType::RATIONAL;
        }

        controller_cb_(controllerType);
    }
}
