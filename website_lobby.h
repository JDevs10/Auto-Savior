#ifndef WEBSITE_LOBBY_H
#define WEBSITE_LOBBY_H

#include <QDialog>
#include "login_interface.h"
#include "about.h"
#include "search_password.h"
#include "add_websites.h"

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
    void on_log_out_clicked();

    void loadWelcomeTitle();

    void on_about_clicked();

    void on_search_pwd_clicked();

    void on_Add_WebSites_clicked();

    void loadingTable();

    void on_load_clicked();

private:
    Ui::Website_lobby *ui;
    Forgot_dash_password* forDashPwdWIND;
    About* abtWIND;
    Search_Password* schpwdWIND;
    Add_Websites* addwWIND;
};

#endif // WEBSITE_LOBBY_H
