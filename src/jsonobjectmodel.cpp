#include "jsonobjectmodel.h"

JsonObjectModel::JsonObjectModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int JsonObjectModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant JsonObjectModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

bool JsonObjectModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool JsonObjectModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

int JsonObjectModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

bool JsonObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

void JsonObjectModel::setJsonObject(const QJsonObject &object)
{
    jsonObject = object;
}

QJsonObject JsonObjectModel::toJsonObject()
{
    return QJsonObject();
}
