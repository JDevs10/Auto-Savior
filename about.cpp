#include "about.h"
#include "ui_about.h"
#include "QtSql"

extern QString userGlobalDB;

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    //![1]  Windown parameters

    setWindowTitle(tr("Auto Savior"));      // Title
    setMaximumSize(250, 200);                  // App size
    //  seMinimumSize(width,height)

    //![1]

    findLanguage();
}

About::~About()
{
    delete ui;
}

void About::on_Close_clicked()
{
    About::close();
}
\
void About::findLanguage()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(userGlobalDB);

    if(!db.open())
        db.lastError().text();

    QString dbLanguage;
    QSqlQuery qry;
    QString searchLanguage = "SELECT language FROM Identification";

    if(!qry.exec(searchLanguage)){
        qDebug() << qry.lastError().text();
    }

    while (qry.next()) {
        dbLanguage = qry.value(0).toString();


        if(dbLanguage == "English"){
            ui->label_text->setText("Auto Savior assists in generating \n"
                                    "and retrieving complex passwords, \n"
                                    "potentially storing such passwords \n"
                                    "in local encrypted database.");
        }
        if(dbLanguage == "French"){
            ui->label_text->setText("Auto Savior aide à générer \n"
                                    "et à récupérer des mots de passe \n"
                                    "complexes, stockant potentiellement \n"
                                    "ces mots de passe dans une base \n"
                                    "de données cryptée locale.");
        }
        if(dbLanguage == "Spanish"){
            ui->label_text->setText("Auto Savior ayuda a generar \n"
                                    "y recuperar contraseñas complejas, \n"
                                    "potencialmente almacenando \n"
                                    "tales contraseñas en la base \n"
                                    "de datos cifrada local.");
        }
        if(dbLanguage == "Dutch"){
            ui->label_text->setText("Auto Savior helpt bij het genereren "
                                    "en ophalen van complexe wachtwoorden, "
                                    "mogelijk het opslaan van dergelijke "
                                    "wachtwoorden in een lokaal "
                                    "gecodeerde database.");
        }
    }
}
