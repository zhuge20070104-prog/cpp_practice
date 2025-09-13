#include "dialog.h"
#include "./ui_dialog.h"
#include "QtWidgets/QMessageBox"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}


void Dialog::on_button_clicked() {
    QMessageBox::information(this, "Dialog", "Happy today!");
}

Dialog::~Dialog()
{
    delete ui;
}

