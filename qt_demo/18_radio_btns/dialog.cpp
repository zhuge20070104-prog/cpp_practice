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


void Dialog::on_ok_clicked() {
    auto animals = ui->animal->children();
    auto colors = ui->color->children();

    std::stringstream ss;
    ss << "You love ";
    for(auto& animal: animals) {
        auto animal_btn = dynamic_cast<QRadioButton*>(animal);
        if(animal_btn && animal_btn->isChecked()) {
            ss << animal_btn->text().toStdString() << " ";
        }
    }

    for(auto& color: colors) {
        auto color_btn = dynamic_cast<QRadioButton*>(color);
        if(color_btn && color_btn->isChecked()) {
            ss << color_btn->text().toStdString();
        }
    }

    QMessageBox::information(this, "Ops", QString(ss.str().data()));
}


Dialog::~Dialog()
{
    delete ui;
}

