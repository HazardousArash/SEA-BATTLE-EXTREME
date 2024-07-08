#include "ArsenalBomb.h"
#include <QHBoxLayout>

ArsenalBomb::ArsenalBomb(QWidget *parent)
    : QWidget(parent), purchased(0), limit(2)
{
    label = new QLabel("0/2 +", this);
    buyButton = new QPushButton("+", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buyButton);

    connect(buyButton, &QPushButton::clicked, this, &ArsenalBomb::onBuyButtonClicked);
    updateLabel();
}

int ArsenalBomb::getPurchased() const {
    return purchased;
}

int ArsenalBomb::getLimit() const {
    return limit;
}

void ArsenalBomb::onBuyButtonClicked() {
    if (purchased < limit) {
        purchased++;
        updateLabel();
        emit purchasedChanged(purchased);
    }
}

void ArsenalBomb::updateLabel() {
    label->setText(QString("%1/%2 +").arg(purchased).arg(limit));
}
