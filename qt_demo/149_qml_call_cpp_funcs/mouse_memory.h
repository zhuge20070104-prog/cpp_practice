#ifndef _MOUSE_MEMORY_H_
#define _MOUSE_MEMORY_H_
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtCore/QPoint>
#include <fstream>
#include <QQmlListProperty>
#include <QtCore/QList>

class Point: public QObject {
public:
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)

public:
    Point(int x_, int y_) {
        setX(x_);
        setY(y_);
    }

    int x() {
        return x_val;
    }

    int y() {
        return y_val;
    }

    void setX(int x) {
        x_val = x;
    }

    void setY(int y) {
        y_val = y;
    }
    int x_val;
    int y_val;
};

class MouseMemory: public QObject {
    Q_OBJECT 
public:
    explicit MouseMemory(QObject* parent=0);
    ~MouseMemory();
    Q_INVOKABLE void save();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void add(int x, int y);

    Q_PROPERTY(QVariantList points READ points)
    QVariantList points();

private:
    QVariantList m_points;
};

#endif