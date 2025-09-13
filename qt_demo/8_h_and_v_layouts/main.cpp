#include "QtWidgets/QApplication"
#include "QtWidgets/QPushButton"
#include "QtWidgets/QHBoxLayout"
#include "QtWidgets/QVBoxLayout"
#include <memory>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    std::shared_ptr<QWidget> window = std::make_shared<QWidget>();
    window->setWindowTitle("My App");
    auto btn1 = new QPushButton("one");
    auto btn2 = new QPushButton("two");
    auto btn3 = new QPushButton("three");

    // auto hlayout = new QHBoxLayout(); 
    // hlayout->addWidget(btn1);  
    // hlayout->addWidget(btn2);
    // hlayout->addWidget(btn3);

    auto vlayout = new QVBoxLayout();
    vlayout->addWidget(btn1);  
    vlayout->addWidget(btn2);
    vlayout->addWidget(btn3);

    window->setLayout(vlayout);
    window->show();     
    return app.exec();  
}