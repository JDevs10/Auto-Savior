#include "search_password.h"
#include "ui_search_password.h"
#include "QDebug"
#include "QtSql"
#include "QMessageBox"
#include "QClipboard"
#include "QStatusBar"

Search_Password::Search_Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search_Password)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(userGlobalDB);

    if(!db.open())
        qDebug() << db.lastError().text();
    return;

    setWindowTitle(tr("Auto Savior"));      // Title
    setMaximumSize(261, 410);
    //  seMinimumSize(width,height
}

Search_Password::~Search_Password()
{
    delete ui;
}

QString Search_Password::GetRandomString(int randomStringLength,
bool letters_box, bool upper_case_box, bool numbers_box, bool symbols_box)
{
    QString possibleSmallLetters = "abcdefghijklmnopqrstuvwxyz";
    QString possibleBigLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString possibleNumbers = "0123456789";
    QString s = "'\'";
    QString possibleSymbols = "~!@#$%&*()_+-={}|[]"+s+";:<>?,./";
    QString possible = "";
    QString complexite = "Complexity :";
    int complex = 0;

    if (letters_box ){
        possible = possible+possibleSmallLetters;
        complex = complex + 10;
    }
    if (upper_case_box){
        possible = possible+possibleBigLetters;
        complex = complex + 15;
    }
    if (numbers_box){
        possible = possible+possibleNumbers;
        complex = complex + 25;
    }
    if (symbols_box){
        possible = possible+possibleSymbols;
        complex = complex + 50;
    }
    if(randomStringLength >=8 && randomStringLength <=12){  complex = complex + 8;    }
    if(randomStringLength >=12 && randomStringLength <=16){ complex = complex + 12;   }
    if(randomStringLength >=16 && randomStringLength <=20){ complex = complex + 16;   }
    if(randomStringLength >=20 && randomStringLength <=24){ complex = complex + 18;   }
    if(randomStringLength >=24 && randomStringLength <=28){ complex = complex + 20;   }
    if(randomStringLength >=28 && randomStringLength <=32){ complex = complex + 22;   }

    if(complex > 100){
        complex = 100;
    }

    // if the case are not checked!
    if(letters_box == false && upper_case_box == false && numbers_box == false && symbols_box == false){
        QMessageBox::information(this,"Information",
        "Please checked the case(s) below to generate a password");
        possible = ".";
    }

    //make random String
    QString randomString;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possible.length();
        QChar nextChar = possible.at(index);
        randomString.append(nextChar);
    }
    //show complexity string
    QString message = complexite;
    ui->label_complexity->setText(message);

    //show number percent
    QString message1 = QString::number(complex);//conversion from int to const QString
    ui->label_compex_nb->setText(message1);

    return randomString;
}

void Search_Password::on_Generate_clicked()
{
    int length = ui->horizontal_pwd_length_Slider->value();
    bool letters_box = ui->checkBox_letters->isChecked();
    bool upper_case_box = ui->checkBox_uppercase_n_lowercase->isChecked();
    bool numbers_box = ui->checkBox_numbers->isChecked();
    bool symbols_box = ui->checkBox_symbols->isChecked();

    QString message = GetRandomString(length,letters_box,upper_case_box,
                                      numbers_box,symbols_box);
    ui->label_show_pwd->setText(message);
}

void Search_Password::on_Copy_the_pwd_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString input = ui->label_show_pwd->text();
    QString message = "The Password copied";
    clip->setText(input);

    ui->Status_bar_text->setText(message);
}
