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

void Pieslice::paint(QPainter* painter) {
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}