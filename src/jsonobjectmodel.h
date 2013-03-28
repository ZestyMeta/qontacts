#ifndef JSONOBJECTMODEL_H
#define JSONOBJECTMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>

class JsonKeyValuePair
{
public:
    JsonKeyValuePair(QString key = QString(), QJsonValue value = QJsonValue())
    {
        this->key = key;
        this->value = value;
    }

    bool operator ==(const JsonKeyValuePair& other)
    {
        return other.key == key && other.value == value;
    }

    QString key;
    QJsonValue value;
};

class JsonObjectModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit JsonObjectModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void setJsonObject(const QJsonObject& object);

    const QJsonObject toJsonObject() const;
    
private:
    QList<JsonKeyValuePair> jsonPairList;
};

#endif // JSONOBJECTMODEL_H
