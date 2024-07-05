#ifndef PLAYINGWINDOW_H
#define PLAYINGWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <vector>

class Board;
class ThemeManager;
class ClickableLabel;
class GameWindow;

namespace Ui {
class PlayingWindow;
}

class PlayingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayingWindow(QWidget *parent, GameWindow *gameWindow, Board* myBoard, Board* enemyBoard, ThemeManager* themeManager);
    PlayingWindow(QWidget *parent, Board* board, ThemeManager* themeManager);
    ~PlayingWindow();

    void updateGridWithBoardState(Board* board, const QString& boardName);
    Board* myBoard;
    Board* enemyBoard;
    Board *board;
private:
    void setupGifBackground();
    void setupGridBackground();

    Ui::PlayingWindow *ui;
    GameWindow* gameWindow;

    ThemeManager* themeManager;

private slots:
    void onBoardBlockClicked(int row, int col);
    void onEnemyBoardBlockClicked(int row, int col);

protected:
    void showEvent(QShowEvent *event) override;
};

#endif // PLAYINGWINDOW_H
