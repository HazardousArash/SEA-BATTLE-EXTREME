#ifndef ARSENAL_H
#define ARSENAL_H

#include <QWidget>

namespace Ui {
class Arsenal;
}

class Arsenal : public QWidget {
    Q_OBJECT

public:
    explicit Arsenal(QWidget *parent = nullptr);
    ~Arsenal();

private slots:
    void on_startButton_clicked();

private:
    Ui::Arsenal *ui;
};

#endif // ARSENAL_H
