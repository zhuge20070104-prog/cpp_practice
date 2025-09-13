#ifndef CLOSEDIG_H
#define CLOSEDIG_H

#include "QtWidgets/QMainWindow"
#include "QtWidgets/QAction"
#include "dialog.h"

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
    void showDialog(bool act);

private:
    Ui::Window *ui;
    Dialog* dlg;

};
#endif // CLOSEDIG_H
