#ifndef _FREDRIC_PIE_SLICE_H_
#define _FREDRIC_PIE_SLICE_H_

#include <QtQuick/QQuickPaintedItem>
#include <QtGui/QColor>

class Pieslice: public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int fromAngle READ fromAngle WRITE setFromAngle)
    Q_PROPERTY(int angleSpan READ angleSpan WRITE setAngleSpan)

public:
    Pieslice(QQuickItem* parent=0);
    QColor color() const;
    void setColor(QColor const& color);

    int fromAngle() const;
    void setFromAngle(int angle);

    int angleSpan() const;
    void setAngleSpan(int span);
    
    void paint(QPainter* painter);
private:
    QColor m_color;
    int m_fromAngle;
    int m_angleSpan;
};

#endif