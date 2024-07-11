#include "WaitingWindow.h"
#include "ui_WaitingWindow.h"

WaitingWindow::WaitingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaitingWindow)
{
    ui->setupUi(this);
    ui->waitingLabel->setText("Waiting for the other player to finish setting up...");
}

WaitingWindow::~WaitingWindow()
{
    delete ui;
}

void WaitingWindow::onBoardReceived() {
    emit boardReceived();
}
