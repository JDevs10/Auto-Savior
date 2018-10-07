#include "create_dash_account.h"
#include "ui_create_dash_account.h"
#include "QtSql"
#include "QDir"
#include "QMessageBox"
#include "QRegularExpression"
#include "QDateTime"
#include "QDebug"

Create_Dash_Account::Create_Dash_Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Dash_Account)
{
    ui->setupUi(this);
}

Create_Dash_Account::~Create_Dash_Account()
{
    delete ui;
}

void Create_Dash_Account::on_Cancel_clicked()
{
    QMessageBox::StandardButtons reply = QMessageBox::question(this, "Warning",
                                                               "Do you wanna cancel and return to the login form",
                                                               QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        Create_Dash_Account::close();
    }
}

bool Create_Dash_Account::validEmail(QString email)
{
    bool actual = true;

    qDebug() << email;

    QRegularExpression regex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                             QRegularExpression::CaseInsensitiveOption);
    if(!regex.match(email).hasMatch())
    {
        actual = false;
    }

    return actual;
}

void Create_Dash_Account::on_Register_clicked()
{
    QString fName, lName, uName, pwd, cPwd, email;
    QString language;

    //Create variables for each line form
    fName = ui->line_firstName->text();
    lName = ui->line_lastName->text();
    uName = ui->line_Username->text();
    pwd = ui->line_pwd->text();
    cPwd = ui->line_c_pwd->text();
    email = ui->line_email->text();
    language = "English";



    QString set="settings/LoginSettings.stg";
    QString space="_", dbdb="db.sql";
    QString dbName = "db/"+lName+space+fName+space+dbdb;
    QDir mdir;
    QString directory("./settings");
    QDir mdir1;
    QString directory1("./db");

    if(fName.isEmpty() || lName.isEmpty() || uName.isEmpty() || pwd.isEmpty() || cPwd.isEmpty() || email.isEmpty()){
        qDebug() << "One or more register field are empty...";

        QMessageBox::warning(this, "Empty field","One or more register field are empty, "
                                                 "please check your form again!!!");
    }
    qDebug() << "The field of form are fild...";

    //if password and confirm password are the same
    if(pwd == cPwd){
        qDebug() << "Password is good...";

        //verified email
        if(validEmail(email) == true){

            //  to create a folder

            if(!mdir.exists(directory)){
                mdir.mkdir(directory);
                qDebug() << "Created";
            }else{
                qDebug() << "already Created";
            }

            QFile fileName(set);
            if(!fileName.exists()){
                qDebug() << set << " does not exist...";

                //open the file and write
                if (!fileName.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;

                QTextStream out(&fileName);
                out << "----------------------------------------------------------------------|\r\n";
                out << "- Save data format...|\r\n";
                out << "- File Name|" << tr ("%1").arg("LoginSettings.stg|\r\n");
                out << "----------------------------------------------------------------------|\r\n";
                out << "Date|Email|UserName|Password|db name|\r\n";
                out << "----------------------------------------------------------------------|\r\n";

                out << tr("%1 |").arg(QDateTime::currentDateTime().toString());     //Date
                out << email << "|";
                out << uName << "|";
                out << pwd << "|";
                out << dbName << "|\r\n";

                fileName.close();
            }else{
                if (!fileName.open(QIODevice::WriteOnly | QIODevice::Append))
                    return;
                QTextStream out(&fileName);

                //out.seek(149);
                //out << "\n";
                out << tr("%1 |").arg(QDateTime::currentDateTime().toString());     //Date
                out << email << "|";
                out << uName << "|";
                out << pwd << "|";
                out << dbName << "|\r\n";
                fileName.close();
            }


            ///////////////////////////////////////////////////////////////////////////////////////////

            //  to create a folder

            if(!mdir1.exists(directory1)){
                mdir1.mkdir(directory1);
                qDebug() << "Created";
            }else{
                qDebug() << "already Created";
            }
            QString file = dbName;

            if(!QFile::exists(file)){
                // if db.sqlite does not exist
                QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName(file);

                if(!db.open()){
                    qDebug () << "Database not created...";
                }

                QSqlQuery query;
                query.exec("CREATE DATABASE IF NOT EXISTS db ;");
                query.exec("USE db;");
                query.exec("create table Identification ("
                           "`id`    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                           "`firstName` varchar(20),"
                           "`lastName` varchar(20),"
                           "`userName` varchar(20),"
                           "`password` varchar(40),"
                           "`email` varchar(40),"
                           "`language` varchar(20),"
                           "`cryption` varchar(20))");

                query.exec("create table Website ("
                           "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                           "`Website` varchar(20),"
                           "`User` varchar(20),"
                           "`Password` varchar(40),"
                           "`Email` varchar(40),"
                           "`Url` varchar(100))");

                query.exec("create table show_db ("
                           "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                           "`show` varchar(60));");

                query.exec("create table Settings ("
                           "`id`    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                           "`displayInfo`   varchar(255));");

                QString insert = "insert into Identification (id,firstName,lastName,userName,password,email,language,cryption) "
                                 "values ('1','"+fName+"','"+lName+"','"+uName+"','"+pwd+"','"+email+"','English','null')";
                QString showDB = "insert into show_db (id,show) values ('1','SELECT * FROM Website')";
                QString settings = "insert into Settings (id,displayInfo,) values ('1','SELECT Website,Email,User,Url FROM Website')";

                QSqlQuery qry,qry1,qry2;
                qry.prepare(insert);
                qry1.prepare(showDB);
                qry2.prepare(settings);

                if(qry.exec() && qry1.exec() && qry2.exec()){
                    qDebug() << "Insert strings excuted";
                }else{
                    qDebug() << "Insert string not excuted";
                    qDebug() << qry.lastError().text();
                    qDebug() << qry1.lastError().text();
                    qDebug() << qry2.lastError().text();
                }

                db.close();


                QMessageBox::StandardButtons reply = QMessageBox::information(this,"Creating Account",
                                                                              "Your account was successfuly registered\r\n"
                                                                              "Exiting to login windows ?",
                                                                              QMessageBox::Yes | QMessageBox::No);
                if(reply == QMessageBox::Yes){
                    Create_Dash_Account::close();
                }else{
                    ui->line_firstName->clear();
                    ui->line_lastName->clear();
                    ui->line_Username->clear();
                    ui->line_pwd->clear();
                    ui->line_c_pwd->clear();
                    ui->line_email->clear();
                }
            }else{
                //if the file exist, notified the user that it exist
                QMessageBox::critical(this,"DB Not possible","it already exist!!!");
            }
        }else{
            //validEmail
            QMessageBox::warning(this, "Email","Wrong Email, Email not correctly written !!!");
            ui->line_email->clear();
        }

    }
}
