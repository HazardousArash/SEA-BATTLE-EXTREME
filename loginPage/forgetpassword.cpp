#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QErrorMessage>
#include <regex>
using namespace std;
forgetPassword::forgetPassword(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::forgetPassword)
{
    ui->setupUi(this);
}

forgetPassword::~forgetPassword()
{
    delete ui;
}

bool isValidRegexPassword2(string input)
{
    regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[!@#$%^&*()\\-=+])(?!.*([a-zA-Z\\d])\\1{3})\\S{6,20}\\s*$");
    return regex_match(input, pattern);
}
QString hashPassword2(const QString& password) {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return hash.toHex();
}
void forgetPassword::on_pushButton_clicked()
{
    QErrorMessage* errorDialog = new QErrorMessage(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("G:\\oldDesktop\\programing\\newS\\UNI\\402-403-AP\\QTFiles\\loginPage\\newDB.db");
    if (!db.open()) {
        qDebug() << "Error opening database: ";
        return;
    }
    if(ui->SkeyLine==NULL||ui->userLine==NULL){
        qDebug()<<"Please give us all the detail!";
        errorDialog->showMessage("Please fill everything");
        return;
    }
    else{
        QSqlQuery insertQuery;
        QString Skey=hashPassword2( ui->SkeyLine->text());
        insertQuery.prepare("SELECT * FROM users WHERE username = :username AND securityKey = :securityKey");
        insertQuery.bindValue(":username", ui->userLine->text());
        insertQuery.bindValue(":securityKey", Skey);
        if (insertQuery.exec() && insertQuery.next()) {
            //true
            if(!isValidRegexPassword2(ui->NPassLine->text().toStdString())){
                errorDialog->showMessage("Invalid Password");
                return ;
            }
            insertQuery.prepare("UPDATE users SET password = :newPassword WHERE username = :username");
            insertQuery.bindValue(":username", ui->userLine->text());
            insertQuery.bindValue(":newPassword",hashPassword2(ui->NPassLine->text()));
            if (insertQuery.exec()) {
                qDebug() << "Password updated successfully!   ";
                errorDialog->showMessage("Updated successfully");
            } else {
                errorDialog->showMessage("Failed!");
            }
        }
        else{
            qDebug()<<Skey<<ui->userLine->text();
            errorDialog->showMessage("Invalid credentials.");
        }

    }
}


void forgetPassword::on_pushButton_2_clicked()
{
    MainWindow *Newpage=new MainWindow();
    this->close();
    Newpage->show();
}

