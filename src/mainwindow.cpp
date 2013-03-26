#include <QSplitter>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactlist.h"
#include "contactdetails.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initJsonDocument();

    ContactList* contactList = new ContactList;
    contactList->setDocument(document);

    ContactDetails* contactDetails = new ContactDetails;
    contactDetails->setDocument(document);

    QSplitter* splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(contactList);
    splitter->addWidget(contactDetails);
    splitter->setSizes(QList<int>() << width()/3 << 2*width()/3);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);

    connect(contactList, &ContactList::currentIndexChanged, contactDetails, &ContactDetails::onPatientClicked);
    connect(contactDetails, &ContactDetails::saveContactDetails, this, &MainWindow::saveDataToDisk);
    connect(contactDetails, &ContactDetails::saveContactDetails, contactList, &ContactList::loadContactsDataIntoModel);
}

MainWindow::~MainWindow()
{
    saveDataToDisk();
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::saveDataToDisk()
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/contactlist.json");
    file.open(QIODevice::WriteOnly);
    file.write(document->toJson());

    if(file.error() == QFile::NoError)
        statusBar()->showMessage("Sucessfully saved contact list.");
    else
        statusBar()->showMessage("Saved contact list: " + file.errorString());

    file.close();
}

void MainWindow::initJsonDocument()
{
    QDir dir;
    dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/contactlist.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError error;
    QString content = file.readAll();
    file.close();

    document = new QJsonDocument(QJsonDocument::fromJson(content.toUtf8(), &error));

    if(document->isArray() && error.error == QJsonParseError::NoError)
        statusBar()->showMessage("Sucessfully loaded contact list.");
    else
        statusBar()->showMessage("Loaded contact list: " + error.errorString());
}
