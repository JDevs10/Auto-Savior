#ifndef SEARCH_PASSWORD_H
#define SEARCH_PASSWORD_H

#include <QDialog>

extern QString userGlobalDB; // isserGlobalDB is a variable from login_interface.cpp

namespace Ui {
class Search_Password;
}

class Search_Password : public QDialog
{
    Q_OBJECT

public:
    explicit Search_Password(QWidget *parent = 0);
    ~Search_Password();

private slots:
    void on_Copy_the_pwd_clicked();

    QString GetRandomString(int randomStringLength, bool letters_box
    , bool upper_lower_case_box, bool numbers_box, bool symbols_box);

    void on_Generate_clicked();

private:
    Ui::Search_Password *ui;
};

#endif // SEARCH_PASSWORD_H
