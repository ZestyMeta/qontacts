#include <QtTest/QtTest>
#include "jsonarraymodel.h"

class tst_JsonArrayModel: public QObject
{
    Q_OBJECT
   
private slots:
    void populated_array_row_count() {
        JsonArrayModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        QJsonArray array;
        array.append(object);

        model.setJsonArray(array);

        QVERIFY(model.rowCount() == 1);
    }

    void empty_array_row_count() {
        JsonArrayModel model(this);
        model.setJsonArray(QJsonArray());

        QVERIFY(model.rowCount() == 0);
    }

    void data_returns_value_for_key() {
        JsonArrayModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        QJsonArray array;
        array.append(object);

        model.setJsonArray(array);
        model.setJsonObjectKey("key");

        QCOMPARE(model.data(model.index(0)).toString(), QString("value"));
    }

    void insert_rows_increases_row_count() {
        JsonArrayModel model(this);

        model.insertRow(0);

        QVERIFY(model.rowCount() == 1);
    }

    void remove_rows_decreases_row_count() {
        JsonArrayModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        QJsonArray array;
        array.append(object);

        model.setJsonArray(array);

        model.removeRow(0);

        QVERIFY(model.rowCount() == 0);

    }
};

QTEST_MAIN(tst_JsonArrayModel)
#include "tst_jsonarraymodel.moc"
