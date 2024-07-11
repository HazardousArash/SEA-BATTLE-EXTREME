#include "onlinemenu.h"
#include "ui_onlinemenu.h"
#include "playerMenu.h"
#include "hostMenu.h"
#include "clientmenu.h"
#include "globalVariables.h"

onlineMenu::onlineMenu(QString userNAme, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::onlineMenu)
{
    ui->setupUi(this);
    this->userName = userNAme;
}

onlineMenu::~onlineMenu()
{
    delete ui;
}

void onlineMenu::on_pushButton_clicked()
{
    playerMenu *newPage = new playerMenu(userName);
    this->close();
    newPage->show();
    isOnline=false;
}

void onlineMenu::on_hostPB_clicked()
{
    isOnline=true;
    globalIsHost = true;
    hostMenu *newPage = new hostMenu(userName);
    this->close();
    newPage->show();
}

void onlineMenu::on_clientPB_clicked()
{
    isOnline=true;
    globalIsHost = false;
    clientMenu *newPage = new clientMenu(userName);
    this->close();
    newPage->show();
}
