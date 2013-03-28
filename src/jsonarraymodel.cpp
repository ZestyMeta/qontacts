#include <QJsonObject>

#include "jsonarraymodel.h"

JsonArrayModel::JsonArrayModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QVariant JsonArrayModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        return jsonArray.at(index.row()).toObject().value(jsonObjectKey).toString();
    }

    return QVariant();
}

bool JsonArrayModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    jsonArray.insert(row, QJsonValue());
    endInsertRows();

    return false;
}

bool JsonArrayModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    jsonArray.removeAt(row);
    endRemoveRows();

    return false;
}

int JsonArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return jsonArray.count();
}

bool JsonArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)

    if(index.isValid())
    {
        QJsonObject object = jsonArray.at(index.row()).toObject();
        object.insert(jsonObjectKey, QJsonValue(value.toString()));

        jsonArray.replace(index.row(), object);

        return true;
    }

    return false;
}

void JsonArrayModel::setJsonArray(const QJsonArray &array)
{
    beginResetModel();
    jsonArray = array;
    endResetModel();
}

void JsonArrayModel::setJsonObjectKey(const QString &key)
{    
    beginResetModel();
    jsonObjectKey = key;
    endResetModel();
}

const QJsonArray JsonArrayModel::toArray() const
{
    return jsonArray;
}
