#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singu.h"
#include "forgetpassword.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QErrorMessage>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signupButt_clicked()
{
    singU *newPage=new singU();
    this->close();
    newPage->show();
}
void MainWindow::on_commandLinkButton_clicked()
{
    forgetPassword *newPage=new forgetPassword();
    this->close();
    newPage->show();
}
QString hashPassword(const QString& password) {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return hash.toHex();
}


void MainWindow::on_loginButt_clicked()
{
    if(ui->userLine==NULL||ui->passLine==NULL){
        qDebug()<<"Error!";
    }
    else{
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("newDB.db");
        if (!db.open()) {
            qDebug() << "Error opening database: ";
            return;
        }
        qDebug()<<"dataBase opened successesfully!";
        qDebug()<<ui->userLine->text();
        qDebug()<<ui->passLine->text();
        QSqlQuery query;
        QString userPass=ui->passLine->text();
        userPass=hashPassword(userPass);
        query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username",ui->userLine->text());
        query.bindValue(":password", userPass);
        QErrorMessage* errorDialog = new QErrorMessage(this);
        if (query.exec() && query.next()) {
            qDebug() << "Login successful!";
            errorDialog->showMessage("Login was successful");
        } else {
            qDebug() << "Invalid login credentials.";
             errorDialog->showMessage("Login failed!");
        }
    }
}




