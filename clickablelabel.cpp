#include "ClickableLabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent), row(-1), col(-1) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // Ensure the size is fixed
}

ClickableLabel::~ClickableLabel() {
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked(row, col);
    }
    event->ignore(); // Ignore the event to prevent any default behavior
}

void ClickableLabel::setRowCol(int row, int col) {
    this->row = row;
    this->col = col;
}
