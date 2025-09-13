#ifndef _FREDRIC_PIE_CHART_H_
#define _FREDRIC_PIE_CHART_H_

#include <QtQuick/QQuickPaintedItem>
#include  <QtGui/QColor>

class PieChart: public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    PieChart(QQuickItem* parent=0);
    QString name() const;
    void setName(QString const& name);

    QColor color() const;
    void setColor(QColor const& color);

    void paint(QPainter* painter); 

    Q_INVOKABLE void clearChart();
signals:
    void chartCleared();

private:
    QString m_name;
    QColor m_color;
};  


#endif