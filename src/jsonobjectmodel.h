#ifndef JSONOBJECTMODEL_H
#define JSONOBJECTMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>

class JsonObjectModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit JsonObjectModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count, const QModelIndex &parent);

    bool removeRows(int row, int count, const QModelIndex &parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void setJsonObject(const QJsonObject& object);

    QJsonObject toJsonObject();
    
private:
    QJsonObject jsonObject;
    
};

#endif // JSONOBJECTMODEL_H
