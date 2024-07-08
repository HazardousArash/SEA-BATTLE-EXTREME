#ifndef ARSENALWINDOW_H
#define ARSENALWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "ThemeManager.h"
#include "ArsenalRadar.h"
#include "ArsenalGun.h"
#include "ArsenalShield.h"
#include "ArsenalMissile.h"
#include "ArsenalBomb.h"

namespace Ui {
class ArsenalWindow;
}

class ArsenalWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArsenalWindow(QWidget *parent = nullptr);
    ~ArsenalWindow();

    QPushButton* getStartButton() const;

private slots:
    void onStartButtonClicked();

private:
    Ui::ArsenalWindow *ui;
    ThemeManager themeManager;

    void setupBackground();
    void setupButton();
    void setupIcons();
    void setupCustomFont();

    struct ArsenalItem {
        int purchased;
        int limit;
        QLabel* label;
        QPushButton* button;
    };

    QList<ArsenalItem> arsenalItems;

    ArsenalRadar radar;
    ArsenalGun gun;
    ArsenalShield shield;
    ArsenalMissile missile;
    ArsenalBomb bomb;
};

#endif // ARSENALWINDOW_H
