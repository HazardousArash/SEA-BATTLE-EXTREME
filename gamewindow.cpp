#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "DraggableButton.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QIcon>
#include "ship.h"
#include "board.h"
#include <vector>
#include "releasablelabel.h"
#include <qdebug.h>
#include <QTimer>
int initialX = 50;
int initialY = 50;
#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "PlayingWindow.h"

#include "GameWindow.h"
#include "ui_GameWindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    playingWindow(nullptr) { // Initialize PlayingWindow to nullptr

    qDebug() << "GameWindow constructor started";

    ui->setupUi(this);
    qDebug() << "UI setup completed";

    initializeFleet();
    qDebug() << "Fleet initialized";

    setupGridBackground();
    qDebug() << "Grid background setup completed";

    setupIcons();
    qDebug() << "Icons setup completed";

    setupTable();
    qDebug() << "Table setup completed";

    connect(ui->nextButton, &QPushButton::clicked, this, &GameWindow::onNextButtonClicked);
    qDebug() << "Next button connected";
}

GameWindow::~GameWindow() {
    qDebug() << "GameWindow destructor started";

    delete ui;
    qDebug() << "UI deleted";

    delete playingWindow; // Clean up PlayingWindow
    qDebug() << "PlayingWindow deleted";
}

void GameWindow::onNextButtonClicked() {
    qDebug() << "Next button clicked";

    if (!playingWindow) {
        qDebug() << "Creating PlayingWindow instance";
        playingWindow = new PlayingWindow(this, &board, &themeManager);
    }

    this->hide(); // Hide the current window
    qDebug() << "GameWindow hidden";

    playingWindow->setWindowFlags(Qt::Window); // Ensure it has window flags set correctly
    playingWindow->setWindowModality(Qt::NonModal); // Ensure it is non-modal
    playingWindow->show(); // Show the PlayingWindow
    playingWindow->raise(); // Bring the PlayingWindow to the top
    playingWindow->activateWindow(); // Focus the PlayingWindow
    qDebug() << "PlayingWindow shown and activated";
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
            cell->setStyleSheet("border: 1px solid gray; background: transparent;");
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

            int cellSize = 591/10;
            int x = (cell->x() - 80) / cellSize;
            int y = (cell->y() - 70) / cellSize;
            qDebug() << "cellX=" << cell->x();
            qDebug() << "cellY=" << cell->y();

            // Check if the ship can be placed without actually placing it
            if (board.canPlaceShip(currentShip, x, y)) {
                cell->setStyleSheet("background: green;");
            } else {
                cell->setStyleSheet("background: red;");
            }
        }
        return true;  // Event handled
    }
    return false;  // Event not handled, pass it on
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
                cell->setStyleSheet("background: transparent; border: 1px solid gray;");
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






