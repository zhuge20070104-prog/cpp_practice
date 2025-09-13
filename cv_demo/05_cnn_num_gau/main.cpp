#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlDebuggingEnabler>
#include "cv_image_item.h"

int main(int argc, char *argv[])
{
    QQmlDebuggingEnabler enabler;
    qmlRegisterType<CVImageItem>("cvimages", 1, 0, "CVImageItem");
    qRegisterMetaType<cv::Mat_<float>>("cv::Mat_<float>");
     qRegisterMetaType<cv::Mat>("cv::Mat");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    
    return app.exec();
}
