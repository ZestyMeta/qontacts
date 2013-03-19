#ifndef CONTACTDETAILS_H
#define CONTACTDETAILS_H

#include <QWidget>

namespace Ui {
class ContactDetails;
}

class ContactDetails : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContactDetails(QWidget *parent = 0);
    ~ContactDetails();

public slots:
    void onPatientClicked(QString patientName);
    
private slots:
    void on_saveBtn_clicked();

    void on_editBtn_clicked();

private:
    Ui::ContactDetails *ui;
};

#endif // CONTACTDETAILS_H
