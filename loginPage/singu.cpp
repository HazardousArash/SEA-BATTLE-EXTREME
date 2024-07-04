#include "singu.h"
#include "ui_singu.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QErrorMessage>
#include <QCryptographicHash>
#include <regex>


using namespace std;
singU::singU(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::singU)
{
    ui->setupUi(this);
}

singU::~singU()
{
    delete ui;
}
QString hashPasswordAgain(const QString& password) {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return hash.toHex();
}
bool isValidRegexfirstName(string input)
{
    regex pattern("^[A-Za-z]+$");
    return regex_match(input, pattern);
}
bool isValidRegexLastName(string input)
{
    regex pattern("^[A-Za-z]+([ -][A-Za-z]+)?$");
    return regex_match(input, pattern);
}
bool isValidRegexEmailData(string input)
{
    regex pattern("^[A-Za-z][A-Za-z0-9]*(?:[._][A-Za-z0-9]+)*@[A-Za-z]+(?:\\.[A-Za-z]+)?\\.com$");
    return regex_match(input, pattern);
}
bool isValidRegexUserName(string input)
{
    regex pattern("^[a-zA-Z0-9]+(?:[._][a-zA-Z0-9]+)*$");
    return regex_match(input, pattern);
}
bool isValidRegexPassword(string input)
{
    regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[!@#$%^&*()\\-=+])(?!.*([a-zA-Z\\d])\\1{3})\\S{6,20}\\s*$");
    return regex_match(input, pattern);
}
bool isValidRegexSecurityKey(string input)
{
    regex pattern("^[A-Za-z0-9]+$");
    return regex_match(input, pattern);
}

void singU::on_pushButton_clicked()
{
         QErrorMessage* errorDialog = new QErrorMessage(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("G:\\oldDesktop\\programing\\newS\\UNI\\402-403-AP\\QTFiles\\loginPage\\newDB.db");
    if (!db.open()) {
        qDebug() << "Error opening database: ";
        return;
    }
    if(ui->firstNLine==NULL||ui->lastNLine==NULL||ui->gmailLine==NULL||ui->userLine==NULL||ui->passLine==NULL||ui->SkeyLine==NULL){
        qDebug()<<"Please give us all the detail!";
         errorDialog->showMessage("Please fill everything");
    }
    else{
        //check all the regex
        if(!isValidRegexUserName(ui->userLine->text().toStdString())){
           errorDialog->showMessage("invalid UserName, Try again please");
            return ;
        }
        QSqlQuery insertQuery;
        insertQuery.prepare("SELECT username FROM users WHERE username = :username");
        insertQuery.bindValue(":username", ui->userLine->text());
        if (insertQuery.exec() && insertQuery.next()) {
            errorDialog->showMessage("userName already exist, please choose another one");
            return;
        }
        if(!isValidRegexPassword(ui->passLine->text().toStdString())){
            errorDialog->showMessage("invalid Password, Try again please");
            return ;
        }
        if(!isValidRegexfirstName(ui->firstNLine->text().toStdString())){
            errorDialog->showMessage("invalid firstName, Try again please");
            return ;
        }
        if(!isValidRegexLastName(ui->lastNLine->text().toStdString())){
            errorDialog->showMessage("invalid lastName, Try again please");
            return ;
        }
        if(!isValidRegexEmailData(ui->gmailLine->text().toStdString())){
            errorDialog->showMessage("invalid Email, Try again please");
            return ;
        }
        if(!isValidRegexSecurityKey(ui->SkeyLine->text().toStdString())){
            errorDialog->showMessage("invalid security Key, Try again please");
            return ;
        }

        insertQuery.prepare("INSERT INTO users (username, password,firstName,lastName,email,securityKey,points,rank,theme1,theme2,theme3,ach1,ach2,ach3) VALUES (:username,:password,:firstName,:lastName,:email,:securityKey,:points,:rank,:theme1,:theme2,:theme3,:ach1,:ach2,:ach3)");
        QString userPass=ui->passLine->text();
        userPass=hashPasswordAgain(userPass);
        QString securityKeyHash=ui->SkeyLine->text();
        securityKeyHash=hashPasswordAgain(securityKeyHash);

        insertQuery.bindValue(":username", ui->userLine->text());
        insertQuery.bindValue(":password", userPass);
        insertQuery.bindValue(":firstName",ui->firstNLine->text());
        insertQuery.bindValue(":lastName",ui->lastNLine->text());
        insertQuery.bindValue(":email",ui->gmailLine->text());
        insertQuery.bindValue(":securityKey",securityKeyHash);
        insertQuery.bindValue(":points",0);
        insertQuery.bindValue(":rank",1);
        insertQuery.bindValue(":theme1",0);
        insertQuery.bindValue(":theme2",0);
        insertQuery.bindValue(":theme3",0);
        insertQuery.bindValue(":ach1",0);
        insertQuery.bindValue(":ach2",0);
        insertQuery.bindValue(":ach3",0);

        if (insertQuery.exec()) {

            qDebug() << "Data inserted successfully!";
errorDialog->showMessage("Sign up was successful");
        } else {
            qDebug() << "Error inserting data: ";
            errorDialog->showMessage("Sign up failed");
        }
    }

}

void singU::on_pushButton_2_clicked()
{
    MainWindow *newwindow=new MainWindow();
    this->close();
    newwindow->show();
}

