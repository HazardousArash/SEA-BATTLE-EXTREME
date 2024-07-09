#include "statsmenu.h"
#include "ui_statsmenu.h"
#include "playermenu.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QErrorMessage>

using namespace std;

void updateWinLoseDB(QString userName,int oil,bool isWin){
    QSqlQuery insertQuery;
    insertQuery.prepare("SELECT * FROM users WHERE username = :username");
    insertQuery.bindValue(":username", userName);

    if (insertQuery.exec() && insertQuery.next()) {
        int rank=insertQuery.value(6).toInt();
        int points=insertQuery.value(5).toInt();
        if(isWin==true){
            int win=insertQuery.value(14).toInt();
            win++;
            switch (rank){
            case 0:
                points+=10;
                if(points>=50){
                    rank+=1;
                    points-=50;
                }
                break;
            case 1:
                points+=20;
                if(points>=75){
                    rank+=1;
                    points-=75;
                }
                break;
            case 2:
                points+=30;
                if(points>=125){
                    rank+=1;
                    points-=125;
                }
                break;
            case 3:
                points+=40;
                if(points>=200){
                    rank+=1;
                    points-=200;
                }
                break;
            case 4:
                points+=50;
            }
            insertQuery.prepare("UPDATE users SET win = :win, points = :points, rank = :rank, oil = :oil WHERE username = :username");
            insertQuery.bindValue(":username",userName);
            insertQuery.bindValue(":win",win);
            insertQuery.bindValue(":rank",rank);
            insertQuery.bindValue(":points",points);
            insertQuery.bindValue(":oil",oil);
            if (insertQuery.exec()) {
                qDebug() << "wins updated successfully!   ";
            } else {
                qDebug()<<"failed updating wins";
            }
        }
        else{
            int lose=insertQuery.value(15).toInt();
            lose++;
            switch (rank){
            case 0:
                points-=5;
                break;
            case 1:
                points-=10;
                break;
            case 2:
                points-=15;
                break;
            case 3:
                points-=20;
                break;
            case 4:
                points-=25;
            }
            if(points<0){
                points=0;
            }
            insertQuery.prepare("UPDATE users SET lose = :lose, points = :points, rank = :rank, oil = :oil WHERE username = :username");
            insertQuery.bindValue(":username",userName);
            insertQuery.bindValue(":lose",lose);
            insertQuery.bindValue(":rank",rank);
            insertQuery.bindValue(":points",points);
            insertQuery.bindValue(":oil",oil);
            if (insertQuery.exec()) {
                qDebug() << "loses updated successfully!";
            } else {
                qDebug()<<"failed updating loses";
            }
        }

    }
}
statsMenu::statsMenu(QString userNAme,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::statsMenu)
{
    ui->setupUi(this);
    userName=userNAme;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("G:\\oldDesktop\\programing\\newS\\UNI\\402-403-AP\\QTFiles\\loginPage\\newDB.db");
    if (!db.open()) {
        qDebug() << "Error opening database: ";
        return;
    }
    qDebug()<<"dataBase opened successesfully!";
      QSqlQuery query;
      query.prepare("SELECT * FROM users WHERE username = :username");
      query.bindValue(":username", userName);

      if(query.exec()){
          if(query.next()){
              QString firstName= query.value(2).toString();
              QString lastName= query.value(3).toString();
              QString points= query.value(5).toString();
              QString rank= query.value(6).toString();
              QString win= query.value(14).toString();
              QString lose= query.value(15).toString();
              QString result="               userName:"+userNAme+"\n"
                               +"               firstName:"+firstName+"   lastName:"+lastName+"\n"
                  +"               points:"+points+"   rank:"+rank+"\n"
                  +"               win:"+win+"   lose:"+lose;
              ui->plainTextEdit->setPlainText(result);
              ui->plainTextEdit->setReadOnly(true);
              qDebug()<<"success";
           //   updateWinLoseDB(userName,10,false);
}
          else{
              qDebug() << "error finding user"<<userName<<query.lastError().text();
          }
      }
      else{
          ui->plainTextEdit->setPlainText("error loading user Data");
          qDebug()<<query.lastError().text();
      }
}

statsMenu::~statsMenu()
{
    delete ui;
}

void statsMenu::on_pushButton_clicked()
{
    playerMenu *newPage=new playerMenu(userName);
    this->close();
    newPage->show();
}


