#include "ArsenalMissile.h"
#include <QHBoxLayout>

ArsenalMissile::ArsenalMissile(QWidget *parent)
    : QWidget(parent), purchased(0), limit(2)
{
    label = new QLabel("0/2 +", this);
    buyButton = new QPushButton("+", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buyButton);

    connect(buyButton, &QPushButton::clicked, this, &ArsenalMissile::onBuyButtonClicked);
    updateLabel();
}

int ArsenalMissile::getPurchased() const {
    return purchased;
}

int ArsenalMissile::getLimit() const {
    return limit;
}

void ArsenalMissile::onBuyButtonClicked() {
    if (purchased < limit) {
        purchased++;
        updateLabel();
        emit purchasedChanged(purchased);
    }
}

void ArsenalMissile::updateLabel() {
    label->setText(QString("%1/%2 +").arg(purchased).arg(limit));
}
