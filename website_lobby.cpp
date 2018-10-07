#include "website_lobby.h"
#include "ui_website_lobby.h"
#include "QDebug"
#include "QMessageBox"
#include "QtSql"

extern QString userGlobalDB; // isserGlobalDB is a variable from login_interface.cpp
extern QString userGlobalID;
extern QString qrySettingExec;

Website_lobby::Website_lobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Website_lobby)
{
    ui->setupUi(this);
}

Website_lobby::~Website_lobby()
{
    delete ui;
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

void Website_lobby::on_log_out_2_clicked()
{
    QMessageBox::StandardButtons reply = QMessageBox::information(this, "Disconnection...",
                                                                  "You're about to disconnect",
                                                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        //qrySettingExec="";
        Website_lobby::close();
    }
}

void Website_lobby::on_about_clicked()
{
    abtWIND = new About(this);
    abtWIND->show();
}
