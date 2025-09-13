#include "dialog.h"
#include "./ui_dialog.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label2->setText("<b>Hello</b> World"); // HTML awared control
}



Dialog::~Dialog()
{
    delete ui;
}

