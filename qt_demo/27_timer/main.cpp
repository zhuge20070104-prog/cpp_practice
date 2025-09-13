#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include "my_timer.h"
#include <thread>
#include <chrono>


int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    MyTimer my_timer;
	Poco::Timer timer(250, 1000);
	timer.start(Poco::TimerCallback<MyTimer>(my_timer, &MyTimer::onTimer));

    app.exec();
}