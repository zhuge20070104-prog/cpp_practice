#include "mouse_memory.h"
#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>
#include <QQmlContext>
#include <memory>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    std::unique_ptr<MouseMemory> mouse = std::make_unique<MouseMemory>();
    qmlRegisterType<Point>();

    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    engine.rootContext()->setContextProperty("mouses", mouse.get());
    
    return app.exec();
}
