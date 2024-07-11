#ifndef HOSTMENU_H
#define HOSTMENU_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class hostMenu;
}

class hostMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit hostMenu(QString userName, QWidget *parent = nullptr);
    ~hostMenu();

private slots:
    void on_pushButton_clicked();
    void onNewConnection();

private:
    Ui::hostMenu *ui;
    QString userName;
    QString ipAddress;
};

#endif // HOSTMENU_H
