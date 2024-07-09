#ifndef ARSENALITEM_H
#define ARSENALITEM_H

#include <QLabel>
#include <QPushButton>

struct ArsenalItem {
    int purchased;
    int limit;
    QLabel* label;
    QPushButton* button;
    int oilCost;
};

#endif // ARSENALITEM_H
