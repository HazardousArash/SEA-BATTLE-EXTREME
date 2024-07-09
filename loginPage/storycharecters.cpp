#include "storycharecters.h"
#include "ui_storycharecters.h"
#include "playermenu.h"

storyCharecters::storyCharecters(QString useRName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::storyCharecters)
{
    ui->setupUi(this);
    this->userName=useRName;
}

storyCharecters::~storyCharecters()
{
    delete ui;
}

void storyCharecters::on_pushButton_clicked()
{
    playerMenu *newPage=new playerMenu(userName);
    this->close();
    newPage->show();
}

