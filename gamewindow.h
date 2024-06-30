#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "ThemeManager.h"
#include "Board.h"
#include "Ship.h"  // Include Ship class
#include "draggablebutton.h"
#include <qlabel.h>
namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void resetBlockColors();
    void setCurrentShip(const Ship& ship);
    void attachShipToBoard() ;
    void handleShipDrop(DraggableButton* button);
    void contextMenuEvent(QContextMenuEvent* event) override;
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    Ui::GameWindow *ui;
    ThemeManager themeManager;
    Board board{10};  // Assume board is initialized appropriately
    Ship currentShip;  // Declare currentShip to track the ship being dragged
     bool isDraggingShip;
    void setupGridBackground();
    void setupIcons();
    void setupTable();
    void initializeFleet();
    DraggableButton* addDraggableButton(const QString& iconName,Ship &ship, int x, int y, int size, int subtractionX, int subtractionY);
    QString getShipIconName(int length);
    void highlightAvailableBlocks();
    void placeShipOnBoard(int x, int y);
    QVector<QVector<QLabel*>> labelGrid;
    DraggableButton* currentShipButton = nullptr;
public slots:
    void switchToTheme1();
    void switchToTheme2();
};

#endif // GAMEWINDOW_H
