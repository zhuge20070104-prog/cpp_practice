#include "dialog.h"
#include "./ui_dialog.h"
#include "QtWidgets/QMessageBox"
#include <iostream>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


void Dialog::on_button_clicked() {
    QMessageBox::information(this, "Message", ui->edit1->text());
}

void Dialog::on_edit1_textChanged(QString const& text) {
    std::cout << text.toStdString() << std::endl;
    ui->edit2->setText(ui->edit1->text());
}

Dialog::~Dialog()
{
    delete ui;
}

