#include "login_interface.h"
#include "ui_login_interface.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>

QString userGlobalDB; // userGlobalDB is a global variable
QString userGlobalID;   // userGlobalID is a global va

login_interface::login_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_interface)
{
    ui->setupUi(this);
    //![1]  Windown parameters

    setWindowTitle(tr("Auto Savior"));      // Title
    setMaximumSize(5, 15);                  // App size
    //  seMinimumSize(width,height)

    //![1]
}

login_interface::~login_interface()
{
    delete ui;
}


void login_interface::on_Cancel_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Warning", "Are you sure, you wanna cancel",
                                                              QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void login_interface::on_Forgot_password_label_linkActivated(const QString &link)
{
    Forgot_dash_password fdpWIND;
    fdpWIND.setModal(this);
    fdpWIND.exec();
}

void login_interface::on_creat_account_label_linkActivated(const QString &link)
{
    Create_Dash_Account cdaWIND;
    cdaWIND.setModal(this);
    cdaWIND.exec();
}

void login_interface::on_Login_clicked()
{
    QString user,pwd,line;
    QStringList lineListHoriz;
    QStringList lineListVerti;
    QString set="settings/LoginSettings.stg";
    user = ui->User_line->text();
    pwd = ui->Pwd_line->text();

    bool showLaSuite = false;
    bool ok = false;

    if(user.isEmpty() || pwd.isEmpty()){
        QMessageBox::information(this,"Empty fields",
                                 "Please Enter your User and Password to proceed!!!");

    }else{
        QFile file(set);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        while(!out.atEnd()){    // looking for the correct user information

            line = out.readAll();
            lineListHoriz = line.split('|');
            lineListVerti = line.split("----------------------------------------------------------------------|");


                        //dbVertiData = lineListVerti[3];
                        //dbHorizData = ;
        }
        file.close();
        QStringList::const_iterator i;
        for (i = lineListHoriz.constBegin(); i != lineListHoriz.constEnd(); ++i){
            qDebug() << (*i).toLocal8Bit().constData() << endl;

            //if user input correspond in data user
            if(user == (*i).toLocal8Bit().constData()){

                //find email
                i = i - 1;
                userGlobalID = (*i).toLocal8Bit().constData();
                i++;

                QStringList::const_iterator constIterator;
                for (constIterator = lineListHoriz.constBegin(); constIterator != lineListHoriz.constEnd(); ++constIterator){
                    qDebug() << (*constIterator).toLocal8Bit().constData() << endl;


                    if(pwd == (*constIterator).toLocal8Bit().constData()){
                        qDebug() << "find users credentials " << user << " " << pwd;
                        showLaSuite = true;
                        ok = true;

                        //find the user db name
                        constIterator++;
                        if(constIterator != lineListHoriz.constEnd()){
                            qDebug() << (*constIterator).toLocal8Bit().constData() << endl;

                            // find db name
                            userGlobalDB = (*constIterator).toLocal8Bit().constData();
                            break;
                        }
                        qDebug() << "didn't find db";
                        break;
                    }else{
                        continue;
                    }
                }
                if(ok == true)
                    break;
            }else{
                continue;
            }
        }
        if(showLaSuite){
//          how to make userGlobalDB pulic to all files ?
            //qDebug() << userGlobalDB;
            Website_lobby wbsl;
            wbsl.setModal(this);
            wbsl.exec();
        }


    }
}
