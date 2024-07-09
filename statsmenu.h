#ifndef STATSMENU_H
#define STATSMENU_H

#include <QMainWindow>

namespace Ui {
class statsMenu;
}

class statsMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit statsMenu(QString userName,QWidget *parent = nullptr);
    ~statsMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::statsMenu *ui;
    QString userName;
};

#endif // STATSMENU_H
