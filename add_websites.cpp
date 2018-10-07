#include "add_websites.h"
#include "ui_add_websites.h"
#include "QDebug"
#include "QMessageBox"
#include "QtSql"

extern QString userGlobalDB;

Add_Websites::Add_Websites(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Websites)
{
    ui->setupUi(this);

    //![1]  Windown parameters

    setWindowTitle(tr("Auto Savior"));      // Title
    setMaximumSize(350, 264);                  // App size
    //  seMinimumSize(width,height)

    //![1]
}

Add_Websites::~Add_Websites()
{
    delete ui;
}

void Add_Websites::on_cancel_clicked()
{
    Add_Websites::close();
}

bool Add_Websites::validEmail(QString email)
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

void Add_Websites::on_add_clicked()
{
    QString webSite, webSiteName, user, pwd, cpwd, email;

    webSite = ui->url_line_4->text();
    webSiteName = ui->web_site_name_line_4->text();
    user = ui->login_line_4->text();
    pwd = ui->pwd_line_4->text();
    cpwd = ui->c_pwd_line_4->text();
    email = ui->email_line_4->text();

    if(webSite.isEmpty() || webSiteName.isEmpty() || user.isEmpty() || pwd.isEmpty() || cpwd.isEmpty() || email.isEmpty()){
        qDebug() << "One or more register field are empty...";

        QMessageBox::warning(this, "Empty field","One or more register field are empty, "
                                                 "please check your form again!!!");
    }
    if(validEmail(email) == true){
        if(pwd == cpwd){
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(userGlobalDB);

            if(!db.open())
                qDebug() << db.lastError().text();


            QSqlQuery qry;
            qry.prepare("insert into Website (id,Website,User,Password,Email,Url) "
                        "values (null,'"+webSiteName+"','"+user+"','"+pwd+"','"+email+"','"+webSite+"')");
            if(!qry.exec())
                qDebug() << qry.lastError().text();
            qDebug() << "insert done...";

            QMessageBox::information(this,"Add Website","Your Website have been registered.");
            Add_Websites::close();

        }else{
            //if pwd != cPwd
            pwd.clear();
            cpwd.clear();
            QMessageBox::warning(this, "Password","The password and confirm password are different !!!");
        }
    }else{
        //validEmail
        QMessageBox::warning(this, "Email","Wrong Email, Email not correctly written !!!");
        email.clear();
    }
}
