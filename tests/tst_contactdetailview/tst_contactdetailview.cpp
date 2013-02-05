#include <QtTest/QtTest>

class tst_ContactDetailView: public QObject
{
   Q_OBJECT
   
private slots:
   void stub() {
      QVERIFY(true);
   }
};

QTEST_MAIN(tst_ContactDetailView)
#include "tst_contactdetailview.moc"
