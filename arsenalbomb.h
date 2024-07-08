#ifndef ARSENALBOMB_H
#define ARSENALBOMB_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ArsenalBomb : public QWidget
{
    Q_OBJECT

public:
    explicit ArsenalBomb(QWidget *parent = nullptr);
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

#endif // ARSENALBOMB_H
