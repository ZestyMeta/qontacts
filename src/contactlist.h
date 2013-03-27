#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QWidget>
#include <QSortFilterProxyModel>

#include "jsonarraymodel.h"

namespace Ui {
class ContactList;
}

class ContactList : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContactList(QWidget *parent = 0);
    ~ContactList();

    void setDocument(QJsonDocument* document);

public slots:
    void loadContactsDataIntoModel();

signals:
    void currentIndexChanged(const QModelIndex& index);

private slots:
    void on_addContact_clicked();

    void on_removeContact_clicked();

    void on_searchLine_textEdited(const QString &arg1);

private:
    Ui::ContactList *ui;
    JsonArrayModel* contactListModel;
    QSortFilterProxyModel* searchContactListModel;
    QJsonDocument* document;
};

#endif // CONTACTLIST_H
