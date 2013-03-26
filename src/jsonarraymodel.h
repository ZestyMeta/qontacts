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

    void setJsonArray(const QJsonArray& array);

    void setJsonObjectKey(const QString& key);

signals:
    
public slots:

private:
    QJsonArray array;
    QString key;
};

#endif // JSONARRAYMODEL_H
