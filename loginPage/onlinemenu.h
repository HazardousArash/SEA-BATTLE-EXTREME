#ifndef ONLINEMENU_H
#define ONLINEMENU_H

#include <QMainWindow>

namespace Ui {
class onlineMenu;
}

class onlineMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit onlineMenu(QString useRNAme,QWidget *parent = nullptr);
    ~onlineMenu();

private slots:
    void on_pushButton_clicked();

    void on_hostPB_clicked();

    void on_clientPB_clicked();

private:
    Ui::onlineMenu *ui;
    QString userName;
};

#endif // ONLINEMENU_H
