#ifndef ARSENALSHIELD_H
#define ARSENALSHIELD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ArsenalShield : public QWidget
{
    Q_OBJECT

public:
    explicit ArsenalShield(QWidget *parent = nullptr);
    int getPurchased() const;
    int getLimit() const;

signals:
    void purchasedChanged(int purchased);

private slots:
    void onBuyButtonClicked();

private:
    int purchased;
    const int limit;
    QLabel* label;
    QPushButton* buyButton;

    void updateLabel();
};

#endif // ARSENALSHIELD_H
