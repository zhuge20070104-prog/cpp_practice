#include "table_model.h"

TableModel::TableModel(): QAbstractTableModel() {

}


int TableModel::rowCount(const QModelIndex &parent) const {
    return 10;
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 10;
}

QVariant TableModel::data(const QModelIndex &index, int role) const  {
    if(role == Qt::DisplayRole) {
        return QString("%1, %2").arg(index.row()).arg(index.column());
    } else {
        return QVariant();
    }
}