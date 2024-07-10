#ifndef HOSTMENU_H
#define HOSTMENU_H

#include <QMainWindow>

namespace Ui {
class hostMenu;
}

class hostMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit hostMenu(QString userName,QWidget *parent = nullptr);
    ~hostMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::hostMenu *ui;
    QString ipAddress;
    QString userName;
};

#endif // HOSTMENU_H
