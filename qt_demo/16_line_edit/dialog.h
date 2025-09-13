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

private slots:
    void on_button_clicked();
    void on_edit1_textChanged(QString const& text);

private:
    Ui::Dialog *ui;
};
#endif // CLOSEDIG_H
