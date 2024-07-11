#ifndef PLAYERMENU_H
#define PLAYERMENU_H

#include <QMainWindow>
#include "musicplayer.h"
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

    void on_chPb_clicked();

    void on_vsbbotPB_clicked();

    void on_CoPB_clicked();

    void on_onlinePB_clicked();

private:
    Ui::playerMenu *ui;
     MusicPlayer *musicPlayer;
};

#endif // PLAYERMENU_H
