#ifndef DRAGGABLEBUTTON_H
#define DRAGGABLEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include "ship.h"
class DraggableButton : public QPushButton {
    Q_OBJECT

public:
    explicit DraggableButton(const QIcon& icon, QWidget* parent = nullptr);


public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    DraggableButton(const QIcon& icon, Ship& ship, QWidget* parent);
    void setCurrentShipButton(DraggableButton* button);
    bool canDrag = true;
private:
    bool dragging;
    QPoint dragStartPosition;
     Ship& ship;
     DraggableButton* currentShipButton;

signals:
    void shipDragged();
};

#endif // DRAGGABLEBUTTON_H
