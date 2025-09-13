#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlDebuggingEnabler>
#include <QtQuick/QQuickView>
#include "piechart.h"

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);
    qmlRegisterType<PieChart>("Charts",  1, 0, "PieChart");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
