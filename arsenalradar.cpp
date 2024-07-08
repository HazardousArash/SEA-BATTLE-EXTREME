#include "ArsenalRadar.h"
#include <QHBoxLayout>

ArsenalRadar::ArsenalRadar(QWidget *parent)
    : QWidget(parent), purchased(0), limit(2)
{
    label = new QLabel("0/2 +", this);
    buyButton = new QPushButton("+", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buyButton);

    connect(buyButton, &QPushButton::clicked, this, &ArsenalRadar::onBuyButtonClicked);
    updateLabel();
}

int ArsenalRadar::getPurchased() const {
    return purchased;
}

int ArsenalRadar::getLimit() const {
    return limit;
}

void ArsenalRadar::onBuyButtonClicked() {
    if (purchased < limit) {
        purchased++;
        updateLabel();
        emit purchasedChanged(purchased);
    }
}

void ArsenalRadar::updateLabel() {
    label->setText(QString("%1/%2 +").arg(purchased).arg(limit));
}
