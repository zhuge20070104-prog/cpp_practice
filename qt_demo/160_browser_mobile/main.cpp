#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlDebuggingEnabler>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    
    return app.exec();
}
