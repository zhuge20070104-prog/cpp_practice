#include "piechart.h"
#include <QtGui/QPainter>


PieChart::PieChart(QQuickItem* parent): QQuickItem(parent) {
}

QString PieChart::name() const {
    return m_name;
}

void PieChart::setName(QString const& name) {
    m_name = name;
}

QQmlListProperty<Pieslice>  PieChart::slices() {
    return QQmlListProperty<Pieslice>(this, nullptr, &PieChart::append_slice, nullptr, nullptr, nullptr);
}


void PieChart::append_slice(QQmlListProperty<Pieslice>* list, Pieslice* slice) {
    PieChart* chart = qobject_cast<PieChart*>(list->object);
    if(chart) {
        slice->setParentItem(chart);
        chart->m_slices.append(slice);
    }
}

