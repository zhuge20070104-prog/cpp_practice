#include "pieslice.h"
#include <QtGui/QPainter>

Pieslice::Pieslice(QQuickItem* parent): QQuickPaintedItem(parent) {

}

QColor Pieslice::color() const {
    return m_color;
}

void Pieslice::setColor(QColor const& color) {
    m_color = color;
}

int Pieslice::fromAngle() const {
    return m_fromAngle;
}

void Pieslice::setFromAngle(int angle) {
    m_fromAngle = angle;
}

int Pieslice::angleSpan() const {
    return m_angleSpan;
}

void Pieslice::setAngleSpan(int span) {
    m_angleSpan = span;
}

void Pieslice::paint(QPainter* painter) {
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), m_fromAngle * 16, m_angleSpan * 16);
}