#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* are we connected? */
    dbConnected = false;
    /* pause loading table when switching database, otherwise it will crash */
    pauseLoading = true;
    /* PGSQL driver, on FreeBSD port/pkg qt5-sqldrivers-pgsql */
    db = QSqlDatabase::addDatabase("QPSQL");
    /* we're local */
    db.setHostName("127.0.0.1");
    /* it's best to use perms of local logged in user (for example if you are 'dave')
     * however if you want you can add user/password here and even change the host
     * check TLS options, though
    db.setUserName("username");
    db.setPassword("password");
    */

    /* use template1 to get database list, postgres table might not be authorized for local user */
    db.setDatabaseName("template1");
    dbConnected = db.open();
    if (dbConnected)
    {
        /* get list of databases */
        QSqlQuery query("SELECT datname FROM pg_database WHERE datistemplate = false");
        while (query.next())
        {
                /* add to combo box */
                ui->dbCombo->addItem(query.value(0).toString());
        }
    } else {
        /* did not connect, no point in continuing so die */
        QMessageBox msgBox;
        msgBox.setText("Connection to Database Failed.");
        msgBox.exec();
        qApp->exit();
    }
}

MainWindow::~MainWindow()
{
    /* bye, bye */
    delete ui;
}


void MainWindow::on_dbCombo_currentIndexChanged(const QString &arg1)
{
    pauseLoading = true;
    if (dbConnected)
    {
        db.setDatabaseName(arg1);
        dbConnected = db.open();
        if (dbConnected)
        {
            ui->dbTableList->clear();
            QSqlQuery query;
            query.exec("SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname != 'pg_catalog' AND schemaname != 'information_schema'");
            while (query.next())
            {
                ui->dbTableList->addItem(query.value(0).toString());
            }
        } else {
            QMessageBox msgBox;
            msgBox.setText("Error connecting to " + arg1);
            msgBox.exec();
            /* don't bail here, probably just a perms issue */
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Database is not open.");
        msgBox.exec();
        qApp->exit();
        /* but it should be open */
    }
    pauseLoading = false;
}

void MainWindow::on_dbTableList_currentRowChanged(int currentRow)
{
    if (!pauseLoading)
    {
        QString tableName = ui->dbTableList->item(currentRow)->text();
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM " + tableName);

        /* this could return nothing if there's a perms issue
            even if your user has access to database you might not have perms on tables
         try running : GRANT SELECT ON ALL TABLES IN SCHEMA public TO yourUsername; */

        /* set db model on tableview */
        ui->dbTableView->setModel(model);
        /* enable user column sort by clicking on header */
        ui->dbTableView->setSortingEnabled(true);
        /* disable editing / make table read-only */
        ui->dbTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}
