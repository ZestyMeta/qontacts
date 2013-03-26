#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "contactlist.h"
#include "ui_contactlist.h"

ContactList::ContactList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactList),
    contactListModel(new QStandardItemModel(this)),
    searchContactListModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    searchContactListModel->setDynamicSortFilter(true);
    searchContactListModel->setSourceModel(contactListModel);

    ui->contactList->setModel(searchContactListModel);

    connect(ui->contactList, &QListView::clicked, this, &ContactList::currentIndexChanged);
}

ContactList::~ContactList()
{
    delete ui;
}

void ContactList::setDocument(QJsonDocument *document)
{
    this->document = document;

    loadContactsDataIntoModel();
}

void ContactList::on_addContact_clicked()
{
    contactListModel->appendRow(QList<QStandardItem*>() << new QStandardItem("First Last"));

    QJsonObject newContact;
    newContact.insert("name", QString("New Contact"));

    QJsonArray array = document->array();
    array.append(newContact);
    document->setArray(array);

    loadContactsDataIntoModel();

    ui->contactList->setCurrentIndex(ui->contactList->model()->index(ui->contactList->model()->rowCount()-1, 0));
    emit currentIndexChanged(ui->contactList->currentIndex());
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

    QJsonArray array = document->array();
    array.removeAt(sourceRow);
    document->setArray(array);

    emit currentIndexChanged(ui->contactList->currentIndex());
}

void ContactList::loadContactsDataIntoModel()
{
    QPersistentModelIndex currentIndex = ui->contactList->currentIndex();

    contactListModel->clear();

    QJsonArray array = document->array();
    QJsonArray::iterator begin = array.begin();

    while(begin != array.end())
    {
        QString name = (*begin).toObject().value("name").toString();

        contactListModel->appendRow(QList<QStandardItem*>() << new QStandardItem(name));
        begin++;
    }

    if(currentIndex.isValid())
        ui->contactList->setCurrentIndex(currentIndex);
}
