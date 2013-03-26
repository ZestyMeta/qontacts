#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void saveDataToDisk();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* contactListModel;
    QJsonDocument* document;

    void initJsonDocument();
};

#endif // MAINWINDOW_H
