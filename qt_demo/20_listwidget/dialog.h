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

private slots:
    void on_ok_clicked();
    void on_clear_clicked();

private:
    Ui::Dialog *ui;

    void init_items();
    std::vector<std::string> songs{"I hate my self for loving you", 
        "Do something",
        "Poke face",
        "Papa razza",
        "Ops, I did it again"};
};
#endif // CLOSEDIG_H
