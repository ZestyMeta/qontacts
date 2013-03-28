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
    ui->readGroupBox->setTitle("");
}

ContactDetailGroupBox::~ContactDetailGroupBox()
{
    delete ui;
}

void ContactDetailGroupBox::setJsonObject(const QJsonObject &object)
{
    ui->groupNameEdit->setText(object.value("group").toString());

    model->setJsonObject(object.value("details").toObject());

    on_stackedWidget_currentChanged(ui->stackedWidget->indexOf(ui->readPage));
}

QJsonObject ContactDetailGroupBox::toJsonObject()
{
    /// TODO: Assemble data in model into a QJsonObject
    return QJsonObject();
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
    model->insertRow(model->rowCount()-1);
}
