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
    
private:
    Ui::ContactDetails *ui;
};

#endif // CONTACTDETAILS_H
