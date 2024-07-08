#ifndef ARSENALRADAR_H
#define ARSENALRADAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ArsenalRadar : public QWidget
{
    Q_OBJECT

public:
    explicit ArsenalRadar(QWidget *parent = nullptr);
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

#endif // ARSENALRADAR_H
