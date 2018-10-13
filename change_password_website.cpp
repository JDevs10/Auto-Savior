#include "change_password_website.h"
#include "ui_change_password_website.h"
#include "QMessageBox"
#include "QtSql"

extern QString userGlobalDB;

Change_Password_Website::Change_Password_Website(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_Password_Website)
{
    ui->setupUi(this);
}

Change_Password_Website::~Change_Password_Website()
{
    delete ui;
}

void Change_Password_Website::on_Cancel_clicked()
{
    QMessageBox::StandardButtons reply = QMessageBox::information(this,"Cancelling",
                                                                  "You are about to leave the reset password window",
                                                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        Change_Password_Website::close();
    }
}

void Change_Password_Website::on_Rest_clicked()
{
    QString nPwd,cPwd,websiteName;

    websiteName = ui->line_website->text();
    nPwd = ui->line_nPwd->text();
    cPwd = ui->line_cPwd->text();

    //check if the fields are empty
    if(websiteName.isEmpty() || nPwd.isEmpty() || cPwd.isEmpty()){
        QMessageBox::warning(this, "Warning","one or more fields are empty.\r\n"
                                             "Please fill are the fields to proceed.");
    }else{
        //the fields are not empty so let's check if the password matches
        if (nPwd != cPwd) {
            QMessageBox::information(this, "Information","The passwords does not match.\r\n"
                                                         "Please make sure the password matches.");
        } else {
            //the password matches
            //let's connect to sqlite and store the data the user wanna change
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(userGlobalDB);

            if(!db.open())
                qDebug() << db.lastError().text();

            //UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6;
            QSqlQuery qry;
            qry.prepare("UPDATE Website SET Password = '"+nPwd+"' WHERE Website = '"+websiteName+"' ");
            if(!qry.exec())
                qDebug() << qry.lastError().text();
            qDebug() << "insert done...";

            QMessageBox::information(this,"Password Changed","The Password have been change to the correspond website.");
            Change_Password_Website::close();
        }
    }
}
