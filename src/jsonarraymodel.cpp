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
    array.insert(row, QJsonValue());
    endInsertRows();

    return false;
}

bool JsonArrayModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    array.removeAt(row);
    endRemoveRows();

    return false;
}

int JsonArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return array.count();
}

bool JsonArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)


    if(index.isValid())
    {
        QJsonObject object = array.at(index.row()).toObject();
        object.insert(key, QJsonValue(value.toString()));

        array.replace(index.row(), object);

        return true;
    }

    return false;
}

void JsonArrayModel::setJsonArray(const QJsonArray &array)
{
    this->array = array;
}

void JsonArrayModel::setJsonObjectKey(const QString &key)
{
    this->key = key;
}

QJsonArray JsonArrayModel::toArray()
{
    return array;
}
