#ifndef CLOSEDIG_H
#define CLOSEDIG_H

#include "QtWidgets/QMainWindow"
#include "QtWidgets/QLabel"
#include "QtWidgets/QProgressBar"

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
    void on_do_sth_triggered();
private:
    QLabel* stat_lab;
    QProgressBar* stat_prog;
    Ui::Window *ui;
};
#endif // CLOSEDIG_H
