#pragma once

#include "calculator.h"
#include "enums.h"
#include <optional>

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //Методы изменения текста
    void SetInputText(const std::string& text);

    void SetErrorText(const std::string& text);

    void SetFormulaText(const std::string& text);

    void SetMemText(const std::string& text);

    void SetExtraKey(const std::optional<std::string>& key);



    //Методы установки колбэк-функций
    void SetDigitKeyCallback(std::function<void(int key)> cb);

    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);

    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);

    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:
    //Кнопки цифр
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




    //Кнопки действий
    void on_tb_extra_clicked();

    void on_tb_negate_clicked();

    void on_tb_backspace_clicked();




    //Кнопки операций
    void on_tb_power_clicked();

    void on_tb_divide_clicked();

    void on_tb_multiplicate_clicked();

    void on_tb_substract_clicked();

    void on_tb_add_clicked();

    void on_tb_equal_clicked();

    void on_tb_reset_clicked();




    //Кнопки работы с памятью
    void on_tb_ms_clicked();

    void on_tb_mc_clicked();

    void on_tn_mr_clicked();


    //Обработка combobox
    void on_cmb_controller_currentIndexChanged();

private:
    Ui::MainWindow* ui;

    //Переменные для callback
    std::function<void(Operation key)> operation_cb_;

    std::function<void(int key)> digit_cb_;

    std::function<void(ControlKey key)> control_cb_;

    std::function<void(ControllerType controller)> controller_cb_;


    //Методы преобразования
    QString RemoveTrailingZeroes(const QString &text);

    QString NormalizeNumber(const QString &text);
};
