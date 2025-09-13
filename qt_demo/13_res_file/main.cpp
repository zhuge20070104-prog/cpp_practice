#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>

void Read(QString const& file_name) {
    // Resource files can only work with QFile
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Could not open file: " << file_name.toStdString() << " for read...";
        return;
    }

    QTextStream in(&file);
    auto text = in.readAll();
    std::cout << text.toStdString();
    file.close();
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QString hello_res = ":/hello_file/conanfile.txt";
    Read(hello_res);
    app.exec();
}