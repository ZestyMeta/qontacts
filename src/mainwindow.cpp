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

    QSplitter* splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(contactList);
    splitter->addWidget(new ContactDetails);
    splitter->setSizes(QList<int>() << 300 << width()-300);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
