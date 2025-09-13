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


void Dialog::on_ok_clicked() {
    if(ui->checkBox->isChecked()) {
        QMessageBox::information(this, "Ops", "You love cats");
    } else {
        QMessageBox::information(this, "Ops", "You don't love cats");
    }
}


Dialog::~Dialog()
{
    delete ui;
}

