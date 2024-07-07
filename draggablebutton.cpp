#include "DraggableButton.h"
#include "gamewindow.h"
#include <qtimer.h>
#include "ship.h"
#include <algorithm>
#include "globalVariables.h"
int rotateCounter = 0;

DraggableButton::DraggableButton(const QIcon& icon, Ship& ship, QWidget* parent)
    : QPushButton(parent), dragging(false), ship(ship), isRotated(false) {
    setIcon(icon);
    setIconSize(QSize(64, 64));  // Adjust size as needed
    initialPosition = pos();     // Store the initial position here
}

void DraggableButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Define the lower 30% region of the button
        int clickWidth = width();
        int clickHeight = height() * 0.3;
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

                // Move the button down based on ship length if rotated
                if (isRotated) {
                    int moveAmount = 0;
                    switch (ship.getLength()) {
                    case 1:  // Tiny ship
                        moveAmount = 10;
                        break;
                    case 2:  // Small ship
                        moveAmount = 20;
                        break;
                    case 3:  // Mid ship
                        moveAmount = 30;
                        break;
                    case 4:  // Large ship
                        moveAmount = 40;
                        break;
                    default:
                        moveAmount = 10;
                        break;
                    }
                    move(pos().x(), pos().y() + moveAmount);
                }

            } else {
                // If canDrag is false, reset to a specific position and allow dragging again
                move(700, 700);
                //qDebug() << "Initial position:" << initialPosition;

                canDrag = true;
            }
        } else {
            event->ignore();  // Ignore if outside the lower region
        }
    } else {
        event->ignore();  // Ignore other mouse events
    }
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

                    // Populate shipBlockCoordinates
                    for (int i = 0; i < ship.getLength(); ++i) {
                        int x = startX + (ship.getIsFlipped() ? 0 : i);
                        int y = startY - (ship.getIsFlipped() ? i : 0);
                        shipBlockCoordinates.append(QPoint(x, y));
                    }

                    setButtonEnabled(false); // Disable the button but maintain its appearance
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
        if(!isRotated)
        {
            isRotated = true;
            transform.rotate(90);
        }
        else
        {
            isRotated = false;
            transform.rotate(-90);
        }

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
        QPoint newPos = mapToParent(event->pos() - dragStartPosition);

        if (isRotated) {
            int moveAmount = 0;
            switch (ship.getLength()) {
            case 1:  // Tiny ship
                moveAmount = 35;
                break;
            case 2:  // Small ship
                moveAmount = 70;
                break;
            case 3:  // Mid ship
                moveAmount = 120;
                break;
            case 4:  // Large ship
                moveAmount = 170;
                break;
            default:
                moveAmount = 10;
                break;
            }
            newPos.setY(newPos.y() + moveAmount);  // Move down based on ship length
        }

        move(newPos);
        qDebug() << "Initial position:" << initialPosition;
        emit shipDragged();
    }
}

void DraggableButton::setButtonEnabled(bool enabled) {
    setEnabled(enabled);
    updateAppearance();
}

void DraggableButton::updateAppearance() {
    if (!isEnabled()) {
        setStyleSheet(
            "QPushButton {"
            "    border: none;"
            "    padding: 0;"
            "    background: transparent;"
            "    opacity: 1.0;"
            "    color: black;" // Ensure the text/icon color is set explicitly
            "}"
            );
    } else {
        setStyleSheet(
            "QPushButton {"
            "    border: none;"
            "    padding: 0;"
            "    background: transparent;"
            "    color: black;" // Ensure the text/icon color is set explicitly
            "}"
            );
    }
}
