#include "closedig.h"
#include "./ui_closedig.h"

CloseDig::CloseDig(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CloseDig)
{
    ui->setupUi(this);
}

CloseDig::~CloseDig()
{
    delete ui;
}

