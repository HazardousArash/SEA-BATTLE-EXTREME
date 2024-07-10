#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QMainWindow>
#include <QTcpSocket>
#include "gamewindow.h"
namespace Ui {
class clientMenu;
}

class clientMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientMenu(QString userName, QWidget *parent = nullptr);
    ~clientMenu();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    Ui::clientMenu *ui;
    QString userName;
};

#endif // CLIENTMENU_H
