#ifndef PLAYINGWINDOW_H
#define PLAYINGWINDOW_H

#include <QWidget>
#include "Board.h"
#include "ThemeManager.h"
#include "ClickableLabel.h"
#include "GameWindow.h"
class GameWindow;
namespace Ui {
class PlayingWindow;
}

class PlayingWindow : public QWidget {
    Q_OBJECT

public:
    PlayingWindow(QWidget *parent, Board* board, ThemeManager* themeManager);
    explicit PlayingWindow(QWidget *parent = nullptr, GameWindow *gameWindow = nullptr, Board* myBoard = nullptr, Board* enemyBoard = nullptr, ThemeManager* themeManager = nullptr);
    ~PlayingWindow();

protected:
    void showEvent(QShowEvent *event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    Ui::PlayingWindow *ui;
    GameWindow *gameWindow;
    Board* myBoard;
    Board* enemyBoard;
    ThemeManager* themeManager;
    void makeShipBlocksPurple(int shipID);
    void setupGridBackground();
    void setupGifBackground();
    void updateGridWithBoardState(Board* board, const QString& boardName);

private slots:
    void onBoardBlockClicked(int row, int col);
    void onEnemyBoardBlockClicked(int row, int col);
    void markSingleShipBlockGreen(int row, int col) ;
    void makeShipBlocksWhite(int shipID);
    void markSingleShipBlockWithCross(int row, int col);
    void clearShipBlockCrosses(int shipID);
    void makeShipBlocksPurple(int shipID, const QString& boardName);
    void markSingleShipBlockWithCross(int row, int col, const QString& boardName);
    void clearShipBlockCrosses(int shipID, const QString& boardName);
};

#endif // PLAYINGWINDOW_H
