#include "DraggableButton.h"
#include "gamewindow.h"
#include <qtimer.h>
#include "ship.h"
#include <algorithm>
int rotateCounter=0;
DraggableButton::DraggableButton(const QIcon& icon, Ship& ship, QWidget* parent)
    : QPushButton(parent), dragging(false), ship(ship) {
    setIcon(icon);
    setIconSize(QSize(64, 64));  // Adjust size as needed
    initialPosition = pos();     // Store the initial position here
}

void DraggableButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Define the lower 30% region of the button
        int clickWidth = width();
        int clickHeight = height() * 0.3;

        // Calculate the boundaries of the lower region
        int clickX = 0;
        int clickY = height() - clickHeight;

        QRect clickableRect(clickX, clickY, clickWidth, clickHeight);

        // Check if the click is within the lower region
        if (clickableRect.contains(event->pos())) {
            if (canDrag) {
                setWindowOpacity(0.5);  // Make semi-transparent
                dragging = true;
                dragStartPosition = event->pos();

                // Save initial position based on real screen coordinates
                int cellSizeX = 591.0f / 10;
                int cellSizeY = 591.0f / 10;
                initialPosition = QPoint(ship.getStartX() * cellSizeX + 80, ship.getStartY() * cellSizeY + 70);

                GameWindow* gameWindow = dynamic_cast<GameWindow*>(parent());
                if (gameWindow) {
                    gameWindow->setCurrentShip(ship);
                }
            } else {
                // If canDrag is false, reset to a specific position and allow dragging again
                move(700, 700);
                qDebug() << "Initial position:" << initialPosition;

                canDrag = true;
            }
        } else {
            event->ignore();  // Ignore if outside the lower region
        }
    } else {
        event->ignore();  // Ignore other mouse events
    }
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
    initializeFleet();

    qDebug() << "Game reset.";
}








void DraggableButton::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && dragging) {
        dragging = false;
        emit shipDragged();

        auto* gameWindow = dynamic_cast<GameWindow*>(parent());
        if (gameWindow) {
            QPoint globalPos = mapToParent(event->pos());
            int endX = globalPos.x();
            int endY = globalPos.y();

            int cellSizeX = 591.0f / 10;
            int cellSizeY = 591.0f / 10;
            int startX = (endX - 80) / cellSizeX;
            int startY = (endY - 70) / cellSizeY;

            if (gameWindow->isWithinGrid(startX, startY)) {
                Board& board = gameWindow->board;

                if (board.canPlaceShip(ship, startX, startY)) {
                    board.placeShip(ship, startX, startY);
                    canDrag = false;

                    int moveAmount = 0;
                    switch (ship.getLength()) {
                    case 1: moveAmount = 13; break;
                    case 2: moveAmount = -0.5; break;
                    case 3: moveAmount = 0; break;
                    case 4: moveAmount = -9; break;
                    default: moveAmount = 0;
                    }

                    int cellStartX = startX * cellSizeX + 80 + moveAmount;
                    int cellEndY = (startY + 1) * cellSizeY + 70;
                    move(cellStartX, cellEndY - height());
                    board.markAdjacentCellsUnavailable(startX, startY, ship.getLength(), ship.getIsFlipped());
                    ship.setStartX(startX);
                    ship.setStartY(startY);

                    setEnabled(false);
                } else {
                    gameWindow->resetGame(); // Reset the game if released outside
                }
            } else {
                gameWindow->resetGame(); // Reset the game if released outside
            }
        } else {
            move(initialPosition);
        }

        rotateCounter = 0; // Reset the rotate counter
        event->ignore();
    }
}




void DraggableButton::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_R && canDrag) {
        // Rotate the ship 90 degrees
        QSize currentSize = size();
        setFixedSize(currentSize.height(), currentSize.width());

        QPixmap pixmap = icon().pixmap(iconSize());
        QTransform transform;
        transform.rotate(90);
        pixmap = pixmap.transformed(transform);
        setIcon(QIcon(pixmap));

        // Toggle the isFlipped flag
        ship.setIsFlipped(!ship.getIsFlipped());
    }
}






void DraggableButton::setCurrentShipButton(DraggableButton* button) {
    currentShipButton = button;
}



void DraggableButton::mouseMoveEvent(QMouseEvent* event) {
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(mapToParent(event->pos() - dragStartPosition));
        qDebug() << "Initial position:" << initialPosition;
        //event not working for rotated ships
        emit shipDragged();
    }
}



