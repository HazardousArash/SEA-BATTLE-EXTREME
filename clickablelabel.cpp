#include "ClickableLabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent), row(-1), col(-1) {
}

ClickableLabel::~ClickableLabel() {
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked(row, col);
    }
    QLabel::mousePressEvent(event);
}

void ClickableLabel::setRowCol(int row, int col) {
    this->row = row;
    this->col = col;
}
