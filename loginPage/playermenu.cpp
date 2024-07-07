#include "playermenu.h"
#include "ui_playermenu.h"
#include "statsmenu.h"
#include "mainwindow.h"

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
