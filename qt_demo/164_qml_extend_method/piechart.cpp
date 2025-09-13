#include "piechart.h"
#include <QtGui/QPainter>


PieChart::PieChart(QQuickItem* parent): QQuickPaintedItem(parent) {
}

QString PieChart::name() const {
    return m_name;
}

void PieChart::setName(QString const& name) {
    m_name = name;
}

QColor PieChart::color() const {
    return m_color;
}

void PieChart::setColor(QColor const& color) {
    m_color = color;
}

void PieChart::paint(QPainter* painter) {
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90*16, 290*16);
} 

void  PieChart::clearChart() {
    setColor(QColor(Qt::transparent));
    update();
    emit chartCleared();
}