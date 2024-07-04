#ifndef SINGU_H
#define SINGU_H

#include <QMainWindow>

namespace Ui {
class singU;
}

class singU : public QMainWindow
{
    Q_OBJECT

public:
    explicit singU(QWidget *parent = nullptr);
    ~singU();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::singU *ui;
};

#endif // SINGU_H
