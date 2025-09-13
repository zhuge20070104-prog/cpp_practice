#ifndef WINDOW_H
#define WINDOW_H

#include "QtWidgets/QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

public slots:
    void on_ok_clicked();
private:
    Ui::Window *ui;
};
#endif // Window_H
