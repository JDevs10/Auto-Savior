#include "login_interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    login_interface w;
    w.show();

    return a.exec();
}
