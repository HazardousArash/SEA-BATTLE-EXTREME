#include "playermenu.h"
#include "ui_playermenu.h"
#include "statsmenu.h"
#include "mainwindow.h"
#include "storycharecters.h"
#include "globalVariables.h"
#include "Game.h"
#include <QSqlQuery>
#include <QSqlError>
void extractctOilDB(){
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", globalUserName);
    if(query.exec()){
        if(query.next()){
            qDebug()<<query.value(16).toInt();
         playerOneOil= query.value(16).toInt();
            qDebug()<<playerOneOil;

            playerOneOil+=30;
            if(playerOneOil>220)
                playerOneOil=220;
            qDebug()<<"success";
            qDebug()<< playerOneOil;
        }
        else{
            qDebug() << "error finding user"<<query.lastError().text();
        }
    }
    else{
        qDebug()<<query.lastError().text();
    }
}
playerMenu::playerMenu(QString userNAme,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::playerMenu)
{
    this->userName=userNAme;
    ui->setupUi(this);
}

playerMenu::~playerMenu()
{
    delete ui;
}

void playerMenu::on_statsPB_clicked()
{
    statsMenu *newPage=new statsMenu(userName);
    this->close();
    newPage->show();
}

void playerMenu::on_pushButton_clicked()
{
    MainWindow *newPage=new MainWindow();
    this->close();
    newPage->show();
}

void playerMenu::on_chPb_clicked()
{
    storyCharecters *newPage=new storyCharecters(userName);
    this->close();
    newPage->show();
}


void playerMenu::on_vsbbotPB_clicked()
{
    globalUserName=userName;
    extractctOilDB();
    this->close();
    modeChosen=1;
    runGame();

}


void playerMenu::on_CoPB_clicked()
{
    globalUserName=userName;
    playerOneOil=220;
    this->close();
    modeChosen=2;
    runGame();
}

