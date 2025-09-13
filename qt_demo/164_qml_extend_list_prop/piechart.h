#ifndef _FREDRIC_PIE_CHART_H_
#define _FREDRIC_PIE_CHART_H_

#include <QtQuick/QQuickPaintedItem>
#include  <QtGui/QColor>
#include "pieslice.h"


class PieChart: public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Pieslice> slices READ slices)
    Q_PROPERTY(QString name READ name WRITE setName)
   

public:
    PieChart(QQuickItem* parent=0);
    QString name() const;
    void setName(QString const& name);

    QQmlListProperty<Pieslice> slices();

private:
    static void append_slice(QQmlListProperty<Pieslice>* list, Pieslice* slice);
    QList<Pieslice*> m_slices;
    QString m_name;
};  


#endif