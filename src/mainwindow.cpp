#include <QSplitter>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactlist.h"
#include "contactdetails.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    contactListModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ContactList* contactList = new ContactList;    

    contactList->setModel(contactListModel);

    loadContactsDataIntoModel();

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
    connect(contactList, &ContactList::saveData, this, &MainWindow::saveDataToJson);
}

MainWindow::~MainWindow()
{
    saveDataToJson();
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::saveDataToJson()
{
    QJsonArray array;
    for(int row = 0; row < contactListModel->rowCount(); row++)
    {
        QJsonObject object;
        object.insert("name", contactListModel->index(row, 0).data().toString());
        array.append(object);
    }

    QJsonDocument document;
    document.setArray(array);

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/contactlist.json");
    file.open(QIODevice::WriteOnly);
    file.write(document.toJson());

    if(file.error() == QFile::NoError)
        statusBar()->showMessage("Sucessfully saved contact list.");
    else
        statusBar()->showMessage("Saved contact list: " + file.errorString());
    file.close();
}

void MainWindow::loadContactsDataIntoModel()
{
    QDir dir;
    dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/contactlist.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError error;
    QString content = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8(), &error);

    if(error.error == QJsonParseError::NoError)
        statusBar()->showMessage("Sucessfully loaded contact list.");
    else
        statusBar()->showMessage("Loaded contact list: " + error.errorString());

    file.close();

    QJsonArray array = document.array();
    QJsonArray::iterator begin = array.begin();

    while(begin!=document.array().end())
    {
        contactListModel->appendRow(QList<QStandardItem*>() << new QStandardItem(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), (*begin).toObject().value("name").toString()));
        begin++;
    }
}
