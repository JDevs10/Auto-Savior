#ifndef WEBSITE_LOBBY_H
#define WEBSITE_LOBBY_H

#include <QDialog>
#include "login_interface.h"
#include "about.h"

namespace Ui {
class Website_lobby;
}

class Website_lobby : public QDialog
{
    Q_OBJECT

public:
    explicit Website_lobby(QWidget *parent = 0);
    ~Website_lobby();

private slots:
    void on_log_out_2_clicked();

    void loadWelcomeTitle();

    void on_about_clicked();

private:
    Ui::Website_lobby *ui;
    Forgot_dash_password* forDashPwdWIND;
    About* abtWIND;
};

#endif // WEBSITE_LOBBY_H
