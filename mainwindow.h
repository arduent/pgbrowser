#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dbCombo_currentIndexChanged(const QString &arg1);

    void on_dbTableList_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool dbConnected;
    bool pauseLoading;
};
#endif // MAINWINDOW_H
