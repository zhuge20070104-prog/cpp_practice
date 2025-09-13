#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>
#include <QQmlContext>
#include <memory>

#include "table_model.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);
    std::shared_ptr<TableModel> tableModel(new TableModel());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("tableModel", tableModel.get());
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    
    return app.exec();
}
