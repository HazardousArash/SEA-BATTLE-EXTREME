#include "statsmenu.h"
#include "ui_statsmenu.h"
#include "playermenu.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QErrorMessage>

using namespace std;

statsMenu::statsMenu(QString userNAme,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::statsMenu)
{
    ui->setupUi(this);
    userName=userNAme;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:\\SEA BATTLE XTRM\\newDB.db");
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


