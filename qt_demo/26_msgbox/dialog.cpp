#include "dialog.h"
#include "./ui_dialog.h"
#include "QtWidgets/QMessageBox"

#include <iostream>
#include <sstream>



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


void Dialog::on_info_clicked() {
    QMessageBox::information(this, "information", "Information box");
}

void Dialog::on_question_clicked() {
    auto reply = QMessageBox::question(this, "Cats", "Do you love cats?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        QMessageBox::information(this, "Cats", "You love cats");
    } else {
        QMessageBox::information(this, "Cats", "You don't love cats");
    }
}

void Dialog::on_warn_clicked() {
    QMessageBox::warning(this, "warning", "Warning box!!");
}

void Dialog::on_custom_clicked() {
    QMessageBox::question(this, "Files", "Do you want to copy this file?",
        QMessageBox::YesToAll | QMessageBox::NoToAll | QMessageBox::Yes | QMessageBox::No);
}   

Dialog::~Dialog()
{
    delete ui;
}

