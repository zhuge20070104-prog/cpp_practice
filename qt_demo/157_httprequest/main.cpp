#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>
#include <memory>
#include "my_namf.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);

    std::shared_ptr<MyNAMFactory> namf(new MyNAMFactory());
    QQmlApplicationEngine engine;
    engine.setNetworkAccessManagerFactory(namf.get());
    
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    
    return app.exec();
}
