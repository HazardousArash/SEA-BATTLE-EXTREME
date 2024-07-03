#include "PlayingWindow.h"
#include "ui_PlayingWindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>

PlayingWindow::PlayingWindow(QWidget *parent, Board* board, ThemeManager* themeManager)
    : QWidget(parent),
    ui(new Ui::PlayingWindow),
    board(board),
    themeManager(themeManager) {

    qDebug() << "PlayingWindow constructor started";

    ui->setupUi(this);
    qDebug() << "UI setup completed";

    setupGridBackground(); // Call setupGridBackground in the constructor
    qDebug() << "Grid background setup completed";

    if (board) {
        qDebug() << "Board size:" << board->getGrid().size();
        // Additional setup using the board can go here
    }

    qDebug() << "PlayingWindow initialized";
}

PlayingWindow::~PlayingWindow() {
    qDebug() << "PlayingWindow destructor started";
    delete ui;
    qDebug() << "UI deleted";
}

void PlayingWindow::setupGridBackground() {
    qDebug() << "Entering setupGridBackground...";
    if (!themeManager) {
        qDebug() << "ThemeManager is not initialized!";
        return;
    }

    QPixmap gridBackground = themeManager->getIcon("paperGrid");
    QPixmap gridBackgroundEnemy = themeManager->getIcon("paperGridEnemy");
    qDebug() << "Loaded icons: paperGrid isNull:" << gridBackground.isNull() << " paperGridEnemy isNull:" << gridBackgroundEnemy.isNull();

    if (gridBackground.isNull() || gridBackgroundEnemy.isNull()) {
        qDebug() << "Failed to load grid background!";
        return;
    }

    // Set the pixmaps for the labels in the UI
    if (ui->myBoard && ui->enemyBoard) {
        ui->myBoard->setPixmap(gridBackground);
        ui->myBoard->setScaledContents(true);
        qDebug() << "Assigned gridBackground to myBoard.";

        ui->enemyBoard->setPixmap(gridBackgroundEnemy);
        ui->enemyBoard->setScaledContents(true);
        qDebug() << "Assigned gridBackgroundEnemy to enemyBoard.";
    } else {
        qDebug() << "Labels myBoard or enemyBoard are not initialized!";
        return;
    }

    int gridSize = 10;
    float cellSizeX = gridBackground.width() / gridSize;
    float cellSizeY = gridBackground.height() / gridSize;

    // Create the grid layout for myBoard
    if (ui->myBoard) {
        QGridLayout *gridLayout1 = new QGridLayout(ui->myBoard);
        gridLayout1->setSpacing(0); // No spacing between cells
        gridLayout1->setContentsMargins(0, 0, 0, 0);

        for (int j = 0; j < gridSize; ++j) { // Loop for rows
            for (int i = 0; i < gridSize; ++i) { // Loop for columns
                QLabel* cell1 = new QLabel(this);
                cell1->setFixedSize(static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
                cell1->setStyleSheet("border: 1px solid gray; background: transparent;");
                cell1->setObjectName(QString("cell_%1_%2").arg(j).arg(i));
                gridLayout1->addWidget(cell1, j, i); // Add the label to the grid layout
                qDebug() << "Added cell to myBoard:" << QString("cell_%1_%2").arg(j).arg(i);
            }
        }
        ui->myBoard->setLayout(gridLayout1); // Set the layout for the myBoard label
        qDebug() << "Created grid layout for myBoard.";
    } else {
        qDebug() << "myBoard label is not initialized!";
    }

    // Create the grid layout for enemyBoard
    if (ui->enemyBoard) {
        QGridLayout *gridLayout2 = new QGridLayout(ui->enemyBoard);
        gridLayout2->setSpacing(0); // No spacing between cells
        gridLayout2->setContentsMargins(0, 0, 0, 0);

        for (int j = 0; j < gridSize; ++j) { // Loop for rows
            for (int i = 0; i < gridSize; ++i) { // Loop for columns
                QLabel* cell2 = new QLabel(this);
                cell2->setFixedSize(static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
                cell2->setStyleSheet("border: 1px solid gray; background: transparent;");
                cell2->setObjectName(QString("cell_enemy_%1_%2").arg(j).arg(i));
                gridLayout2->addWidget(cell2, j, i); // Add the label to the grid layout
                qDebug() << "Added cell to enemyBoard:" << QString("cell_enemy_%1_%2").arg(j).arg(i);
            }
        }
        ui->enemyBoard->setLayout(gridLayout2); // Set the layout for the enemyBoard label
        qDebug() << "Created grid layout for enemyBoard.";
    } else {
        qDebug() << "enemyBoard label is not initialized!";
    }

    qDebug() << "Grid background setup completed.";
}

void PlayingWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    qDebug() << "PlayingWindow shown.";
}
