#ifndef CLOSEDIG_H
#define CLOSEDIG_H

#include "QtWidgets/QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui { class CloseDig; }
QT_END_NAMESPACE

class CloseDig : public QMainWindow
{
    Q_OBJECT

public:
    CloseDig(QWidget *parent = nullptr);
    ~CloseDig();

private:
    Ui::CloseDig *ui;
};
#endif // CLOSEDIG_H
