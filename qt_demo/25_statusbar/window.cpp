#include "window.h"
#include "./ui_window.h"
#include "QtWidgets/QMessageBox"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    stat_lab = new QLabel(this);
    stat_prog = new QProgressBar(this);
    stat_lab->setText("Hello");
    stat_prog->setTextVisible(false);
    ui->statusbar->addPermanentWidget(stat_lab, 0);
    ui->statusbar->addPermanentWidget(stat_prog, 1);
}


void Window::on_do_sth_triggered() {
    stat_lab->setText("Do something!!");
    stat_prog->setValue(45);
}

Window::~Window()
{
    delete ui;
}

