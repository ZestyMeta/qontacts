#include <QLabel>

#include "contactdetailgroupbox.h"
#include "ui_contactdetailgroupbox.h"

ContactDetailGroupBox::ContactDetailGroupBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactDetailGroupBox),
    model(new JsonObjectModel(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->editPage);
    ui->tableView->setModel(model);
}

ContactDetailGroupBox::~ContactDetailGroupBox()
{
    delete ui;
}

void ContactDetailGroupBox::setJsonObject(const QJsonObject &object)
{
    ui->groupNameEdit->setText(object.value("group").toString());

    model->setJsonObject(object.value("fields").toObject());

    on_stackedWidget_currentChanged(ui->stackedWidget->indexOf(ui->readPage));
}

QJsonObject ContactDetailGroupBox::toJsonObject()
{
    QJsonObject groupFields;

    for(int rowIndex = 0; rowIndex < model->rowCount(); rowIndex++)
    {
        QVariant keyData = model->index(rowIndex, 0).data(Qt::EditRole);
        QVariant valueData = model->index(rowIndex, 1).data();

        if(!keyData.isNull() && !valueData.isNull())
        {
            groupFields.insert(keyData.toString(), valueData.toString());
        }
    }

    QJsonObject groupDetails;

    if(!ui->groupNameEdit->text().isEmpty() && !groupFields.isEmpty())
    {
        groupDetails.insert("group", ui->groupNameEdit->text());
        groupDetails.insert("fields", groupFields);
    }

    return groupDetails;
}

void ContactDetailGroupBox::setToReadMode(bool readMode)
{
    ui->stackedWidget->setCurrentWidget(readMode ? ui->readPage : ui->editPage);
}

void ContactDetailGroupBox::on_stackedWidget_currentChanged(int index)
{
    if(index == ui->stackedWidget->indexOf(ui->readPage))
    {
        ui->readGroupBox->setTitle(ui->groupNameEdit->text());

        QFormLayout* formLayout = qobject_cast<QFormLayout*>(ui->readGroupBox->layout());

        while(QLayoutItem* item = formLayout->itemAt(0))
        {
            formLayout->removeItem(item);
            delete item;
        }

        for(int row = 0; row < model->rowCount(); row++)
        {
            formLayout->addRow(new QLabel(model->index(row, 0).data().toString()), new QLabel(model->index(row, 1).data().toString()));
        }
    }
}

void ContactDetailGroupBox::on_addDetailBtn_clicked()
{
    model->insertRow(model->rowCount());
}
