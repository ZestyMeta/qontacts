#include <QtTest/QtTest>
#include "jsonobjectmodel.h"

class tst_JsonObjectModel: public QObject
{
    Q_OBJECT
   
private slots:
    void column_count_should_be_two() {
        JsonObjectModel model;
        QVERIFY(model.columnCount() == 2);
    }

    void populated_object_row_count() {
        JsonObjectModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        model.setJsonObject(object);

        QVERIFY(model.rowCount() == 1);
    }

    void empty_object_row_count() {
        JsonObjectModel model(this);
        model.setJsonObject(QJsonObject());

        QVERIFY(model.rowCount() == 0);
    }

    void data_returns_value_for_first_column() {
        JsonObjectModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        model.setJsonObject(object);

        QCOMPARE(model.data(model.index(0, 0)).toString(), QString("key"));
    }

    void data_returns_value_for_second_column() {
        JsonObjectModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        model.setJsonObject(object);

        QCOMPARE(model.data(model.index(0, 1)).toString(), QString("value"));
    }

    void insert_rows_increases_row_count() {
        JsonObjectModel model(this);

        model.insertRow(0);

        QVERIFY(model.rowCount() == 1);
    }

    void remove_rows_decreases_row_count() {
        JsonObjectModel model(this);

        QJsonObject object;
        object.insert("key", QString("value"));

        model.setJsonObject(object);

        model.removeRow(0);

        QVERIFY(model.rowCount() == 0);
    }

    void set_data_can_be_read_from_model() {
        JsonObjectModel model(this);
        model.insertRow(0);

        model.setData(model.index(0, 0), QString("key"));
        model.setData(model.index(0, 1), QString("value"));

        QVERIFY(model.index(0, 0).data().toString() == QString("key"));
        QVERIFY(model.index(0, 1).data().toString() == QString("value"));
    }

    void model_produces_expected_json_object() {
        JsonObjectModel model(this);
        model.insertRow(0);

        model.setData(model.index(0, 0), QString("key"));
        model.setData(model.index(0, 1), QString("value"));

        QJsonObject object;
        object.insert("key", QString("value"));

        QVERIFY(model.jsonObject() == object);
    }

    void setting_object_resets_model() {
        JsonObjectModel model(this);

        QSignalSpy begin(&model, SIGNAL(modelAboutToBeReset()));
        QSignalSpy end(&model, SIGNAL(modelReset()));

        model.setJsonObject(QJsonObject());

        QVERIFY(begin.count() > 0);
        QVERIFY(end.count() > 0);
    }
};

QTEST_MAIN(tst_JsonObjectModel)
#include "tst_jsonobjectmodel.moc"
