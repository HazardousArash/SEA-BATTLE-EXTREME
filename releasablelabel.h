// CustomLabel.h
#include <QLabel>
#include <QMouseEvent>

class ReleasableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ReleasableLabel (QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void mouseReleased();  // Custom signal for mouse release

protected:
    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit mouseReleased();
        }
        QLabel::mouseReleaseEvent(event);
    }
};
