#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "ThemeManager.h"
#include "Board.h"
#include "Ship.h"
#include "DraggableButton.h"
#include "PlayingWindow.h"
#include "ui_playingwindow.h"
class PlayingWindow;
namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    bool isWithinGrid(int x, int y);
    void resetBlockColors();
    void setCurrentShip(const Ship& ship);
    void attachShipToBoard();
    void handleShipDrop(DraggableButton* button);
    void contextMenuEvent(QContextMenuEvent* event) override;
    void resetGame();
    Board *myBoard;
    Board *enemyBoard;
    ThemeManager themeManager;
    PlayingWindow *playingWindow = nullptr;
    Board board;
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Ui::GameWindow *ui;
    std::vector<Ship*> ships;
    Ship currentShip;
    bool isDraggingShip;
    void setupGridBackground();
    void setupIcons();
    void setupTable();
    void initializeFleet();
    DraggableButton* addDraggableButton(const QString& iconName, Ship &ship, int x, int y, int size, int subtractionX, int subtractionY);
    QString getShipIconName(int length);
    void highlightAvailableBlocks();
    void placeShipOnBoard(int x, int y);
    QVector<QVector<QLabel*>> labelGrid;
    DraggableButton* currentShipButton = nullptr;

    void showPlayingWindow();

private slots:
    void onNextButtonClicked();
    void switchToTheme1();
    void switchToTheme2();
};

#endif // GAMEWINDOW_H
