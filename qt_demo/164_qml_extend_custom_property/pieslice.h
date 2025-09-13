#ifndef _FREDRIC_PIE_SLICE_H_
#define _FREDRIC_PIE_SLICE_H_

#include <QtQuick/QQuickPaintedItem>
#include <QtGui/QColor>

class Pieslice: public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    Pieslice(QQuickItem* parent=0);
    QColor color() const;
    void setColor(QColor const& color);
    void paint(QPainter* painter);
private:
    QColor m_color;
};

#endif