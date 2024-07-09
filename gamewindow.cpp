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
    player1Turn(true),isSecondPlayerSettingUp(false),
    player2Turn(false)
{
    ui->setupUi(this);
    initializeFleet();
    setupGridBackground();
    setupIcons();
    setupTable();

    connect(ui->nextButton, &QPushButton::clicked, this, &GameWindow::onNextButtonClicked);
    connect(this, &GameWindow::secondPlayerSetupComplete, this, &GameWindow::showPlayingWindow);

    // Initialize the ArsenalWindow
    arsenalWindow = new ArsenalWindow(this);
    connect(arsenalWindow, &ArsenalWindow::arsenalSelectionComplete, this, &GameWindow::onArsenalSelectionComplete);
}
void GameWindow::onArsenalSelectionComplete(int player, int oil, const QVector<ArsenalItem>& arsenal) {
    if (player == 1) {
        playerOneOil = oil;
        playerOneArsenal = arsenal;
    } else if (player == 2) {
        playerTwoOil = oil;
        playerTwoArsenal = arsenal;
    }

    if (modeChosen == 2 && player == 1) {
        qDebug() << "Player 1 completed arsenal selection, starting Player 2 setup";
        // Prepare for Player 2 setup
        board.reset(); // Reset the board
        Ship::resetIDCounter();
        // Hide Player 1's DraggableButtons
        for (auto button : findChildren<DraggableButton*>()) {
            button->hide();
        }
        // Reinitialize the fleet for Player 2
        initializeFleet();
        ui->statusLabel->setText("Second player, set up your board!");
        resetBlockColors();
    } else {
        // Proceed to the playing window
        showPlayingWindow();
    }
}
GameWindow::~GameWindow() {
    delete ui;
    delete playingWindow; // Clean up PlayingWindow
    delete myBoard;
    delete enemyBoard;
    delete arsenalWindow; // Clean up ArsenalWindow
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
            *myBoard = board;
            player1Board = board;
            playingWindow = new PlayingWindow(this, this, &board, enemyBoard, &themeManager);
        }

        // Debug: Verify ship placement on myBoard
        qDebug() << "Ship placement on myBoard before bot turn:";
        for (const auto& row : myBoard->getGrid()) {
            QString rowString;
            for (int cell : row) {
                rowString += QString::number(cell) + " ";
            }
            qDebug() << rowString;
        }

        // Show ArsenalWindow
        if (!arsenalWindow) {
            qDebug() << "Creating ArsenalWindow instance";
            arsenalWindow = new ArsenalWindow(this);
            arsenalWindow->setMode(modeChosen);
            arsenalWindow->setPlayer(1); // Set player 1
            arsenalWindow->setOil(playerOneOil);
        }

        this->hide(); // Hide the current window
        qDebug() << "GameWindow hidden";

        arsenalWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
        arsenalWindow->setWindowModality(Qt::WindowModal); // Ensure it is window modal
        arsenalWindow->show(); // Show the ArsenalWindow
        arsenalWindow->raise(); // Bring the ArsenalWindow to the top
        arsenalWindow->activateWindow(); // Focus the ArsenalWindow
        qDebug() << "ArsenalWindow for player 1 shown and activated";

        // Connect the start button to proceed to the PlayingWindow
        connect(arsenalWindow->getStartButton(), &QPushButton::clicked, this, [this]() {
            arsenalWindow->close();
            playingWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
            playingWindow->setWindowModality(Qt::NonModal); // Ensure it is non-modal
            playingWindow->show(); // Show the PlayingWindow
            playingWindow->raise(); // Bring the PlayingWindow to the top
            playingWindow->activateWindow(); // Focus the PlayingWindow
            qDebug() << "PlayingWindow shown and activated";

            // Trigger the bot's turn after the player has completed their setup
            QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn);
        });

    } else if (modeChosen == 2) { // 1vs1 mode
        if (isSecondPlayerSettingUp) {
            qDebug() << "Second player finished setting up";
            player2Board = board; // Store the second player's board in player2Board
            player1Board.resetUnavailableCells();
            player2Board.resetUnavailableCells();
            emit secondPlayerSetupComplete(); // Emit the signal when the second player is done

            // Show ArsenalWindow for player 2
            if (!arsenalWindow) {
                qDebug() << "Creating ArsenalWindow instance";
                arsenalWindow = new ArsenalWindow(this);
                arsenalWindow->setMode(modeChosen);
                arsenalWindow->setPlayer(2); // Set player 2
                arsenalWindow->setOil(playerTwoOil);
            } else {
                //arsenalWindow->resetArsenal(); // Reset the arsenal items for player 2
                arsenalWindow->setPlayer(2); // Ensure player 2 is set
                arsenalWindow->setOil(playerTwoOil); // Ensure oil is set correctly for player 2
            }

            this->hide(); // Hide the current window
            qDebug() << "GameWindow hidden";

            arsenalWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
            arsenalWindow->setWindowModality(Qt::WindowModal); // Ensure it is window modal
            arsenalWindow->show(); // Show the ArsenalWindow
            arsenalWindow->raise(); // Bring the ArsenalWindow to the top
            arsenalWindow->activateWindow(); // Focus the ArsenalWindow
            qDebug() << "ArsenalWindow for player 2 shown and activated";

            // Connect the start button to proceed to the PlayingWindow
            connect(arsenalWindow, &ArsenalWindow::arsenalSelectionComplete, this, [this](int player, int oil, const QVector<ArsenalItem>& arsenal) {
                if (player == 2) {
                    playerTwoOil = oil;
                    playerTwoArsenal = arsenal;
                    arsenalWindow->close();

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
                }
            });

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

            // Show ArsenalWindow for player 1
            if (!arsenalWindow) {
                qDebug() << "Creating ArsenalWindow instance";
                arsenalWindow = new ArsenalWindow(this);
                arsenalWindow->setMode(modeChosen);
                arsenalWindow->setPlayer(1); // Set player 1
                arsenalWindow->setOil(playerOneOil);
            } else {
                //arsenalWindow->resetArsenal(); // Reset the arsenal items for player 1
                arsenalWindow->setPlayer(1); // Ensure player 1 is set
                arsenalWindow->setOil(playerOneOil); // Ensure oil is set correctly for player 1
            }

            this->hide(); // Hide the current window
            qDebug() << "GameWindow hidden";

            arsenalWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
            arsenalWindow->setWindowModality(Qt::WindowModal); // Ensure it is window modal
            arsenalWindow->show(); // Show the ArsenalWindow
            arsenalWindow->raise(); // Bring the ArsenalWindow to the top
            arsenalWindow->activateWindow(); // Focus the ArsenalWindow
            qDebug() << "ArsenalWindow for player 1 shown and activated";

            // Connect the signal for arsenal selection completion
            connect(arsenalWindow, &ArsenalWindow::arsenalSelectionComplete, this, [this](int player, int oil, const QVector<ArsenalItem>& arsenal) {
                if (player == 1) {
                    playerOneOil = oil;
                    playerOneArsenal = arsenal;
                    arsenalWindow->close();

                    qDebug() << "Player 1 completed arsenal selection, starting Player 2 setup";
                    show();
                }
            });

            // Clear the grid background if necessary
            resetBlockColors();
        }
    }
}
void GameWindow::processAttack(int row, int col, Board* attackingBoard, Board* defendingBoard, int attackingPlayer) {
    int cellValue = defendingBoard->getGrid()[row][col];

    if (cellValue == 101) {
        // A mine was hit
        QMessageBox::information(this, "Don't hit yourself!", "Don't hit yourself!");

        // The attacking player's block in [row][col] is affected
        attackingBoard->getGrid()[row][col] = -1; // Mark the cell to indicate it's been hit
        qDebug() << "Player" << attackingPlayer << "hit a mine at (" << row << "," << col << ") and affected their own board.";

        // Print the attacking board for debugging
        qDebug() << "Attacking Player Board after hitting a mine:";
        for (const auto& rowVec : attackingBoard->getGrid()) {
            QString rowString;
            for (int cell : rowVec) {
                rowString += QString::number(cell) + " ";
            }
            qDebug() << rowString;
        }

    } else {
        // Handle regular attack logic
        if (cellValue > 0) {
            // Hit a ship
            defendingBoard->getGrid()[row][col] = -1; // Mark the cell as hit
            qDebug() << "Player" << attackingPlayer << "hit a ship at (" << row << "," << col << ").";

            // Add logic for checking if the ship is sunk, game over, etc.
        } else {
            // Missed attack
            defendingBoard->getGrid()[row][col] = -1; // Mark the cell as miss
            qDebug() << "Player" << attackingPlayer << "missed at (" << row << "," << col << ").";
        }
    }

    // Add any additional logic for updating UI, switching turns, etc.
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

int GameWindow::getPlayerOneOil() const {
    return playerOneOil;
}

void GameWindow::setPlayerOneOil(int oil) {
    playerOneOil = oil;
}

int GameWindow::getPlayerTwoOil() const {
    return playerTwoOil;
}

void GameWindow::setPlayerTwoOil(int oil) {
    playerTwoOil = oil;
}

QVector<ArsenalItem>& GameWindow::getPlayerOneArsenal() {
    return playerOneArsenal;
}

QVector<ArsenalItem>& GameWindow::getPlayerTwoArsenal() {
    return playerTwoArsenal;
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
                qDebug() << "Marking missed block with cross.";
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
                qDebug() << "Marking hit block with cross.";
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
                        qDebug() << "Ship is sunk.";
                        playingWindow->clearShipBlockCrosses(shipID, "myBoard");
                        playingWindow->makeShipBlocksPurple(shipID, "myBoard");
                    }
                }
                qDebug() << "Bot hit a ship. Bot gets another turn.";
                // Bot gets another turn if it hits a ship
                QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn);
            } else if (result == -2) { // Ship sunk
                qDebug() << "Marking sunk ship blocks.";
                int shipID = -myBoard->getCell(selectedRow, selectedCol);
                playingWindow->makeShipBlocksPurple(shipID, "myBoard");
                qDebug() << "Bot sunk the ship. Bot gets another turn.";
                QTimer::singleShot(1000, this, &GameWindow::triggerBotTurn); // Bot gets another turn if it sinks a ship
            } else if (result == -3) { // All ships sunk
                qDebug() << "All ships sunk. Checking for any remaining positive values.";

                // Check if there are any positive numbers in myBoard
                bool hasPositive = false;
                for (const auto& row : myBoard->getGrid()) {
                    for (int cell : row) {
                        if (cell > 0) {
                            hasPositive = true;
                            break;
                        }
                    }
                    if (hasPositive) {
                        break;
                    }
                }

                // Show lose window if no positive numbers are found
                if (!hasPositive) {
                    qDebug() << "No positive values found. Player loses.";
                    playingWindow->showLoseWindow(); // Show lose window when player loses
                } else {
                    qDebug() << "Positive values found. Game continues.";
                }
            } else {
                qDebug() << "Bot's turn ended. Switching to player 1's turn.";
                player1Turn = true;
                player2Turn = false; // Switch back to player's turn
            }
        }
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
            cell->setStyleSheet("border:1px solid gray; background: transparent;");
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


void GameWindow::handleArsenalSelectionComplete(int player, int remainingOil, const QVector<ArsenalItem>& selectedArsenal) {
    qDebug() << "Arsenal selection complete for player:" << player;
    qDebug() << "Remaining oil:" << remainingOil;
    for (const ArsenalItem& item : selectedArsenal) {
        qDebug() << "Arsenal item purchased:" << item.purchased << "/" << item.limit << "cost:" << item.oilCost;
    }

    // Update the corresponding player's oil and arsenal
    if (player == 1) {
        playerOneOil = remainingOil;
        playerOneArsenal = selectedArsenal;

        // Start Player 2's setup
        qDebug() << "Player 1 completed arsenal selection, starting Player 2 setup";
        player2Board.reset(); // Reset the board for Player 2 setup
        Ship::resetIDCounter();

        // Clear Player 1's DraggableButtons
        for (auto button : findChildren<DraggableButton*>()) {
            button->hide();
        }

        // Reinitialize the fleet for Player 2
        initializeFleet();

        // Show a message or update UI to indicate it's the second player's turn
        ui->statusLabel->setText("Second player, set up your board!");
        resetBlockColors();

        isSecondPlayerSettingUp = true;

        this->show(); // Show the GameWindow for Player 2 to set up their board
        return; // Exit the function to wait for Player 2 to complete their setup
    } else if (player == 2) {
        playerTwoOil = remainingOil;
        playerTwoArsenal = selectedArsenal;

        // Proceed to the PlayingWindow
        if (!playingWindow) {
            qDebug() << "Creating PlayingWindow instance";
            playingWindow = new PlayingWindow(this, this, &player1Board, &player2Board, &themeManager);
        }

        playingWindow->setWindowFlags(Qt::Window);
        playingWindow->setWindowModality(Qt::NonModal);
        playingWindow->show();
        playingWindow->raise();
        playingWindow->activateWindow();
        qDebug() << "PlayingWindow shown and activated";
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

void GameWindow::resetGame() {
    // Clear the board
    for (auto& row : board.getGrid()) {
        for (auto& cell : row) {
            cell = 0;  // Set each cell to 0
        }
    }

    // Delete existing ships and buttons
    qDeleteAll(ships);
    ships.clear();

    for (auto button : findChildren<DraggableButton*>()) {
        button->deleteLater();
    }

    // Reinitialize the fleet
    Ship::resetIDCounter();
    initializeFleet();
    shipBlockCoordinates.clear();
    qDebug() << "Game reset.";
}






