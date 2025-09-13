#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    const QUrl url(QStringLiteral("qrc:/ws_client.qml"));
    engine.load(url);
    
    return app.exec();
}
