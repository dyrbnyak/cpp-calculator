#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <QMessageBox>
#include <algorithm>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <cctype>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937 &random_gen){
    random_gen_ = random_gen;
}






//Методы
void MainWindow::on_btn_clear_clicked(){
    deque_model_.items.clear();
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_push_front_clicked(){
    std::string set_text = ui->txt_elem_content->text().toStdString();

    deque_model_.items.push_front(set_text);
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_pop_front_clicked(){
    deque_model_.items.pop_front();
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_push_back_clicked(){
    std::string set_text = ui->txt_elem_content->text().toStdString();

    deque_model_.items.push_back(set_text);
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_pop_back_clicked(){
    deque_model_.items.pop_back();
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_insert_clicked(){
    deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().toStdString());
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_erase_clicked(){
    deque_model_.items.erase(deque_model_.iterator);
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}








//Алгоритмы
void MainWindow::on_btn_lower_bound_clicked(){
    if(!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())){
        return;
    }

    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(),
                                             deque_model_.items.end(),
                                             ui->txt_elem_content->text().toStdString());

    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked(){
    if(!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())){
        return;
    }

    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(),
                                             deque_model_.items.end(),
                                             ui->txt_elem_content->text().toStdString());

    ApplyIterator();
}

void MainWindow::on_btn_min_el_clicked(){
    auto it = std::min_element(deque_model_.items.begin(), deque_model_.items.end());

    if(it != deque_model_.items.end()){
        deque_model_.iterator = it;
        deque_model_.iterator = it;
    }

    ApplyIterator();
}

void MainWindow::on_btn_max_el_clicked(){
    auto it = std::max_element(deque_model_.items.begin(), deque_model_.items.end());

    if(it != deque_model_.items.end()){
        deque_model_.iterator = it;
    }

    ApplyIterator();
}

void MainWindow::on_btn_sort_clicked(){
    deque_model_.items = MergeSort(deque_model_.items, std::less<>());
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_sOrT_clicked(){
    auto compare_ci = [](const std::string& l, const std::string& r) {
        return QString::compare(QString::fromStdString(l), QString::fromStdString(r), Qt::CaseInsensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, compare_ci);

    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_unique_clicked(){
    if(std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())){
        auto to_del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(to_del, deque_model_.items.end());

        deque_model_.iterator = deque_model_.items.begin();

        ApplyModel();
        ApplyIterator();
    }
}


void MainWindow::on_btn_reverse_clicked(){
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());

    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_btn_shuffle_clicked(){
    // Создание генератора со случайным начальным значением.
    std::mt19937 gen_shuffle(random_gen_);
    SetRandomGen(gen_shuffle);


    // Перемешаем элементы в векторе.
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen_shuffle);


    ApplyModel();
    ApplyIterator();
}









//Итераторы
void MainWindow::on_btn_dec_iterator_clicked(){
    if (deque_model_.iterator != deque_model_.items.begin()) {
        deque_model_.iterator -= 1;
        ApplyIterator();
    }
}

void MainWindow::on_btn_inc_iterator_clicked(){
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.iterator += 1;
        ApplyIterator();
    }
}

void MainWindow::on_btn_begin_clicked(){
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked(){
    deque_model_.iterator = deque_model_.items.end();

    ApplyIterator();
}





//Заготовки
void MainWindow::on_btn_tea_clicked(){
    deque_model_.items = tea;
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_cakes_clicked(){
    deque_model_.items = cakes;
    ApplyModel();

    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}




//Другие кнопки работы с очередью
void MainWindow::on_btn_edit_clicked(){
    int index = std::distance(deque_model_.items.begin(),deque_model_.iterator);
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items[index] = text;

    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_resize_clicked(){
    int text_from_txt_size = ui->txt_size->text().toInt();
    deque_model_.items.resize(text_from_txt_size);
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_btn_find_clicked(){
    std::string text = ui->txt_elem_content->text().toStdString();
    auto it = std::find(deque_model_.items.begin(), deque_model_.items.end(), text);
    deque_model_.iterator = it;


    ApplyIterator();
}


void MainWindow::on_btn_count_clicked(){
    int count = std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toStdString());

    ui->lbl_count->setText(QString::number(count));
}




//Методы применения изменений
void MainWindow::ApplyModel() {
    if(deque_model_.items.empty()){
        ui->list_widget->clear();
        ui->txt_size->setText(QString::number(0));
        ui->txt_elem_content->clear();
        ui->list_widget->addItem("end");

        SetAbleDisableBtn();
        return;
    }

    int size_deque = deque_model_.items.size();
    ui->txt_size->setText(QString::number(size_deque));


    auto preserve_iter = deque_model_.iterator;
    ui->list_widget->clear();

    for(int i = 0; i < size_deque; ++i){
        ui->list_widget->addItem(QString::number(i) + ": " + QString::fromStdString(deque_model_.items[i]));
    }

    ui->list_widget->addItem("end");
    deque_model_.iterator = preserve_iter;

    SetAbleDisableBtn();
}

void MainWindow::ApplyIterator(){
    if (deque_model_.items.empty()) {
        ui->list_widget->setCurrentRow(0); // Выделяем "end"
        ui->txt_elem_content->clear();

    } else {
        int hops = std::distance(deque_model_.items.begin(), deque_model_.iterator);
        ui->list_widget->setCurrentRow(hops);

        if(deque_model_.iterator == deque_model_.items.end()){
            ui->txt_elem_content->clear();
        } else{
            ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
        }
    }

    SetAbleDisableBtn();
}

void MainWindow::SetAbleDisableBtn(){
    bool iterator_end = deque_model_.iterator == deque_model_.items.end();
    bool iterator_begin = deque_model_.iterator == deque_model_.items.begin();
    bool deque_is_empty = deque_model_.items.empty();


    ui->btn_pop_back->setDisabled(deque_is_empty);
    ui->btn_pop_front->setDisabled(deque_is_empty);
    ui->btn_erase->setDisabled(iterator_end);


    ui->btn_dec_iterator->setDisabled(iterator_begin);
    ui->btn_inc_iterator->setDisabled(iterator_end);


    ui->btn_begin->setDisabled(iterator_begin);
    ui->btn_end->setDisabled(iterator_end);


    ui->btn_edit->setDisabled(iterator_end);
}




void MainWindow::on_list_widget_currentRowChanged(int currentRow){
    int current_row = std::clamp(currentRow, 0, (int)deque_model_.items.size());
    int deque_size = static_cast<int>(deque_model_.items.size());


    if (current_row < deque_size) {
        deque_model_.iterator = deque_model_.items.begin() + current_row;

    } else if (current_row == deque_size) {
        deque_model_.iterator = deque_model_.items.end();

    }

    ApplyIterator();
}














