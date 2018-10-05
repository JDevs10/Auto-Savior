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

private:
    Ui::login_interface *ui;
};

#endif // LOGIN_INTERFACE_H
