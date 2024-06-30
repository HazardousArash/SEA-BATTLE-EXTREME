#include "DraggableButton.h"
#include "gamewindow.h"

DraggableButton::DraggableButton(const QIcon& icon, Ship& ship, QWidget* parent)
    : QPushButton(parent), dragging(false), ship(ship) {
    setIcon(icon);
    setIconSize(QSize(64, 64));  // Adjust size as needed
}

void DraggableButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && canDrag) {
        setWindowOpacity(0.5);  // Make semi-transparent
        // or use: setZValue(1);  // Lower z-order if applicable
        dragging = true;
        dragStartPosition = event->pos();

        GameWindow* gameWindow = dynamic_cast<GameWindow*>(parent());
        if (gameWindow) {
            gameWindow->setCurrentShip(ship);
        }
    }
}

// Ensure this is defined only once in DraggableButton.cpp
void DraggableButton::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1.0);
        dragging = false;

        emit shipDragged();

        auto* gameWindow = dynamic_cast<GameWindow*>(parent());
        if (gameWindow) {
            gameWindow->handleShipDrop(this);
        }

        // Pass the event to the parent to allow detection on underlying labels
        event->ignore();
    }
}

void DraggableButton::setCurrentShipButton(DraggableButton* button) {
    currentShipButton = button;
}



void DraggableButton::mouseMoveEvent(QMouseEvent* event) {
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(mapToParent(event->pos() - dragStartPosition));
        emit shipDragged();
    }
}



