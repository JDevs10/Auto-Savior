#include "forgot_dash_password.h"
#include "ui_forgot_dash_password.h"
#include "QMessageBox"
#include "QFile"
#include "QtSql"
#include "QDebug"

/*  In this sector the user can change his password of Auto Savior
    The user only needs his unique email address to change the password
*/

extern QString userGlobalDB;

Forgot_dash_password::Forgot_dash_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Forgot_dash_password)
{
    ui->setupUi(this);
    //![1]  Windown parameters

    setWindowTitle(tr("Auto Savior"));      // Title
    setMaximumSize(355, 239);                  // App size
    //  seMinimumSize(width,height)

    //![1]
}

Forgot_dash_password::~Forgot_dash_password()
{
    delete ui;
}

void Forgot_dash_password::on_Cancel_clicked()
{
    QMessageBox::StandardButtons reply = QMessageBox::information(this,"Cancelling",
                                                                  "You are about to leave the reset password window",
                                                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        Forgot_dash_password::close();
    }
}

bool Forgot_dash_password::validEmail(QString email)
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

void Forgot_dash_password::on_Rest_clicked()
{
    QString nPwd,cnPwd,email,line,fileName,pwdSpot;
    QStringList lineListHoriz,lineListVerti;
    int pwdSpotInt = -1;
    nPwd = ui->line_nPwd->text();
    cnPwd = ui->line_cPwd->text();
    email = ui->line_email->text();
    fileName = "settings/LoginSettings.stg";

    if(nPwd.isEmpty() || cnPwd.isEmpty() || email.isEmpty()){
        QMessageBox::warning(this, "Warning","one or more fields are empty.\r\n"
                                             "Please fill are the fields to proced.");
    }else{
        if(validEmail(email) == true){
            if(nPwd == cnPwd){
                //password and confirm password are the same
                QFile file(fileName);

                if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                    return;

                QTextStream out(&file);
                // looking for the correct user information

                line = out.readAll();
                lineListHoriz = line.split('|');
                lineListVerti = line.split("----------------------------------------------------------------------|");

                file.close();


                QStringList::const_iterator constIterator;
                for (constIterator = lineListHoriz.constBegin(); constIterator != lineListHoriz.constEnd(); ++constIterator){
                    qDebug() << (*constIterator).toLocal8Bit().constData() << endl;
                    pwdSpotInt++;

                    if(email == (*constIterator).toLocal8Bit().constData()){
                        qDebug() << "find user email " << email ;
                        //showLaSuite = true;
                        //ok = true;

                        //find the user password
                        constIterator++;
                        constIterator++;
                        pwdSpotInt++;
                        pwdSpotInt++;
                        if(constIterator != lineListHoriz.constEnd()){
                            qDebug() << (*constIterator).toLocal8Bit().constData() << endl;

                            // find password
                            pwdSpot = lineListHoriz[pwdSpotInt];

                            // replace password
                            QRegularExpression oldPwd(pwdSpot);
                            QString newPwd(nPwd);

                            line.replace(oldPwd, newPwd);

                            file.remove();
                            QFile newFile(fileName);
                            if(newFile.open(QFile::WriteOnly | QFile::Text)){
                                QTextStream out(&newFile);
                                out.seek(0);
                                out << line;
                            }
                            newFile.close();
                            QMessageBox::information(this, "Success", "Your password have been changed!!!");
                            break;
                        }
                    }else{
                        continue;
                    }
                }
                // After restting the Major password then erease the lines
                ui->line_nPwd->clear();
                ui->line_cPwd->clear();
                ui->line_email->clear();

            }else{
                //password and confirm password aren't the same
                qDebug() << "password and confirm password aren't the same";

                QMessageBox::information(this, "Ops", "The password and confirm password are different!!!");
                ui->line_nPwd->clear();
                ui->line_cPwd->clear();
            }
        }else {
            //validEmail
            QMessageBox::warning(this, "Email","Wrong Email, Email not correctly written !!!");
            ui->line_email->clear();
        }
    }
}
