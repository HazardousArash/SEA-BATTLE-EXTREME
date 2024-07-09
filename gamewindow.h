#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <globalVariables.h>
#include <QWidget>
#include <QMessageBox>
#include "ThemeManager.h"
#include "Board.h"
#include "Ship.h"
#include "DraggableButton.h"
#include "PlayingWindow.h"
#include "ui_playingwindow.h"
#include <QTimer>
#include "ArsenalWindow.h"
#include <QVector>
#include "ArsenalItem.h"
#include <QPair>
class PlayingWindow;
class ArsenalWindow;
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
    Board *enemyBoard{nullptr};
    ThemeManager themeManager;
    PlayingWindow *playingWindow = nullptr;
    Board board;
    void clearBoardUI();
    bool player1Turn;
    bool player2Turn;
    void triggerBotTurn();
    void replacer();
    void populateShipBlockCoordinates();
    void setPlayerOneOil(int oil);
    int getPlayerOneOil() const;
    void setPlayerTwoOil(int oil);
    int getPlayerTwoOil() const;
    QVector<ArsenalItem>& getPlayerOneArsenal();
    QVector<ArsenalItem>& getPlayerTwoArsenal();
    QVector<ArsenalItem> playerOneArsenal;
    QVector<ArsenalItem> playerTwoArsenal;
    void handleArsenalSelectionComplete(int player, int remainingOil, const QVector<ArsenalItem>& selectedArsenal);
    ArsenalWindow *arsenalWindow;
    void processAttack(int row, int col, Board* attackingBoard, Board* defendingBoard, int attackingPlayer);
    QVector<QPair<int, int>> humanBombs;
    QPair<int, int> playerOneShieldedRows;
    QPair<int, int> playerTwoShieldedRows;
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    bool areAllShipsPlaced() ;
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
    std::vector<QPoint> shipBlockCoordinates;
    void showPlayingWindow();
     bool isSecondPlayerSettingUp;
private slots:
    void onNextButtonClicked();
    void switchToTheme1();
    void switchToTheme2();
     void onArsenalSelectionComplete(int player, int oil, const QVector<ArsenalItem>& arsenal);
signals:
    void secondPlayerSetupComplete();

};

#endif // GAMEWINDOW_H
