#ifndef CONTACTDETAILS_H
#define CONTACTDETAILS_H

#include <QWidget>
#include <QJsonDocument>

#include "contactdetailgroupbox.h"

namespace Ui {
class ContactDetails;
}

class ContactDetails : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContactDetails(QWidget *parent = 0);
    ~ContactDetails();

    void setDocument(QJsonDocument* document);

public slots:
    void onPatientClicked(const QModelIndex &index);

signals:
    void saveContactDetails();
    
private slots:
    void on_saveBtn_clicked();

    void on_editBtn_clicked();

private:
    Ui::ContactDetails *ui;
    QJsonDocument* document;
    int rowIndex;
    QList<ContactDetailGroupBox*> contactDetailList;

    void loadDetailsFromDocument();

    void writeDetailsToDocument();

    void setReadMode(bool readMode);
};

#endif // CONTACTDETAILS_H
