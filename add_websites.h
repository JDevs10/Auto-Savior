#ifndef ADD_WEBSITES_H
#define ADD_WEBSITES_H

#include <QDialog>

namespace Ui {
class Add_Websites;
}

class Add_Websites : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Websites(QWidget *parent = 0);
    ~Add_Websites();

private slots:
    void on_cancel_clicked();

    bool validEmail(QString email);

    void on_add_clicked();

private:
    Ui::Add_Websites *ui;
};

#endif // ADD_WEBSITES_H
