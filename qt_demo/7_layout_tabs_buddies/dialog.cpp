#include "dialog.h"
#include <iostream>
#include "./ui_dialog.h"



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(getValue()));
}



void Dialog::getValue() {
    std::cout << "Name: " << ui->nameEdit->text().toStdString() << std::endl; 
}

Dialog::~Dialog()
{
    delete ui;
}

