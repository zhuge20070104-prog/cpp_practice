#ifndef _FREDRIC_DIALOG_H_
#define _FREDRIC_DIALOG_H_

#include "QtWidgets/QDialog"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void getValue();

private:
    Ui::Dialog *ui;
};
#endif // CLOSEDIG_H
