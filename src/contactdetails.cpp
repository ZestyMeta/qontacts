#include "contactdetails.h"
#include "ui_contactdetails.h"

ContactDetails::ContactDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactDetails)
{
    ui->setupUi(this);

    ui->photoLbl->setPixmap(QPixmap(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
    ui->frame->setFixedSize(50, 50);
}

ContactDetails::~ContactDetails()
{
    delete ui;
}
