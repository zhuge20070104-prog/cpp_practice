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

    ui->tv->setColumnCount(2);
    ui->tv->setHeaderLabels(QStringList() << "one" << "two");
    add_root("1 hello", "world");
    add_root("2 hello", "world");
    add_root("3 hello", "world");
}


void Dialog::add_root(QString const& name, QString const& description) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->tv);
    item->setText(0, name);
    item->setText(1, description);
    ui->tv->addTopLevelItem(item);

    add_child(item, "one", "hello");
    add_child(item, "two", "world");
}

void Dialog::add_child(QTreeWidgetItem* parent, QString const& name, QString const& description) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, description);
    parent->addChild(item);
}

void Dialog::on_click_me_clicked() {
    ui->tv->currentItem()->setBackgroundColor(0, Qt::red);
    ui->tv->currentItem()->setBackgroundColor(1, Qt::blue);
}


Dialog::~Dialog()
{
    delete ui;
}

