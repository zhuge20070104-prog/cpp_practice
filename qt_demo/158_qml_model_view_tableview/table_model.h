#ifndef _FREDRIC_TABLE_MODEL_H_
#define _FREDRIC_TABLE_MODEL_H_

#include "QtCore/QAbstractTableModel"

class TableModel: public QAbstractTableModel {
    Q_OBJECT

public:
    TableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};


#endif 