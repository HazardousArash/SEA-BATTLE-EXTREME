#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QMainWindow>

namespace Ui {
class clientMenu;
}

class clientMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientMenu(QString userName,QWidget *parent = nullptr);
    ~clientMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::clientMenu *ui;
    QString userName;
};

#endif // CLIENTMENU_H
