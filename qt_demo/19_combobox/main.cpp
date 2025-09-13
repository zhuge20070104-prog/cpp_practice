#include "dialog.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dlg;
    dlg.show();
    return a.exec();
}
