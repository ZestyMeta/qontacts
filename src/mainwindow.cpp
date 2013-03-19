#include <QSplitter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactlist.h"
#include "contactdetails.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ContactList* contactList = new ContactList;    
    QStandardItemModel* contactListModel = new QStandardItemModel(this);
    contactList->setModel(contactListModel);

    ContactDetails* contactDetails = new ContactDetails;

    QSplitter* splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(contactList);
    splitter->addWidget(contactDetails);
    splitter->setSizes(QList<int>() << width()/3 << 2*width()/3);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);

    connect(contactList, &ContactList::patientSelected, contactDetails, &ContactDetails::onPatientClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
