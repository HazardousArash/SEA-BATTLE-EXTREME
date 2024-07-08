#include "ArsenalGun.h"
#include <QHBoxLayout>

ArsenalGun::ArsenalGun(QWidget *parent)
    : QWidget(parent), purchased(0), limit(2)
{
    label = new QLabel("0/2 +", this);
    buyButton = new QPushButton("+", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buyButton);

    connect(buyButton, &QPushButton::clicked, this, &ArsenalGun::onBuyButtonClicked);
    updateLabel();
}

int ArsenalGun::getPurchased() const {
    return purchased;
}

int ArsenalGun::getLimit() const {
    return limit;
}

void ArsenalGun::onBuyButtonClicked() {
    if (purchased < limit) {
        purchased++;
        updateLabel();
        emit purchasedChanged(purchased);
    }
}

void ArsenalGun::updateLabel() {
    label->setText(QString("%1/%2 +").arg(purchased).arg(limit));
}
