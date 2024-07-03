#ifndef RELEASABLELABEL_H
#define RELEASABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ReleasableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ReleasableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void mouseReleased();  // Custom signal for mouse release
    void mousePressed();   // Custom signal for mouse press

protected:
    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit mouseReleased();
        }
        QLabel::mouseReleaseEvent(event); // Call base class implementation
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit mousePressed();
        }
        QLabel::mousePressEvent(event); // Call base class implementation
        qDebug ()<< "clicked";
    }
};

#endif // RELEASABLELABEL_H
