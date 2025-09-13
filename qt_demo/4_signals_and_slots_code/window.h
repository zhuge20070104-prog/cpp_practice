#ifndef CLOSEDIG_H
#define CLOSEDIG_H

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

private:
    Ui::Window *ui;
};
#endif // CLOSEDIG_H
