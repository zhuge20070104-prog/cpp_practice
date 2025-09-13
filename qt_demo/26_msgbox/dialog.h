#ifndef _FREDRIC_DIALOG_H_
#define _FREDRIC_DIALOG_H_

#include "QtWidgets/QDialog"
#include <vector>
#include <string>


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
    void on_info_clicked();
    void on_question_clicked();
    void on_warn_clicked();
    void on_custom_clicked();
private:
    Ui::Dialog *ui;

};
#endif // CLOSEDIG_H
