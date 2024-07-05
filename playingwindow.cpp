#include "PlayingWindow.h"
#include "ui_PlayingWindow.h"
#include "Board.h"
#include "ThemeManager.h"
#include "ClickableLabel.h"
#include "GameWindow.h"

#include <QDebug>
#include <QMovie>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QContextMenuEvent>
#include <QMenu>

PlayingWindow::PlayingWindow(QWidget *parent, GameWindow *gameWindow, Board* myBoard, Board* enemyBoard, ThemeManager* themeManager)
    : QWidget(parent),
    ui(new Ui::PlayingWindow),
    gameWindow(gameWindow),
    myBoard(new Board(*myBoard)),  // Make a deep copy of the myBoard
    enemyBoard(new Board(*enemyBoard)),  // Make a deep copy of the enemyBoard
    themeManager(themeManager) {
    qDebug() << "PlayingWindow constructor started";

    ui->setupUi(this);
    qDebug() << "UI setup completed";

    setupGifBackground(); // Set up the GIF background
    qDebug() << "GIF background setup completed";

    setupGridBackground(); // Call setupGridBackground for both boards
    qDebug() << "Grid background setup completed";

    updateGridWithBoardState(this->myBoard, "myBoard"); // Update the grid with the current board state
    updateGridWithBoardState(this->enemyBoard, "enemyBoard"); // Update the enemy grid with the current board state

    if (this->myBoard) {
        qDebug() << "My Board size:" << this->myBoard->getGrid().size();
    }

    if (this->enemyBoard) {
        qDebug() << "Enemy Board size:" << this->enemyBoard->getGrid().size();
    }

    qDebug() << "PlayingWindow initialized";
}

PlayingWindow::~PlayingWindow() {
    qDebug() << "PlayingWindow destructor started";
    delete ui;
    delete myBoard;
    delete enemyBoard;
    qDebug() << "UI deleted";
}

void PlayingWindow::setupGifBackground() {
    qDebug() << "Setting up GIF background...";

    if (!ui->waterBackground) {
        qDebug() << "waterBackground label is not initialized!";
        return;
    }

    // Load the GIF using QMovie
    QMovie *movie = new QMovie(":themes/theme1/waterBackground.gif");
    if (!movie->isValid()) {
        qDebug() << "Failed to load GIF from path!";
        return;
    }

    ui->waterBackground->setMovie(movie);
    ui->waterBackground->setScaledContents(true); // Ensure the GIF fits the QLabel
    movie->start();

    qDebug() << "GIF background setup completed.";
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
                ClickableLabel* cell1 = new ClickableLabel(this);
                cell1->setFixedSize(static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
                cell1->setStyleSheet("border: 1px solid gray; background: transparent;");
                cell1->setObjectName(QString("cell_%1_%2").arg(j).arg(i));
                cell1->setRowCol(j, i);
                connect(cell1, &ClickableLabel::leftClicked, this, &PlayingWindow::onBoardBlockClicked);
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
                ClickableLabel* cell2 = new ClickableLabel(this);
                cell2->setFixedSize(static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
                cell2->setStyleSheet("border: 1px solid gray; background: transparent;");
                cell2->setObjectName(QString("cell_enemy_%1_%2").arg(j).arg(i));
                cell2->setRowCol(j, i);
                connect(cell2, &ClickableLabel::leftClicked, this, &PlayingWindow::onEnemyBoardBlockClicked);
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



void PlayingWindow::updateGridWithBoardState(Board* board, const QString& boardName) {
    if (!board) {
        qDebug() << boardName << " is not initialized!";
        return;
    }

    const std::vector<std::vector<int>>& grid = board->getGrid();
    int gridSize = grid.size();

    for (int id = 1; id <= 10; ++id) {
        std::vector<QPoint> shipBlocks;
        for (int j = 0; j < gridSize; ++j) {
            for (int i = 0; i < gridSize; ++i) {
                if (grid[j][i] == id) {
                    shipBlocks.emplace_back(i, j);
                }
            }
        }

        if (!shipBlocks.empty()) {
            int minX = gridSize, minY = gridSize;
            int maxX = 0, maxY = 0;

            for (const auto& point : shipBlocks) {
                minX = std::min(minX, point.x());
                minY = std::min(minY, point.y());
                maxX = std::max(maxX, point.x());
                maxY = std::max(maxY, point.y());
            }

            QString shipIconName;
            int shipLength = 1;

            if (id >= 1 && id <= 4) {
                shipIconName = "tinyShip";
                shipLength = 1;
            } else if (id >= 5 && id <= 7) {
                shipIconName = "smallShip";
                shipLength = 2;
            } else if (id >= 8 && id <= 9) {
                shipIconName = "midShip";
                shipLength = 3;
            } else if (id == 10) {
                shipIconName = "largeShip";
                shipLength = 4;
            }

            QPixmap shipPixmap = QPixmap(themeManager->getIconPath(shipIconName));
            QSize cellSize;

            if (boardName == "myBoard") {
                cellSize = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(minY).arg(minX))->size();
            } else {
                cellSize = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(minY).arg(minX))->size();
            }

            if (minY == maxY) {  // Horizontal ship
                QTransform transform;
                transform.rotate(90);
                QSize iconSize(cellSize.width() * shipLength, cellSize.height());
                shipPixmap = shipPixmap.transformed(transform);
                shipPixmap = shipPixmap.scaled(iconSize, Qt::KeepAspectRatio);
            } else if (minX == maxX) {  // Vertical ship
                QSize iconSize(cellSize.width(), cellSize.height() * shipLength);
                QTransform transform;
                shipPixmap = shipPixmap.transformed(transform).scaled(iconSize, Qt::KeepAspectRatio);
            }

            ClickableLabel* cell;
            if (boardName == "myBoard") {
                cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(minY).arg(minX));
            } else {
                cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(minY).arg(minX));
            }

            if (cell) {
                cell->setPixmap(shipPixmap);
                cell->setFixedSize(QSize(cellSize.width() * (minY == maxY ? shipLength : 1), cellSize.height() * (minX == maxX ? shipLength : 1)));
                cell->setStyleSheet("border: 2px solid red;"); // Add red border for visualization
            }
        }
    }
}


void PlayingWindow::onBoardBlockClicked(int row, int col) {
    qDebug() << "Left-clicked on myBoard at (" << row << ", " << col << ")";
}

void PlayingWindow::onEnemyBoardBlockClicked(int row, int col) {
    qDebug() << "Left-clicked on enemyBoard at (" << row << ", " << col << ")";
}


void PlayingWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    qDebug() << "PlayingWindow shown.";
}

void PlayingWindow::contextMenuEvent(QContextMenuEvent* event) {
    QMenu contextMenu(this);

    QAction* action1 = new QAction("Show myBoard Grid", this);
    connect(action1, &QAction::triggered, this, [this]() {
        if (myBoard) {
            qDebug() << "myBoard state:";
            for (const auto& row : myBoard->getGrid()) {
                QString rowString;
                for (int cell : row) {
                    rowString += QString::number(cell) + " ";
                }
                qDebug() << rowString;
            }
        } else {
            qDebug() << "myBoard is not initialized!";
        }
    });

    QAction* action2 = new QAction("Show enemyBoard Grid", this);
    connect(action2, &QAction::triggered, this, [this]() {
        if (enemyBoard) {
            qDebug() << "enemyBoard state:";
            for (const auto& row : enemyBoard->getGrid()) {
                QString rowString;
                for (int cell : row) {
                    rowString += QString::number(cell) + " ";
                }
                qDebug() << rowString;
            }
        } else {
            qDebug() << "enemyBoard is not initialized!";
        }
    });

    contextMenu.addAction(action1);
    contextMenu.addAction(action2);

    contextMenu.exec(event->globalPos());
}

