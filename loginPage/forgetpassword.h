#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QMainWindow>

namespace Ui {
class forgetPassword;
}

class forgetPassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit forgetPassword(QWidget *parent = nullptr);
    ~forgetPassword();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::forgetPassword *ui;
};

#endif // FORGETPASSWORD_H
