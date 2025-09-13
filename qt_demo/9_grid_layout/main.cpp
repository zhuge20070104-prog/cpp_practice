#include "QtWidgets/QApplication"
#include "QtWidgets/QPushButton"
#include "QtWidgets/QGridLayout"
#include "QtWidgets/QLabel"
#include "QtWidgets/QLineEdit"
#include <memory>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    std::shared_ptr<QWidget> window = std::make_shared<QWidget>();
    window->setWindowTitle("My App");

    auto glayout = new QGridLayout();
    
    QLabel* name = new QLabel("Name:");
    QLineEdit* nameEdit = new QLineEdit();

    QLabel* sex = new QLabel("Sex:");
    QLineEdit* sexEdit = new QLineEdit();

    glayout->addWidget(name, 0, 0);
    glayout->addWidget(nameEdit, 0, 1);

    glayout->addWidget(sex, 1, 0);
    glayout->addWidget(sexEdit, 1, 1);

    QPushButton* ok = new QPushButton("OK");
    glayout->addWidget(ok, 2, 0, 1, 2);
    
    window->setLayout(glayout);
    window->show();     
    return app.exec();  
}