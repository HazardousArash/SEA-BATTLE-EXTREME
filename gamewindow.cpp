#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "DraggableButton.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QIcon>
#include "ship.h"
#include "Board.h"
#include <vector>
#include "releasablelabel.h"
#include <QDebug>
#include <QTimer>
#include <set>
#include <algorithm>
#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "PlayingWindow.h"
#include "GameWindow.h"
#include "ui_GameWindow.h"
#include <QDebug>
#include "thememanager.h"
#include <QTimer>
int initialX = 50;
int initialY = 50;
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::GameWindow),
    playingWindow(nullptr),
    myBoard(new Board()),  // Initialize myBoard
    enemyBoard(new Board()),
    player1Turn(true),
    player2Turn(false) {
    ui->setupUi(this);
    initializeFleet();
    setupGridBackground();
    setupIcons();
    setupTable();

    connect(ui->nextButton, &QPushButton::clicked, this, &GameWindow::onNextButtonClicked);
    connect(this, &GameWindow::secondPlayerSetupComplete, this, &GameWindow::showPlayingWindow);
}





GameWindow::~GameWindow() {
    delete ui;
    delete playingWindow; // Clean up PlayingWindow
    delete myBoard;
    delete enemyBoard;
}

bool GameWindow::areAllShipsPlaced() {
    // std::set<int> placedShipIDs;
    // for (const auto& row : board.getGrid()) {
    //     for (int cell : row) {
    //         if (cell > 0) {
    //             placedShipIDs.insert(cell);
    //         }
    //     }
    // }
    // // Check if we have exactly 10 unique ship IDs
    // return placedShipIDs.size() == 10;
    return true; // Temporarily return true to bypass ship placement check
}

void GameWindow::onNextButtonClicked() {
    qDebug() << "Next button clicked";

    if (!areAllShipsPlaced()) {
        QMessageBox::warning(this, "Error", "You must place all 10 ships before proceeding!");
        return;
    }

    static bool isSecondPlayerSettingUp = false;

    if (modeChosen == 1) { // Versus Bot
        if (!playingWindow) {
            qDebug() << "Creating PlayingWindow instance for Versus Bot mode";

            // Create and shuffle the enemy board for bot mode
            Board* enemyBoard = new Board();
            enemyBoard->shuffleBoard();
            board.resetUnavailableCells();

            playingWindow = new PlayingWindow(this, this, &board, enemyBoard, &themeManager);
        }

        this->hide(); // Hide the current window
        qDebug() << "GameWindow hidden";

        playingWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
        playingWindow->setWindowModality(Qt::NonModal); // Ensure it is non-modal
        playingWindow->show(); // Show the PlayingWindow
        playingWindow->raise(); // Bring the PlayingWindow to the top
        playingWindow->activateWindow(); // Focus the PlayingWindow
        qDebug() << "PlayingWindow shown and activated";

        // Trigger the bot's turn after the player has completed their setup
        QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn);
    } else if (modeChosen == 2) { // 1vs1 mode
        if (isSecondPlayerSettingUp) {
            // If this is the second player's turn to set up
            qDebug() << "Second player finished setting up";
            player2Board = board; // Store the second player's board in player2Board
            player1Board.resetUnavailableCells();
            player2Board.resetUnavailableCells();
            emit secondPlayerSetupComplete(); // Emit the signal when the second player is done

            this->hide(); // Hide the current window
            qDebug() << "GameWindow hidden";

            if (!playingWindow) {
                qDebug() << "Creating PlayingWindow instance for 1vs1 mode";
                playingWindow = new PlayingWindow(this, this, &player1Board, &player2Board, &themeManager);
            }

            playingWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
            playingWindow->setWindowModality(Qt::NonModal); // Ensure it is non-modal
            playingWindow->show(); // Show the PlayingWindow
            playingWindow->raise(); // Bring the PlayingWindow to the top
            playingWindow->activateWindow(); // Focus the PlayingWindow
            qDebug() << "PlayingWindow shown and activated";
        } else {
            qDebug() << "Player 1 finished setting up";
            player1Board = board; // Store the first player's board in player1Board

            // Clear the current board for the second player
            board.reset(); // Reset the board
            Ship::resetIDCounter();

            // Remove Player 1's DraggableButtons
            for (auto button : findChildren<DraggableButton*>()) {
                button->hide();
            }

            // Reinitialize the fleet for the second player
            initializeFleet();

            isSecondPlayerSettingUp = true;

            // Show a message or update UI to indicate it's the second player's turn
            ui->statusLabel->setText("Second player, set up your board!");

            // Clear the grid background if necessary
            resetBlockColors();
        }
    }
}
void GameWindow::triggerBotTurn() {
    if (modeChosen == 1) { // Versus Bot mode
        qDebug() << "Bot's turn to play.";

        // Debug: Check myBoard state before bot's turn
        qDebug() << "Before bot's turn, myBoard state:";
        for (const auto& row : myBoard->getGrid()) {
            QString rowString;
            for (int cell : row) {
                rowString += QString::number(cell) + " ";
            }
            qDebug() << rowString;
        }

        // Call the bot's AI function to make a move
        int selectedRow, selectedCol;
        int result = enemyBoard->botAi(*myBoard, selectedRow, selectedCol); // Use myBoard directly

        // Debug: Check the selected cell and result
        qDebug() << "Bot selected (" << selectedRow << ", " << selectedCol << "), result: " << result;

        // Update the playing window to reflect the bot's move
        if (playingWindow) {
            playingWindow->updateGridWithBoardState(myBoard, "myBoard"); // Use myBoard directly

            // Debug: Check myBoard state after update
            qDebug() << "After updateGridWithBoardState, myBoard state:";
            for (const auto& row : myBoard->getGrid()) {
                QString rowString;
                for (int cell : row) {
                    rowString += QString::number(cell) + " ";
                }
                qDebug() << rowString;
            }

            if (result == -1) { // Miss
                playingWindow->markSingleShipBlockWithCross(selectedRow, selectedCol, "myBoard");
                ClickableLabel* cell = playingWindow->findChild<ClickableLabel*>(QString("cell_%1_%2").arg(selectedRow).arg(selectedCol));
                if (cell) {
                    cell->setStyleSheet("background: rgba(255, 0, 0, 0.5); border: 1px solid gray;"); // Glassy red
                    cell->setEnabled(false); // Make it unclickable
                }
                qDebug() << "Bot missed. Switching to player 1's turn.";
                player1Turn = true;
                player2Turn = false; // Switch back to player's turn
            } else if (result == 1) { // Hit
                int shipID = -myBoard->getCell(selectedRow, selectedCol);
                qDebug() << "Bot hit ship part. Ship ID: " << shipID;
                Ship* ship = Ship::getShipByID(shipID);
                if (ship) {
                    ship->decrementHitPoints();
                    playingWindow->markSingleShipBlockWithCross(selectedRow, selectedCol, "myBoard");
                    ClickableLabel* cell = playingWindow->findChild<ClickableLabel*>(QString("cell_%1_%2").arg(selectedRow).arg(selectedCol));
                    if (cell) {
                        cell->setEnabled(false); // Make it unclickable
                    }

                    if (ship->getHitPoints() == 0) {
                        playingWindow->clearShipBlockCrosses(shipID, "myBoard");
                        playingWindow->makeShipBlocksPurple(shipID, "myBoard");
                    }
                }
                qDebug() << "Bot hit a ship. Bot gets another turn.";
                // Bot gets another turn if it hits a ship
                QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn);
            } else if (result == -2) { // Ship sunk
                int shipID = -myBoard->getCell(selectedRow, selectedCol);
                playingWindow->makeShipBlocksPurple(shipID, "myBoard");
                qDebug() << "Bot sunk the ship. Bot gets another turn.";
                QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn); // Bot gets another turn if it sinks a ship
            } else {
                qDebug() << "Bot's turn ended. Switching to player 1's turn.";
                player1Turn = true;
                player2Turn = false; // Switch back to player's turn
            }
        }
    }
}






void GameWindow::showPlayingWindow() {
    if (playingWindow) {
        qDebug() << "Attempting to show PlayingWindow.";
        this->hide(); // Hide GameWindow
        playingWindow->setWindowFlags(Qt::Window | Qt::MSWindowsOwnDC);
        playingWindow->show();
        playingWindow->raise(); // Ensure PlayingWindow is brought to the front
        playingWindow->activateWindow(); // Ensure PlayingWindow gets focus
        qDebug() << "PlayingWindow visibility:" << playingWindow->isVisible();
    } else {
        qDebug() << "PlayingWindow is not initialized.";
    }
}
void GameWindow::contextMenuEvent(QContextMenuEvent* event) {
    Q_UNUSED(event);
    qDebug() << "Board state:";
    for (const auto& row : board.getGrid()) {  // Assuming getGrid() returns the 2D vector
        QString rowString;
        for (int cell : row) {
            rowString += QString::number(cell) + " ";
        }
        qDebug() << rowString;
    }
}

void GameWindow::setupGridBackground() {
    QPixmap gridBackground = themeManager.getIcon("paperGrid");
    ui->gridBackgroundLabel->setPixmap(gridBackground);
    ui->gridBackgroundLabel->setScaledContents(true);

    int gridSize = 10;
    float cellSizeX = 591.0f / gridSize;
    float cellSizeY = 591.0f / gridSize;

    labelGrid.resize(gridSize, QVector<QLabel*>(gridSize, nullptr));

    for (int j = 0; j < gridSize; ++j) {  // Loop for rows
        for (int i = 0; i < gridSize; ++i) {  // Loop for columns
            ReleasableLabel* cell = new ReleasableLabel(ui->gridBackgroundLabel);
            cell->setGeometry(static_cast<int>(-2+ i * cellSizeX), static_cast<int>(j * cellSizeY),
                              static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
            cell->setStyleSheet("border: none; background: transparent;");
            cell->setObjectName(QString("cell_%1_%2").arg(j).arg(i));  // Swapped i and j
            cell->installEventFilter(this);
            cell->setMouseTracking(true);  // Enable mouse tracking
            cell->show();
            labelGrid[j][i] = cell;  // Swapped i and j

            connect(cell, &ReleasableLabel::mouseReleased, this, [this, j, i]() {  // Swapped i and j
                qDebug() << "Clicked cell at coordinates:" << j << i;

            });
        }
    }
}





void GameWindow::handleShipDrop(DraggableButton* button) {
    QPoint pos = button->pos();
    int gridSize = 10;
    int cellSizeX = 591 / gridSize;
    int cellSizeY = 591 / gridSize;
    int x=0,y=0;
    qDebug()<< "hey";
    switch (currentShip.getLength())
    {
    case 1:
         x = qBound(0, pos.x() / cellSizeX, gridSize);
         y = qBound(0, pos.y() / cellSizeY, gridSize );
        break;
    case 2:
         x = qBound(0, pos.x() / cellSizeX, gridSize );
         y = qBound(0, pos.y() / cellSizeY, gridSize );
        break;
    case 3:
         x = qBound(0, pos.x() / cellSizeX, gridSize );
         y = qBound(0, pos.y() / cellSizeY, gridSize );
        break;
    case 4:
         x = qBound(0, pos.x() / cellSizeX, gridSize );
         y = qBound(0, pos.y() / cellSizeY, gridSize );
        break;
    }

    int moveX = 0, moveY = 0;

    switch (currentShip.getLength())
    {
    case 1:  // Tiny ships
        moveX = 35;
        moveY = 17.5;
        break;
    case 2:  // Small ships
        moveX = 0;
        moveY = 0;
        break;
    case 3:  // Mid ships
        moveX = 0;
        moveY = 0;
        break;
    case 4:  // Large ships
        moveX = 0;
        moveY = 0;
        break;
    }

    int adjustedX = qBound(0, x * cellSizeX + moveX, 591 - cellSizeX);
    int adjustedY = qBound(0, y * cellSizeY + moveY, 591 - cellSizeY);

    button->move(adjustedX, adjustedY);

    placeShipOnBoard(x, y);
}



void GameWindow::placeShipOnBoard(int startX, int startY) {
    int gridSize = 10;
    float cellSizeX = 591.0f / gridSize;
    float cellSizeY = 591.0f / gridSize;

    // Convert coordinates to grid indices
    int gridX = (startX + 2) / cellSizeX;  // Adjusting based on setupGridBackground logic
    int gridY = startY / cellSizeY;

    if (isWithinGrid(gridX, gridY)) {
        int length = currentShip.getLength();
        bool isFlipped = currentShip.getIsFlipped();

        int shipStartX = gridX;
        int shipStartY = gridY;

        if (isFlipped) {
            shipStartY = gridY - length + 1;
        } else {
            shipStartX = gridX - length + 1;
        }

        // Ensure starting positions are within bounds
        shipStartX = qBound(0, shipStartX, gridSize - 1);
        shipStartY = qBound(0, shipStartY, gridSize - 1);

        if (board.canPlaceShip(currentShip, shipStartX, shipStartY)) {
            board.placeShip(currentShip, shipStartY, shipStartX);
            board.markAdjacentCellsUnavailable(shipStartX, shipStartY, length, isFlipped);
            qDebug() << "Ship placed successfully";
            highlightAvailableBlocks();
            resetBlockColors();
        } else {
            qDebug() << "Failed to place ship";
        }
    } else {
        qDebug() << "Position out of bounds";
    }
}

void GameWindow::clearBoardUI() {
    for (int j = 0; j < labelGrid.size(); ++j) {
        for (int i = 0; i < labelGrid[j].size(); ++i) {
            if (labelGrid[j][i]) {
                labelGrid[j][i]->clear();
                labelGrid[j][i]->setStyleSheet("border: none; background: transparent;");
            }
        }
    }
}


bool GameWindow::isWithinGrid(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}



void GameWindow::setCurrentShip(const Ship& ship) {
    currentShip = ship;
    qDebug() << "Ship selected with ID:" << currentShip.getID();  // Debug message
}



void GameWindow::initializeFleet() {
    int spacing = 10;
    std::vector<Ship*> ships;

    // Create tiny ships
    for (int i = 0; i < 4; ++i) {
        Ship* tinyShip = new Ship(1);
        ships.push_back(tinyShip);
        DraggableButton* button = addDraggableButton("tinyShip", *tinyShip, 1085 + i * (25 + spacing), 67.5, 55, 30, 6.25);
        connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
        button->canDrag = true; // Allow dragging initially
        //button->setStyleSheet("border: 2px solid red;");
    }

    // Create small ships
    for (int i = 0; i < 3; ++i) {
        Ship* smallShip = new Ship(2);
        ships.push_back(smallShip);
        DraggableButton* button = addDraggableButton("smallShip", *smallShip, 1080 + i * (40 + spacing), 130, 128, 70, 30);
        connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
        button->canDrag = true; // Allow dragging initially
        //button->setStyleSheet("border: 2px solid red;");
    }

    // Create mid ships
    for (int i = 0; i < 2; ++i) {
        Ship* midShip = new Ship(3);
        ships.push_back(midShip);
        DraggableButton* button = addDraggableButton("midShip", *midShip, 1185 - i * (40 + spacing), 235, 256, 200, 75);
        connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
        button->canDrag = true; // Allow dragging initially
        //button->setStyleSheet("border: 2px solid red;");
    }

    // Create large ship
    Ship* largeShip = new Ship(4);
    ships.push_back(largeShip);
    DraggableButton* button = addDraggableButton("largeShip", *largeShip, 1180, 430, 220, 145, 8);
    connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
    button->canDrag = true; // Allow dragging initially
    //button->setStyleSheet("border: 2px solid red;");
}





bool GameWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Enter && isDraggingShip) {
        QLabel* cell = qobject_cast<QLabel*>(obj);
        if (cell) {
            highlightAvailableBlocks();

          //  int cellSize = 591/10;
           // int x = (cell->x() - 80) / cellSize;
            //int y = (cell->y() - 70) / cellSize;
           // qDebug() << "cellX=" << cell->x();
            //qDebug() << "cellY=" << cell->y();

            // Check if the ship can be placed without actually placing it
            //if (board.canPlaceShip(currentShip, x, y)) {
                //cell->setStyleSheet("background: green;");
            //} else {
                //cell->setStyleSheet("background: red;");
            //}
        //}
        return true;  // Event handled
    }
    return false;  // Event not handled, pass it on
}
}



void GameWindow::setupIcons() {
    ui->backButton->setIcon(QIcon(themeManager.getIcon("back")));
    ui->nextButton->setIcon(QIcon(themeManager.getIcon("next")));
    connect(ui->nextButton, &QPushButton::clicked, this, &GameWindow::showPlayingWindow);
}

void GameWindow::setupTable() {
    QPixmap tableIcon = themeManager.getIcon("table");
    ui->tableLabel->setPixmap(tableIcon);
    ui->tableLabel->setScaledContents(true);
}

QString GameWindow::getShipIconName(int length) {
    switch (length) {
    case 4: return "largeShip";
    case 3: return "midShip";
    case 2: return "smallShip";
    case 1: return "tinyShip";
    default: return "";
    }
}





DraggableButton* GameWindow::addDraggableButton(const QString& iconName, Ship& ship, int x, int y, int size, int subtractionX, int subtractionY){
    int buttonWidth = size - subtractionX;
    int buttonHeight = size - subtractionY;

    DraggableButton* button = new DraggableButton(QIcon(themeManager.getIcon(iconName)), ship, this);
    button->setGeometry(x, y, buttonWidth, buttonHeight);
    button->setIconSize(QSize(size, size));
    button->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    padding: 0;"
        "    background: transparent;"
        "}"
        "QPushButton:pressed {"
        "    background: transparent;"
        "}"
        );
    button->show();
    return button;
}

void GameWindow::highlightAvailableBlocks() {
    int gridSize = 10;

    for (int i = 0; i < gridSize; ++i) {
        for (int j= 0; j < gridSize; ++j) {
            QLabel* cell = labelGrid[i][j];

            if (cell) {
                if (board.getCell(i, j) == 0) {
                    cell->setStyleSheet("background: rgba(0, 255, 0, 0.5); border: 1px solid gray;");
                } else {
                    cell->setStyleSheet("background: rgba(255, 0, 0, 0.5); border: 1px solid gray;");
                }
            }
        }
    }
}

void GameWindow::resetBlockColors() {
    int gridSize = 10;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            QLabel* cell = labelGrid[i][j];
            if (cell) {
                cell->setStyleSheet("background: transparent; border: none;");
            }
        }
    }
}

void GameWindow::switchToTheme1() {
    themeManager.setTheme(1);
    setupGridBackground();
    setupIcons();
    setupTable();
}

void GameWindow::switchToTheme2() {
    themeManager.setTheme(2);
    setupGridBackground();
    setupIcons();
    setupTable();
}






