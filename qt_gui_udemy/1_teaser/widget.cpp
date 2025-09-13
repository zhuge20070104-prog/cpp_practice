#include "widget.h"
#include "./ui_widget.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <sstream>

namespace fs = boost::filesystem;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_submit_btn_clicked()
{
    std::stringstream files_ss;
    fs::path p_(".\\");
    fs::directory_iterator it(p_);
    for(auto const& d: it) {
        files_ss << d.path().string() << std::endl;
    }
    ui->first_name_txt->setText("Fredric");
    ui->last_name_txt->setText("Zhu");
    ui->textEdit->setPlainText(files_ss.str().data());

    std::cout << ui->first_name_txt->text().toStdString() << std::endl;
    std::cout << ui->last_name_txt->text().toStdString() << std::endl;
    std::cout << ui->textEdit->toPlainText().toStdString() << std::endl;
}

