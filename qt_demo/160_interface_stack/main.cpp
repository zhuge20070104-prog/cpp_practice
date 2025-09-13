#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    
    return app.exec();
}
