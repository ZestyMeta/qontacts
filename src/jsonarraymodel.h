#ifndef JSONARRAYMODEL_H
#define JSONARRAYMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>

class JsonArrayModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JsonArrayModel(QObject *parent = 0);
        
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count, const QModelIndex &parent);

    bool removeRows(int row, int count, const QModelIndex &parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void setJsonArray(const QJsonArray& array);

    void setJsonObjectKey(const QString& key);

    const QJsonArray toArray() const;

private:
    QJsonArray jsonArray;
    QString jsonObjectKey;
};

#endif // JSONARRAYMODEL_H
