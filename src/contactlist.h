#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class ContactList;
}

class ContactList : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContactList(QWidget *parent = 0);
    ~ContactList();

    void setModel(QStandardItemModel* model);

private slots:
    void on_addContact_clicked();
    void on_removeContact_clicked();

    void on_searchLine_textEdited(const QString &arg1);

private:
    Ui::ContactList *ui;
    QStandardItemModel* contactListModel;
    QSortFilterProxyModel* searchContactListModel;
};

#endif // CONTACTLIST_H
