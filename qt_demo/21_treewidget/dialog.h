#ifndef _FREDRIC_DIALOG_H_
#define _FREDRIC_DIALOG_H_

#include "QtWidgets/QDialog"
#include <vector>
#include <string>
#include "QtWidgets/QTreeWidgetItem"
#include "QtWidgets/QTreeWidget"


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
    void on_click_me_clicked();
private:
    void add_root(QString const& name, QString const& description);
    void add_child(QTreeWidgetItem* parent, QString const& name, QString const& description);
    Ui::Dialog *ui;

};
#endif // CLOSEDIG_H
