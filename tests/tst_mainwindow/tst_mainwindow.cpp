#include <QtTest/QtTest>

class tst_MainWindow: public QObject
{
    Q_OBJECT
   
private slots:
    void stub() {
       QVERIFY(true);
    }
};

QTEST_MAIN(tst_MainWindow)
#include "tst_mainwindow.moc"
