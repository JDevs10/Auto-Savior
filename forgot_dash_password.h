#ifndef FORGOT_DASH_PASSWORD_H
#define FORGOT_DASH_PASSWORD_H

#include <QDialog>

namespace Ui {
class Forgot_dash_password;
}

class Forgot_dash_password : public QDialog
{
    Q_OBJECT

public:
    explicit Forgot_dash_password(QWidget *parent = 0);
    ~Forgot_dash_password();

private slots:
    void on_Cancel_clicked();
    bool validEmail(QString email);
    void on_Rest_clicked();

private:
    Ui::Forgot_dash_password *ui;
};

#endif // FORGOT_DASH_PASSWORD_H
