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

    for(auto song: songs) {
        ui->combo->addItem(QString(song.data()));
    }
}


void Dialog::on_ok_clicked() {
    QMessageBox::information(this, "Your favorite song", ui->combo->currentText());
}


Dialog::~Dialog()
{
    delete ui;
}

