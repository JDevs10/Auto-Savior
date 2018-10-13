#include "website_lobby.h"
#include "ui_website_lobby.h"
#include "QDebug"
#include "QMessageBox"
#include "QtSql"

QString qrySettingExec="";
extern QString userGlobalDB;

Website_lobby::Website_lobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Website_lobby)
{
    ui->setupUi(this);
    loadWelcomeTitle();
    loadingTable();
}

Website_lobby::~Website_lobby()
{
    delete ui;
}

void Website_lobby::on_load_clicked()
{
    loadingTable();
}

void Website_lobby::loadingTable()
{// load all websites saved...
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(userGlobalDB);

    if(!db.open()){
        qDebug() << db.lastError().text();
    }else {
        // get the db table settings saved by the user in the db
        QString show = "SELECT displayInfo FROM Settings";
        QSqlQuery qry;

        if(!qry.exec(show)){
            qDebug() << "No websites saves at this time !";
        }else{
            //qrySettingExec = qry.nextResult();
        }
    }

    if(qrySettingExec==""){
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery qry;
        QString select = "SELECT website,user,email,url FROM Website";

        qry.exec(select);

        modal->setQuery(qry);
        ui->tableView->setModel(modal);

        //db.close();
        qDebug() << modal->rowCount();
    }else{
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery qry;
        qry.exec(qrySettingExec);

        modal->setQuery(qry);
        ui->tableView->setModel(modal);

        //db.close();
        qDebug() << modal->rowCount();
    }
}

void Website_lobby::loadWelcomeTitle()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(userGlobalDB);

    if(!db.open())
        qDebug() << db.lastError().text();

    QSqlQuery qry;
    qry.exec("SELECT firstName FROM Identification");

    QString welcome_name;
    while (qry.next()) {
        welcome_name = qry.value(0).toString();
        break;
    }
    ui->welcom_email->setText(welcome_name);
}

void Website_lobby::on_log_out_clicked()
{
    QMessageBox::StandardButtons reply = QMessageBox::information(this, "Disconnection...",
                                                                  "You're about to disconnect",
                                                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        qrySettingExec="";
        Website_lobby::close();
    }
}

void Website_lobby::on_search_pwd_clicked()
{
    schpwdWIND = new Search_Password(this);
    schpwdWIND->show();
}

void Website_lobby::on_about_clicked()
{
    abtWIND = new About(this);
    abtWIND->show();
}

void Website_lobby::on_Add_WebSites_clicked()
{
    addwWIND = new Add_Websites(this);
    addwWIND->show();
}

void Website_lobby::on_change_web_pwd_clicked()
{
    cpwdwWIND = new Change_Password_Website(this);
    cpwdwWIND->show();
}
