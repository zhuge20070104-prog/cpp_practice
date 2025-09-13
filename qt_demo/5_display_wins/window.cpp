#include "window.h"
#include "./ui_window.h"
#include "QtCore/QDebug"
#include <iostream>
#include "dialog.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->actionNew_Window, SIGNAL(triggered(bool)), this, SLOT(showDialog(bool)));
    setCentralWidget(ui->textEdit);
}


void Window::showDialog(bool act) {
   Dialog dlg;
   dlg.setModal(true);
   dlg.exec();
}

Window::~Window()
{
    delete ui;
}

