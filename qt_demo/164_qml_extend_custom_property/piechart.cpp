#include "piechart.h"
#include <QtGui/QPainter>


PieChart::PieChart(QQuickItem* parent): QQuickItem(parent), m_pieSlice(nullptr) {
}

QString PieChart::name() const {
    return m_name;
}

void PieChart::setName(QString const& name) {
    m_name = name;
}

Pieslice* PieChart::pieSlice() const {
    return m_pieSlice;
}

void PieChart::setPieSlice(Pieslice* pieSlice) {
    m_pieSlice = pieSlice;
    pieSlice->setParentItem(this);
}
