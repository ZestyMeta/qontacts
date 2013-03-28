#ifndef CONTACTDETAILGROUPBOX_H
#define CONTACTDETAILGROUPBOX_H

#include <QWidget>
#include <QJsonObject>

#include "jsonobjectmodel.h"

namespace Ui {
class ContactDetailGroupBox;
}

class ContactDetailGroupBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContactDetailGroupBox(QWidget *parent = 0);
    ~ContactDetailGroupBox();

    void setJsonObject(const QJsonObject& object);

    QJsonObject toJsonObject();

    void setToReadMode(bool readMode);
    
private slots:
    void on_stackedWidget_currentChanged(int index);

private:
    Ui::ContactDetailGroupBox *ui;
    JsonObjectModel* model;
};

#endif // CONTACTDETAILGROUPBOX_H
