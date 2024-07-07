#ifndef PLAYERMENU_H
#define PLAYERMENU_H

#include <QMainWindow>

namespace Ui {
class playerMenu;
}

class playerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit playerMenu(QString userName,QWidget *parent = nullptr);
    QString userName;
    ~playerMenu();

private slots:
    void on_statsPB_clicked();

    void on_pushButton_clicked();

private:
    Ui::playerMenu *ui;
};

#endif // PLAYERMENU_H
