#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "contactdetails.h"
#include "ui_contactdetails.h"

ContactDetails::ContactDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactDetails)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->emptyPage);
}

ContactDetails::~ContactDetails()
{
    delete ui;
}

void ContactDetails::setDocument(QJsonDocument *document)
{
    this->document = document;
}

void ContactDetails::onPatientClicked(const QModelIndex& index)
{
    rowIndex = index.row();

    loadDetailsFromDocument();

    ui->stackedWidget->setCurrentWidget(ui->populatedPage);
    setReadMode(true);
}

void ContactDetails::on_saveBtn_clicked()
{
    writeDetailsToDocument();

    emit saveContactDetails();

    setReadMode(true);
}

void ContactDetails::on_editBtn_clicked()
{
    setReadMode(false);
}

void ContactDetails::loadDetailsFromDocument()
{
    if(!document->array().at(rowIndex).isObject())
    {
        //qDebug() << "error! Item at rowIndex" << m_rowIndex << "is not an object!";
        return;
    }

    QJsonObject object = document->array().at(rowIndex).toObject();

    ui->nameLbl->setText(object.value("name").toString());
    ui->nameLineEdit->setText(object.value("name").toString());

    while(QLayoutItem* item = ui->detailGroupLayout->itemAt(0))
    {
        ui->detailGroupLayout->removeItem(item);
        delete item;
    }

    if(object.contains("detailGroups"))
    {
        QJsonArray array = object.value("detailGroups").toArray();

        QJsonArray::const_iterator begin = array.constBegin();

        while(begin != array.end())
        {
            on_addGroupBtn_clicked();

            contactDetailList.last()->setJsonObject((*begin).toObject());

            begin++;
        }
    }    
}

void ContactDetails::writeDetailsToDocument()
{
    QJsonArray detailGroupArray;

    foreach(ContactDetailGroupBox* detailGroup, contactDetailList)
    {
        if(!detailGroup->toJsonObject().isEmpty())
            detailGroupArray.append(detailGroup->toJsonObject());
    }

    QJsonObject contactObject;
    contactObject.insert("name", ui->nameLineEdit->text());
    contactObject.insert("detailGroups", detailGroupArray);

    QJsonArray currentArray = document->array();
    currentArray.replace(rowIndex, contactObject);

    document->setArray(currentArray);
}

void ContactDetails::setReadMode(bool readMode)
{
    ui->editBtn->setVisible(readMode);
    ui->nameLbl->setVisible(readMode);

    ui->saveBtn->setVisible(!readMode);
    ui->nameLineEdit->setVisible(!readMode);
    ui->addGroupBtn->setVisible(!readMode);

    foreach(ContactDetailGroupBox* wgt, contactDetailList)
    {
        wgt->setToReadMode(readMode);
    }
}

void ContactDetails::on_addGroupBtn_clicked()
{
    contactDetailList.append(new ContactDetailGroupBox);
    ui->detailGroupLayout->addWidget(contactDetailList.last());
}
