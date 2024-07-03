#ifndef PLAYINGWINDOW_H
#define PLAYINGWINDOW_H

#include <QWidget>
#include "Board.h"
#include "ThemeManager.h"

namespace Ui {
class PlayingWindow;
}

class PlayingWindow : public QWidget {
    Q_OBJECT

public:
    explicit PlayingWindow(QWidget *parent = nullptr, Board* board = nullptr, ThemeManager* themeManager = nullptr);
    ~PlayingWindow();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::PlayingWindow *ui;
    Board* board;
    ThemeManager* themeManager;

    void setupGridBackground();
};

#endif //
