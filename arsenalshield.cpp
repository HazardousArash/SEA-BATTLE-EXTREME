#include "ArsenalShield.h"
#include <QHBoxLayout>

ArsenalShield::ArsenalShield(QWidget *parent)
    : QWidget(parent), purchased(0), limit(2)
{
    label = new QLabel("0/2 +", this);
    buyButton = new QPushButton("+", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buyButton);

    connect(buyButton, &QPushButton::clicked, this, &ArsenalShield::onBuyButtonClicked);
    updateLabel();
}

int ArsenalShield::getPurchased() const {
    return purchased;
}

int ArsenalShield::getLimit() const {
    return limit;
}

void ArsenalShield::onBuyButtonClicked() {
    if (purchased < limit) {
        purchased++;
        updateLabel();
        emit purchasedChanged(purchased);
    }
}

void ArsenalShield::updateLabel() {
    label->setText(QString("%1/%2 +").arg(purchased).arg(limit));
}
