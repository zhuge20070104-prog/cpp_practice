#include "window.h"
#include "./ui_window.h"
#include <QtWidgets/qmessagebox.h>
#include <list>

int constexpr Size = 10000000;
Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}

// 一个QT的UI应用程序，每个应用程序都有一个主线程，这个主线程用来执行程序
// 并且接受用户的输入，如果有一个耗时任务占用了主线程
// 那么主线程将无法再接受用户的输入

// 在pushButton clicked的回调函数中，调用download函数，会出现什么情况
// 点完pushButton之后，因为卡顿时间太长，pushButton不可再点
void Window::on_ok_clicked() {
    std::list<int> g_data;
    for(int i=0; i<Size; ++i) {
        g_data.push_back(i);
    }
    QMessageBox::about(this, "Message", "Hello there");
}

Window::~Window()
{
    delete ui;
}

