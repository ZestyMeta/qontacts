#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "contactlist.h"
#include "ui_contactlist.h"

ContactList::ContactList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactList),
    contactListModel(new JsonArrayModel(this)),
    searchContactListModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    searchContactListModel->setDynamicSortFilter(true);
    searchContactListModel->setSourceModel(contactListModel);

    ui->contactList->setModel(searchContactListModel);

    contactListModel->setJsonObjectKey("name");

    connect(ui->contactList, &QListView::clicked, this, &ContactList::currentIndexChanged);
}

ContactList::~ContactList()
{
    delete ui;
}

void ContactList::setDocument(QJsonDocument *document)
{
    this->document = document;

    contactListModel->setJsonArray(document->array());
}

void ContactList::on_addContact_clicked()
{
    contactListModel->insertRow(contactListModel->rowCount());
    contactListModel->setData(contactListModel->index(contactListModel->rowCount()-1), "New Contact");

    document->setArray(contactListModel->toArray());

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

    contactListModel->setJsonArray(document->array());

    if(currentIndex.isValid())
        ui->contactList->setCurrentIndex(currentIndex);
}
