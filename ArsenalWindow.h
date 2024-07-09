#ifndef ARSENALWINDOW_H
#define ARSENALWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QMap>
#include "ThemeManager.h"
#include "GameWindow.h"
#include "ArsenalRadar.h"
#include "ArsenalGun.h"
#include "ArsenalShield.h"
#include "ArsenalMissile.h"
#include "ArsenalBomb.h"
#include "ArsenalItem.h"
#include "globalVariables.h"
#include "playingwindow.h"
class GameWindow;

namespace Ui {
class ArsenalWindow;
}

class ArsenalWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArsenalWindow(GameWindow* gameWindow, QWidget *parent = nullptr);
    ~ArsenalWindow();
    QPushButton* getStartButton() const;
    void setMode(int mode);
    void setPlayer(int player);
    void setOil(int oil);
    int getOil() const;
    void resetArsenal();
private:
    Ui::ArsenalWindow *ui;
    ThemeManager themeManager;
    QProgressBar* oilBar;
    int modeChosen;
    int currentPlayer;
    GameWindow* gameWindow; // Reference to the GameWindow
    QVector<ArsenalItem> playerOneArsenal;
    QVector<ArsenalItem> playerTwoArsenal;
    void showMineCoordinateDialog(ArsenalItem &item);
    bool validateMineCoordinate(int row, int col);
    void setupBackground();
    void setupButton();
    void setupIcons();
    void setupOilBar();
    void updateOil(int amount);
    void setupCustomFont();
    int getCurrentPlayerOil() const;
    void setCurrentPlayerOil(int oil);

private slots:
    void onStartButtonClicked();
signals:
    void arsenalSelectionComplete(int player, int oil, const QVector<ArsenalItem>& arsenal);
};

#endif // ARSENALWINDOW_H
