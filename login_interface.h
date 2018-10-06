#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H

#include <QMainWindow>

namespace Ui {
class login_interface;
}

class login_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit login_interface(QWidget *parent = 0);
    ~login_interface();

private slots:
    void on_Cancel_clicked();

    void on_Forgot_password_label_linkActivated(const QString &link);

    void on_creat_account_label_linkActivated(const QString &link);

    void on_Login_clicked();

private:
    Ui::login_interface *ui;
};

#endif // LOGIN_INTERFACE_H
