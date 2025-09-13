#include "window.h"
#include "./ui_window.h"
#include "QtWidgets/QMessageBox"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}


void Window::on_actionOpen_triggered() {
    QMessageBox::information(this, "Open", "Open File");
}

Window::~Window()
{
    delete ui;
}

