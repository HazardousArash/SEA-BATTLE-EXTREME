#ifndef WAITINGWINDOW_H
#define WAITINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class WaitingWindow;
}

class WaitingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaitingWindow(QWidget *parent = nullptr);
    ~WaitingWindow();

signals:
    void boardReceived();

public slots:
    void onBoardReceived();

private:
    Ui::WaitingWindow *ui;
};

#endif // WAITINGWINDOW_H
