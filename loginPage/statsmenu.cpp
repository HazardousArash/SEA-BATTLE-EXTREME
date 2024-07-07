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
              QString win= query.value(7).toString();
              QString lose= query.value(8).toString();
              QString result="               userName:"+userNAme+"\n"
                               +"               firstName:"+firstName+"   lastName:"+lastName+"\n"
                  +"               points:"+points+"   rank:"+rank+"\n"
                  +"               win:"+win+"   lose:"+lose;
              ui->plainTextEdit->setPlainText(result);
              qDebug()<<"success";
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

