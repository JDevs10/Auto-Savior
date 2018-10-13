#ifndef CHANGE_PASSWORD_WEBSITE_H
#define CHANGE_PASSWORD_WEBSITE_H

#include <QDialog>

namespace Ui {
class Change_Password_Website;
}

class Change_Password_Website : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Password_Website(QWidget *parent = 0);
    ~Change_Password_Website();

private slots:
    void on_Cancel_clicked();

    void on_Rest_clicked();

private:
    Ui::Change_Password_Website *ui;
};

#endif // CHANGE_PASSWORD_WEBSITE_H
