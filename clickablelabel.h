#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

signals:
    void clicked(int row, int col);

protected:
    void mousePressEvent(QMouseEvent* event) override;

public slots:
    void setRowCol(int row, int col);

private:
    int row;
    int col;
};

#endif // CLICKABLELABEL_H
