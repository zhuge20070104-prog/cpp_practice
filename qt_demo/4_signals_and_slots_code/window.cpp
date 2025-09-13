#include "window.h"
#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->hs, SIGNAL(valueChanged(int)), ui->pb, SLOT(setValue(int)));
    connect(ui->hs, SIGNAL(valueChanged(int)), ui->pb1, SLOT(setValue(int)));
    disconnect(ui->hs, SIGNAL(valueChanged(int)), ui->pb, SLOT(setValue(int)));
}

Window::~Window()
{
    delete ui;
}

