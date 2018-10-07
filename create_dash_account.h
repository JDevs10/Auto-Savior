#ifndef CREATE_DASH_ACCOUNT_H
#define CREATE_DASH_ACCOUNT_H

#include <QDialog>

namespace Ui {
class Create_Dash_Account;
}

class Create_Dash_Account : public QDialog
{
    Q_OBJECT

public:
    explicit Create_Dash_Account(QWidget *parent = 0);
    ~Create_Dash_Account();

private slots:
    void on_Cancel_clicked();

    void on_Register_clicked();

    bool validEmail(QString email);

private:
    Ui::Create_Dash_Account *ui;
};

#endif // CREATE_DASH_ACCOUNT_H
