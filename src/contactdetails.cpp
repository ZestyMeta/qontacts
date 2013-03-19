#include "contactdetails.h"
#include "ui_contactdetails.h"

ContactDetails::ContactDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactDetails)
{
    ui->setupUi(this);

    ui->photoLbl->setPixmap(QPixmap(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
    ui->frame->setFixedSize(50, 50);
    ui->stackedWidget->setCurrentWidget(ui->readOnlyPage);
}

ContactDetails::~ContactDetails()
{
    delete ui;
}

void ContactDetails::onPatientClicked(QString patientName)
{
    ui->nameLbl->setText(patientName);
}

void ContactDetails::on_saveBtn_clicked()
{
    ui->homephone->setText(ui->home_phone->text());
    ui->homeemail->setText(ui->home_email->text());
    ui->homeaddress->setText(ui->home_address->text());

    ui->workphone->setText(ui->work_phone->text());
    ui->workemail->setText(ui->work_email->text());
    ui->workaddress->setText(ui->work_address->text());
    ui->stackedWidget->setCurrentWidget(ui->readOnlyPage);
}

void ContactDetails::on_editBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->editablePage);
}
