#include "clientmenu.h"
#include "ui_clientmenu.h"
#include "onlinemenu.h"

clientMenu::clientMenu(QString userName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::clientMenu)
{
    ui->setupUi(this);
    this->userName=userName;
}

clientMenu::~clientMenu()
{
    delete ui;
}

void clientMenu::on_pushButton_clicked()
{
    onlineMenu *newPage=new onlineMenu(userName);
    this->close();
    newPage->show();
}

