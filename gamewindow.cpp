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
int initialX = 50;
int initialY = 50;

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    themeManager(),
    isDraggingShip(false)
{
    ui->setupUi(this);
     initializeFleet();
    setupGridBackground();
    setupIcons();
    setupTable();

}

GameWindow::~GameWindow() {
    delete ui;
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
            cell->setGeometry(static_cast<int>(-3 + i * cellSizeX), static_cast<int>(j * cellSizeY),
                              static_cast<int>(cellSizeX), static_cast<int>(cellSizeY));
            cell->setStyleSheet("border: 1px solid gray; background: transparent;");
            cell->setObjectName(QString("cell_%1_%2").arg(j).arg(i));  // Swapped i and j
            cell->installEventFilter(this);
            cell->setMouseTracking(true);  // Enable mouse tracking
            cell->show();
            labelGrid[j][i] = cell;  // Swapped i and j

            connect(cell, &ReleasableLabel::mouseReleased, this, [this, j, i]() {  // Swapped i and j
                qDebug() << "Clicked cell at coordinates:" << j << i;
                placeShipOnBoard(j, i);
            });
        }
    }
}





void GameWindow::handleShipDrop(DraggableButton* button) {
    QPoint pos = button->pos();
    int gridSize = 10;
    int cellSizeX = 591 / gridSize;
    int cellSizeY = 591 / gridSize;
    int x,y;
    switch (currentShip.getLength())
    {
    case 1:
         x = qBound(0, pos.x() / cellSizeX, gridSize-1);
         y = qBound(1, pos.y() / cellSizeY, gridSize - 1);
        break;
    case 2:
         x = qBound(0, pos.x() / cellSizeX, gridSize - 1);
         y = qBound(1, pos.y() / cellSizeY, gridSize - 1);
        break;
    case 3:
         x = qBound(0, pos.x() / cellSizeX, gridSize - 1);
         y = qBound(1, pos.y() / cellSizeY, gridSize - 1);
        break;
    case 4:
         x = qBound(0, pos.x() / cellSizeX, gridSize - 1);
         y = qBound(1, pos.y() / cellSizeY, gridSize - 1);
        break;
    }

    int moveX = 0, moveY = 0;

    switch (currentShip.getLength())
    {
    case 1:  // Tiny ships
        moveX = 35;
        moveY = 10;
        break;
    case 2:  // Small ships
        moveX = 20;
        moveY = 15;
        break;
    case 3:  // Mid ships
        moveX = 15;
        moveY = 0;
        break;
    case 4:  // Large ships
        moveX = 10;
        moveY = 15;
        break;
    }

    int adjustedX = qBound(0, x * cellSizeX + moveX, 591 - cellSizeX);
    int adjustedY = qBound(0, y * cellSizeY + moveY, 591 - cellSizeY);

    button->move(adjustedX, adjustedY);

    placeShipOnBoard(x, y);
}



void GameWindow::placeShipOnBoard(int startX, int startY) {
    int length = currentShip.getLength();
    bool isFlipped = currentShip.getIsFlipped();

    int maxIndex = 11 - (isFlipped ? 1 : length);  // Increase max index by one
    int adjustedX = qBound(0, startX - (isFlipped ? 0 : length - 1), maxIndex);
    int adjustedY = qBound(0, startY - (isFlipped ? length - 1 : 0), maxIndex);

    if (board.placeShip(currentShip, adjustedX, adjustedY)) {
        board.markAdjacentCellsUnavailable(adjustedX, adjustedY, length, isFlipped);
        highlightAvailableBlocks();
    } else {
        qDebug() << "Failed to place ship at" << adjustedX << adjustedY;
    }
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
        button->setStyleSheet("border: 2px solid red;");
    }

    // Create small ships
    for (int i = 0; i < 3; ++i) {
        Ship* smallShip = new Ship(2);
        ships.push_back(smallShip);
        DraggableButton* button = addDraggableButton("smallShip", *smallShip, 1080 + i * (40 + spacing), 130, 128, 70, 30);
        connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
        button->canDrag = true; // Allow dragging initially
        button->setStyleSheet("border: 2px solid red;");
    }

    // Create mid ships
    for (int i = 0; i < 2; ++i) {
        Ship* midShip = new Ship(3);
        ships.push_back(midShip);
        DraggableButton* button = addDraggableButton("midShip", *midShip, 1185 - i * (40 + spacing), 235, 256, 200, 75);
        connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
        button->canDrag = true; // Allow dragging initially
        button->setStyleSheet("border: 2px solid red;");
    }

    // Create large ship
    Ship* largeShip = new Ship(4);
    ships.push_back(largeShip);
    DraggableButton* button = addDraggableButton("largeShip", *largeShip, 1180, 430, 220, 145, 8);
    connect(button, &DraggableButton::shipDragged, this, &GameWindow::highlightAvailableBlocks);
    button->canDrag = true; // Allow dragging initially
    button->setStyleSheet("border: 2px solid red;");
}





bool GameWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Enter && isDraggingShip) {
        QLabel* cell = qobject_cast<QLabel*>(obj);
        if (cell) {
            highlightAvailableBlocks();
            int x = (cell->x() - 80) / (591 / 10);
            int y = (cell->y() - 70) / (591 / 10);

            bool canPlace = board.placeShip(currentShip, x, y);
            if (canPlace) {
                cell->setStyleSheet("background: green;");
            } else {
                cell->setStyleSheet("background: red;");
            }
        }
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void GameWindow::setupIcons() {
    ui->backButton->setIcon(QIcon(themeManager.getIcon("back")));
    ui->nextButton->setIcon(QIcon(themeManager.getIcon("next")));
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
        for (int j = 0; j < gridSize; ++j) {
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

