#ifndef _FREDRIC_PIE_CHART_H_
#define _FREDRIC_PIE_CHART_H_

#include <QtQuick/QQuickPaintedItem>
#include  <QtGui/QColor>
#include "pieslice.h"


class PieChart: public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(Pieslice* pieSlice READ pieSlice WRITE setPieSlice)
    Q_PROPERTY(QString name READ name WRITE setName)
   

public:
    PieChart(QQuickItem* parent=0);
    QString name() const;
    void setName(QString const& name);

    Pieslice* pieSlice() const;
    void setPieSlice(Pieslice* pieSlice);

private:
    Pieslice* m_pieSlice;
    QString m_name;
};  


#endif