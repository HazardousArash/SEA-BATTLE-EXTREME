#include "PlayingWindow.h"
#include "ui_PlayingWindow.h"
#include "Board.h"
#include "ThemeManager.h"
#include "ClickableLabel.h"
#include "GameWindow.h"
#include <qpainter.h>
#include <QDebug>
#include <QMovie>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include "GlobalVariables.h"
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
   //connect(myBoard, &Board::gameOver, this, &PlayingWindow::showLoseWindow);


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
void PlayingWindow::markShipBlockWithHitIndicator(int row, int col, const QString& boardName) {
    ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
    if (boardName == "enemyBoard") {
        cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
    }

    if (cell) {
        // Create a label with "20" text
        QLabel* hitLabel = new QLabel("SHOT!", cell);
        hitLabel->setAlignment(Qt::AlignCenter);
        hitLabel->setStyleSheet("color: white; background-color: rgba(255, 0, 0, 128); border: 1px solid gray;");
        hitLabel->setGeometry(0, 0, cell->width(), cell->height());
        hitLabel->show();
        qDebug() << "ouwwwwwwwwwwwwwwwww";
    } else {
        qDebug() << "Error: ClickableLabel not found for (" << row << ", " << col << ") on " << boardName;
    }
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



void PlayingWindow::showLoseWindow() {
    QWidget* loseWindow = new QWidget();
    loseWindow->setWindowTitle("Game Over");
    loseWindow->setFixedSize(300, 200);
    QVBoxLayout* layout = new QVBoxLayout(loseWindow);

    QLabel* message = new QLabel("You lost all your ships!", loseWindow);
    message->setAlignment(Qt::AlignCenter);
    layout->addWidget(message);

    QPushButton* closeButton = new QPushButton("Close", loseWindow);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, loseWindow, &QWidget::close);
    loseWindow->show();
}


void PlayingWindow::updateGridWithBoardState(Board* board, const QString& boardName) {
    if (!board) {
        qDebug() << boardName << " is not initialized!";
        return;
    }

    const std::vector<std::vector<int>>& grid = board->getGrid();
    int gridSize = grid.size();
    qDebug() << "Updating grid for " << boardName << " with grid size " << gridSize;

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

            if ((modeChosen == 1 && boardName == "enemyBoard") || modeChosen == 2 || (modeChosen == 1 && boardName == "myBoard")) {
                continue; // Skip displaying ship icons for enemyBoard in mode 1, both boards in mode 2, and myBoard in mode 1
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

            qDebug() << "Processing ship ID " << id << " with icon name " << shipIconName << " and length " << shipLength;
            qDebug() << "Ship blocks for ID " << id << ": " << shipBlocks;

            if (minY == maxY) {  // Horizontal ship
                QTransform transform;
                transform.rotate(90);
                QSize iconSize(cellSize.width() * shipLength, cellSize.height());
                shipPixmap = shipPixmap.transformed(transform);
                shipPixmap = shipPixmap.scaled(iconSize, Qt::KeepAspectRatio);
                qDebug() << "Ship is horizontal. Transformed pixmap size: " << iconSize;
            } else if (minX == maxX) {  // Vertical ship
                QSize iconSize(cellSize.width(), cellSize.height() * shipLength);
                QTransform transform;
                shipPixmap = shipPixmap.transformed(transform).scaled(iconSize, Qt::KeepAspectRatio);
                qDebug() << "Ship is vertical. Transformed pixmap size: " << iconSize;
            }

            ClickableLabel* cell;
            if (boardName == "myBoard") {
                cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(minY).arg(minX));
            } else {
                cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(minY).arg(minX));
            }

            if (cell) {
                cell->setPixmap(shipPixmap);
                cell->setStyleSheet("border: none;");
                qDebug() << "Setting cell at (" << minY << "," << minX << ") on " << boardName << " with ship icon and red border.";
                cell->setFixedSize(QSize(cellSize.width() * (minY == maxY ? shipLength : 1), cellSize.height() * (minX == maxX ? shipLength : 1)));
            } else {
                qDebug() << "Cell at (" << minY << "," << minX << ") on " << boardName << " not found.";
            }
        }
    }

    // Apply red borders for hits and misses
    for (int j = 0; j < gridSize; ++j) {
        for (int i = 0; i < gridSize; ++i) {
            int cellValue = grid[j][i];
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(j).arg(i));
            if (boardName == "enemyBoard") {
                cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(j).arg(i));
            }

            if (cell) {
                if (cellValue == -1) {
                    // Missed shots
                    cell->setStyleSheet("border: none; background: rgba(255, 0, 0, 0.5);"); // Glassy red
                } else if (cellValue < -1) {
                    // Hit shots
                    cell->setStyleSheet("border: none; background: rgba(255, 0, 0, 0.5);"); // Glassy red
                } else if (cellValue > 0) {
                    // Ships with no hit
                    if (modeChosen == 1 && boardName == "myBoard") {
                        cell->setStyleSheet("border: 2px solid red; background: transparent;");
                    } else if (modeChosen == 2) {
                        cell->setPixmap(QPixmap());
                        cell->setStyleSheet("border: 1px solid gray; background: transparent;");
                    }
                } else {
                    cell->setPixmap(QPixmap());
                    cell->setStyleSheet("border: 1px solid gray; background: transparent;");
                }
            }
        }
    }

    // Hide ships and remove borders for enemyBoard in mode 1
    if (modeChosen == 1 && boardName == "enemyBoard") {
        for (int j = 0; j < gridSize; ++j) {
            for (int i = 0; i < gridSize; ++i) {
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(j).arg(i));
                if (cell) {
                    cell->setPixmap(QPixmap());
                    cell->setStyleSheet("border: 1px solid gray; background: transparent;");
                }
            }
        }
    }

    // Hide ship pixmaps for myBoard in mode 1 but keep red borders
    if (modeChosen == 1 && boardName == "myBoard") {
        for (int j = 0; j < gridSize; ++j) {
            for (int i = 0; i < gridSize; ++i) {
                int cellValue = grid[j][i];
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(j).arg(i));
                if (cellValue > 0 && cell) {
                    cell->setPixmap(QPixmap());
                }
            }
        }
    }
}




void PlayingWindow::clearShipBlockCrosses(int shipID) {
    const std::vector<std::vector<int>>& grid = enemyBoard->getGrid();
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == -shipID) {
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
                if (cell) {
                    cell->setPixmap(QPixmap());  // Clear the cross
                }
            }
        }
    }
}
void PlayingWindow::makeShipBlocksWhite(int shipID) {
    const std::vector<std::vector<int>>& grid = enemyBoard->getGrid();
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == -shipID) {
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
                if (cell) {
                    cell->setStyleSheet("background: transparent; border: 1px solid gray;");
                }
            }
        }
    }
}
void PlayingWindow::onBoardBlockClicked(int row, int col) {
    if (player2Turn && modeChosen != 1) {
        qDebug() << "Player 2 clicked on myBoard at (" << row << ", " << col << ")";

        int cellValue = myBoard->getCell(row, col);

        if (cellValue == 0) {
            myBoard->getGrid()[row][col] = -1;
            markSingleShipBlockWithCross(row, col, "myBoard");
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setStyleSheet("background: rgba(255, 0, 0, 0.5); border: 1px solid gray;");  // Glassy red
                cell->setEnabled(false);  // Make it unclickable
            }
            // Switch turns
            qDebug() << "Player 2 missed. Switching to player 1's turn.";
            player1Turn = true;
            player2Turn = false;
        } else if (cellValue > 0) {
            int shipID = cellValue;
            myBoard->getGrid()[row][col] = -cellValue;
            markSingleShipBlockWithCross(row, col, "myBoard");
            markSingleShipBlockWithCross( row,  col, "myBoard"); // Add this line to mark the block
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setEnabled(false);  // Make it unclickable
            }

            Ship* ship = Ship::getShipByID(shipID);
            if (ship) {
                ship->decrementHitPoints();
                if (ship->getHitPoints() == 0) {
                    makeShipBlocksPurple(shipID, "myBoard");   // Mark blocks purple
                }
            }

            // Check if all ships of Player 1 are sunken
            if (myBoard->allShipsSunken()) {
                QMessageBox::information(this, "Game Over", "Player 2 wins!");
                showLoseWindow(); // Show the lose window when player loses
                return;
            }

            // Player gets a bonus shot, do not switch turns
            qDebug() << "Player 2 hit a ship. Player 2 gets another turn.";
        }
    } else if (modeChosen == 1) {
        qDebug() << "Player tried to click on their own board in mode 1. Ignoring.";
    } else {
        qDebug() << "It's not player 2's turn!";
    }
}






void PlayingWindow::markSingleShipBlockWithCross(int row, int col) {
    ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
    if (cell) {
        QPoint clickPos = cell->mapFromGlobal(QCursor::pos()); // Get the position of the mouse click relative to the cell
        QPixmap pixmap(cell->size());
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw the existing pixmap if any
        QPixmap originalPixmap = cell->pixmap(Qt::ReturnByValue);
        if (!originalPixmap.isNull()) {
            painter.drawPixmap(0, 0, originalPixmap.scaled(cell->size()));
        }

        // Draw a cross centered at the click position
        painter.setPen(QPen(Qt::red, 2));  // Adjust the color and thickness as needed
        int crossSize = 10; // Size of the cross
        painter.drawLine(clickPos.x() - crossSize, clickPos.y() - crossSize, clickPos.x() + crossSize, clickPos.y() + crossSize);
        painter.drawLine(clickPos.x() + crossSize, clickPos.y() - crossSize, clickPos.x() - crossSize, clickPos.y() + crossSize);

        painter.end();

        cell->setPixmap(pixmap);
    }
}




void PlayingWindow::clearShipBlockCrosses(int shipID, const QString& boardName) {
    const std::vector<std::vector<int>>& grid = boardName == "myBoard" ? myBoard->getGrid() : enemyBoard->getGrid();
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == -shipID) {
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
                if (boardName == "enemyBoard") {
                    cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
                }
                if (cell) {
                    cell->setPixmap(QPixmap());  // Clear the cross
                }
            }
        }
    }
}

void PlayingWindow::makeShipBlocksPurple(int shipID, const QString& boardName) {
    const std::vector<std::vector<int>>& grid = boardName == "myBoard" ? myBoard->getGrid() : enemyBoard->getGrid();
    bool allPartsHit = true;

    // First pass: Check if all parts of the ship are hit
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == shipID) {
                allPartsHit = false;
                break;
            }
        }
        if (!allPartsHit) break;
    }

    // Second pass: If all parts are hit, mark them as purple
    if (allPartsHit) {
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[row].size(); ++col) {
                if (grid[row][col] == -shipID) {
                    ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
                    if (boardName == "enemyBoard") {
                        cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
                    }
                    if (cell) {
                        cell->setStyleSheet("background: rgba(128, 0, 128, 128); border: 1px solid gray;");  // Glassy purple color
                    }
                }
            }
        }
    }
}



void PlayingWindow::onEnemyBoardBlockClicked(int row, int col) {
    if (modeChosen == 1 && player1Turn) { // Mode 1 logic
        qDebug() << "Player clicked on enemyBoard at (" << row << ", " << col << ")";

        int cellValue = enemyBoard->getCell(row, col);

        if (cellValue == 0) {
            enemyBoard->getGrid()[row][col] = -1;
            markSingleShipBlockWithCross(row, col, "enemyBoard");
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setStyleSheet("background: rgba(255, 0, 0, 0.5); border: 1px solid gray;"); // Glassy red
                cell->setEnabled(false); // Make it unclickable
            }
            // Switch turns
            qDebug() << "Player missed. Switching to bot's turn.";
            player1Turn = false;
            player2Turn = true;
            QTimer::singleShot(1000, gameWindow, &GameWindow::triggerBotTurn); // Call bot's turn
        } else if (cellValue > 0) {
            int shipID = cellValue;
            enemyBoard->getGrid()[row][col] = -cellValue;
            markSingleShipBlockWithCross(row, col, "enemyBoard");
            markSingleShipBlockWithCross(row, col, "enemyBoard"); // Add this line to mark the block
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setEnabled(false); // Make it unclickable
            }

            Ship* ship = Ship::getShipByID(shipID);
            if (ship) {
                ship->decrementHitPoints();
                if (ship->getHitPoints() == 0) {
                    makeShipBlocksPurple(shipID, "enemyBoard"); // Mark blocks purple
                }
            }

            // Check if all ships of Player 2 are sunken
            if (enemyBoard->allShipsSunken()) {
                QMessageBox::information(this, "Game Over", "Player 1 wins!");
                return;
            }

            // Player gets a bonus shot, do not switch turns
            qDebug() << "Player hit a ship. Player gets another turn.";
        }
    } else if (modeChosen != 1 && player1Turn) { // Mode 2 logic
        qDebug() << "Player 1 clicked on enemyBoard at (" << row << ", " << col << ")";

        int cellValue = enemyBoard->getCell(row, col);

        if (cellValue == 0) {
            enemyBoard->getGrid()[row][col] = -1;
            markSingleShipBlockWithCross(row, col, "enemyBoard");
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setStyleSheet("background: rgba(255, 0, 0, 0.5); border: 1px solid gray;");  // Glassy red
                cell->setEnabled(false);  // Make it unclickable
            }
            // Switch turns
            qDebug() << "Player 1 missed. Switching to player 2's turn.";
            player1Turn = false;
            player2Turn = true;
        } else if (cellValue > 0) {
            int shipID = cellValue;
            enemyBoard->getGrid()[row][col] = -cellValue;
            markSingleShipBlockWithCross(row, col, "enemyBoard");
            markSingleShipBlockWithCross(row, col, "enemyBoard"); // Add this line to mark the block
            ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
            if (cell) {
                cell->setEnabled(false);  // Make it unclickable
            }

            Ship* ship = Ship::getShipByID(shipID);
            if (ship) {
                ship->decrementHitPoints();
                if (ship->getHitPoints() == 0) {
                    makeShipBlocksPurple(shipID, "enemyBoard");   // Mark blocks purple
                }
            }

            // Check if all ships of Player 2 are sunken
            if (enemyBoard->allShipsSunken()) {
                QMessageBox::information(this, "Game Over", "Player 1 wins!");
                return;
            }

            // Player gets a bonus shot, do not switch turns
            qDebug() << "Player 1 hit a ship. Player 1 gets another turn.";
        }
    } else {
        qDebug() << "It's not player 1's turn!";
    }
}



void PlayingWindow::markSingleShipBlockWithCross(int row, int col, const QString& boardName) {
    qDebug() << "Marking block with cross at (" << row << ", " << col << ") on " << boardName;
    ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_%1_%2").arg(row).arg(col));
    if (boardName == "enemyBoard") {
        cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
    }

    if (cell) {
        QPoint clickPos = cell->mapFromGlobal(QCursor::pos()); // Get the position of the mouse click relative to the cell
        QPixmap pixmap(cell->size());
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw the existing pixmap if any
        QPixmap originalPixmap = cell->pixmap(Qt::ReturnByValue);
        if (!originalPixmap.isNull()) {
            painter.drawPixmap(0, 0, originalPixmap.scaled(cell->size()));
        }

        // Draw a cross centered at the click position
        painter.setPen(QPen(Qt::red, 2));  // Use red for the cross
        int crossSize = 10; // Size of the cross
        painter.drawLine(clickPos.x() - crossSize, clickPos.y() - crossSize, clickPos.x() + crossSize, clickPos.y() + crossSize);
        painter.drawLine(clickPos.x() + crossSize, clickPos.y() - crossSize, clickPos.x() - crossSize, clickPos.y() + crossSize);

        painter.end();

        cell->setPixmap(pixmap);
    } else {
        qDebug() << "Error: ClickableLabel not found for (" << row << ", " << col << ") on " << boardName;
    }
}

void PlayingWindow::makeShipBlocksPurple(int shipID) {
    const std::vector<std::vector<int>>& grid = enemyBoard->getGrid();
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == -shipID) {
                ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
                if (cell) {
                    cell->setStyleSheet("background: green; border: 1px solid gray;");
                }
            }
        }
    }
}


void PlayingWindow::markSingleShipBlockGreen(int row, int col) {
    ClickableLabel* cell = findChild<ClickableLabel*>(QString("cell_enemy_%1_%2").arg(row).arg(col));
    if (cell) {
        QPixmap originalPixmap = cell->pixmap(Qt::ReturnByValue);
        if (!originalPixmap.isNull()) {
            QPixmap tintedPixmap(originalPixmap.size());
            tintedPixmap.fill(Qt::transparent);

            QPainter painter(&tintedPixmap);
            painter.drawPixmap(0, 0, originalPixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
            painter.fillRect(tintedPixmap.rect(), QColor(0, 255, 0, 128));  // Green tint
            painter.end();

            cell->setPixmap(tintedPixmap);
        } else {
            cell->setStyleSheet("background-color: green; border: 1px solid gray;");
        }
    }
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

