#ifndef ARSENALMISSILE_H
#define ARSENALMISSILE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ArsenalMissile : public QWidget
{
    Q_OBJECT

public:
    explicit ArsenalMissile(QWidget *parent = nullptr);
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

#endif // ARSENALMISSILE_H
