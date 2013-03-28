#include "jsonobjectmodel.h"

#define COLUMN_COUNT 2

JsonObjectModel::JsonObjectModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int JsonObjectModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}

QVariant JsonObjectModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        if(index.column() == 0)
            return jsonPairList.at(index.row()).key;
        else if(index.column() == 1)
            return jsonPairList.at(index.row()).value.toString();
    }

    return QVariant();
}

Qt::ItemFlags JsonObjectModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? Qt::ItemIsEditable : Qt::NoItemFlags;
}

bool JsonObjectModel::insertRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    jsonPairList.insert(row, JsonKeyValuePair());

    return true;
}

bool JsonObjectModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    jsonPairList.removeAt(row);

    return true;
}

int JsonObjectModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return jsonPairList.count();
}

bool JsonObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)

    if(index.isValid())
    {
        JsonKeyValuePair pair = jsonPairList.at(index.row());

        if(index.column() == 0)
            pair.key = value.toString();
        else if(index.column() == 1)
            pair.value = value.toString();

        jsonPairList.replace(index.row(), pair);

        return true;
    }

    return false;
}

void JsonObjectModel::setJsonObject(const QJsonObject &object)
{
    beginResetModel();
    jsonPairList.clear();

    QJsonObject::const_iterator it = object.constBegin();

    while(it != object.end())
    {
        jsonPairList.append(JsonKeyValuePair(it.key(), it.value()));
        it++;
    }

    endResetModel();
}

const QJsonObject JsonObjectModel::toJsonObject() const
{
    QJsonObject object;

    foreach(JsonKeyValuePair pair, jsonPairList)
    {
        object.insert(pair.key, pair.value);
    }

    return object;
}
