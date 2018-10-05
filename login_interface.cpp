#include "login_interface.h"
#include "ui_login_interface.h"

login_interface::login_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_interface)
{
    ui->setupUi(this);
}

login_interface::~login_interface()
{
    delete ui;
}
