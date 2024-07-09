#ifndef ARSENALGUN_H
#define ARSENALGUN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ArsenalGun : public QWidget
{
    Q_OBJECT

public:
    explicit ArsenalGun(QWidget *parent = nullptr);
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

#endif // ARSENALGUN_H
