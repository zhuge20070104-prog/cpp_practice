#include "dialog.h"
#include "./ui_dialog.h"
#include "QtWidgets/QMessageBox"
#include "QtCore/QStringList"

#include <iostream>
#include <sstream>



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->pbar->setValue(ui->slider->value());
    ui->pbar->setTextVisible(false);
    connect(ui->slider, SIGNAL(valueChanged(int)), ui->pbar, SLOT(setValue(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

