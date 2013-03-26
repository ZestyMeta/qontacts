#include <QJsonObject>

#include "jsonarraymodel.h"

JsonArrayModel::JsonArrayModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QVariant JsonArrayModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    return array.at(index.row()).toObject().value(key).toString();
}

bool JsonArrayModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    endInsertRows();

    return false;
}

bool JsonArrayModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    endRemoveRows();

    return false;
}

int JsonArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return array.count();
}

void JsonArrayModel::setJsonArray(const QJsonArray &array)
{
    this->array = array;
}

void JsonArrayModel::setJsonObjectKey(const QString &key)
{
    this->key = key;
}
