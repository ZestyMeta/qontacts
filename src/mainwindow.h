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
    void saveDataToJson();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* contactListModel;

    void loadContactsDataIntoModel();
};

#endif // MAINWINDOW_H
