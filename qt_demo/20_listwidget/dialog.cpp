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
    init_items();
}


void Dialog::init_items() {
    ui->listbox->clear();
    for(auto song: songs) {
        ui->listbox->addItem(QString(song.data()));
    }
}


void Dialog::on_ok_clicked() {
    auto current_item = ui->listbox->currentItem();
    std::stringstream ss;
    ss << "I love the song: " << current_item->text().toStdString();
    current_item->setText(QString(ss.str().data()));
    current_item->setTextColor(Qt::red);
    current_item->setBackgroundColor(Qt::black);
}

void Dialog::on_clear_clicked() {
    init_items();
}


Dialog::~Dialog()
{
    delete ui;
}

