#include <QMessageBox>

#include "contactlist.h"
#include "ui_contactlist.h"

ContactList::ContactList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactList),
    contactListModel(0),
    searchContactListModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    searchContactListModel->setDynamicSortFilter(true);

    ui->contactList->setModel(searchContactListModel);

    connect(ui->pushButton, &QPushButton::clicked, this, &ContactList::saveData);
}

ContactList::~ContactList()
{
    delete ui;
}

void ContactList::setModel(QStandardItemModel *model)
{
    contactListModel = model;
    searchContactListModel->setSourceModel(contactListModel);
}

void ContactList::on_addContact_clicked()
{
    contactListModel->appendRow(QList<QStandardItem*>() << new QStandardItem(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), "First Last"));

}

void ContactList::on_searchLine_textEdited(const QString &arg1)
{
    searchContactListModel->setFilterRegExp("^.*" + arg1 + ".*$");
}

void ContactList::on_removeContact_clicked()
{
    if(!ui->contactList->currentIndex().isValid() ||
            QMessageBox::Cancel == QMessageBox::warning(this, "Confirm contact deletion", "This will delete the contact. You cool with that?", QMessageBox::Ok, QMessageBox::Cancel))
        return;

    int sourceRow = searchContactListModel->mapToSource(ui->contactList->currentIndex()).row();
    contactListModel->removeRow(sourceRow);
}

void ContactList::on_contactList_clicked(const QModelIndex &index)
{
    emit patientSelected(index.data().toString());
}
