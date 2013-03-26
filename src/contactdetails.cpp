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
    m_rowIndex = index.row();

    loadDetailsFromDocument();

    ui->stackedWidget->setCurrentWidget(ui->readOnlyPage);
}

void ContactDetails::on_saveBtn_clicked()
{
    writeDetailsToDocument();

    loadDetailsFromDocument();

    ui->stackedWidget->setCurrentWidget(ui->readOnlyPage);

    emit saveContactDetails();
}

void ContactDetails::on_editBtn_clicked()
{
    // set values
    ui->stackedWidget->setCurrentWidget(ui->editablePage);
}

void ContactDetails::loadDetailsFromDocument()
{
    if(!document->array().at(m_rowIndex).isObject())
    {
        //qDebug() << "error! Item at rowIndex" << m_rowIndex << "is not an object!";
        return;
    }

    QJsonObject object = document->array().at(m_rowIndex).toObject();

    ui->nameLbl->setText(object.value("name").toString());

    QJsonArray array;
    if(!object.contains("details"))
    {
        object.insert("details", array);
    }

    array = object.value("details").toArray();

    QJsonArray::iterator begin = array.begin();

    while(begin != array.end())
    {
        QJsonObject object = (*begin).toObject();

        QJsonObject::iterator detailIt = object.find("group");

        if(QJsonValue(*detailIt).toString() == "home")
        {
            detailIt = object.find("phone");
            if(detailIt != object.end())
                ui->homephone->setText(QJsonValue(*detailIt).toString());

            detailIt = object.find("address");
            if(detailIt != object.end())
                ui->homeaddress->setText(QJsonValue(*detailIt).toString());

            detailIt = object.find("email");
            if(detailIt != object.end())
                ui->homeemail->setText(QJsonValue(*detailIt).toString());
        }
        else if(QJsonValue(*detailIt).toString() == "group")
        {
            detailIt = object.find("phone");
            if(detailIt != object.end())
                ui->workphone->setText(QJsonValue(*detailIt).toString());

            detailIt = object.find("address");
            if(detailIt != object.end())
                ui->workaddress->setText(QJsonValue(*detailIt).toString());

            detailIt = object.find("email");
            if(detailIt != object.end())
                ui->workemail->setText(QJsonValue(*detailIt).toString());
        }

       begin++;
    }
}

void ContactDetails::writeDetailsToDocument()
{
    QJsonArray array;

    QJsonObject homeObject;
    homeObject.insert("group", QJsonValue(QString("home")));
    homeObject.insert("phone", QJsonValue(ui->home_phone->text()));
    homeObject.insert("email", QJsonValue(ui->home_email->text()));
    homeObject.insert("address", QJsonValue(ui->home_address->text()));

    array.append(homeObject);

    QJsonObject workObject;
    workObject.insert("group", QJsonValue(QString("work")));
    workObject.insert("phone", QJsonValue(ui->work_phone->text()));
    workObject.insert("email", QJsonValue(ui->work_email->text()));
    workObject.insert("address", QJsonValue(ui->work_address->text()));

    array.append(workObject);

    QJsonObject contactObject;
    contactObject.insert("name", ui->nameLineEdit->text());
    contactObject.insert("details", array);

    QJsonArray currentArray = document->array();
    currentArray.replace(m_rowIndex, contactObject);

    document->setArray(currentArray);
}
