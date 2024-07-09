#ifndef ARSENALITEM_H
#define ARSENALITEM_H

#include <QLabel>
#include <QPushButton>

struct ArsenalItem {
    int purchased;
    int limit;
    QLabel* label;
    QPushButton* button;
    int oilCost; // Add oil cost to the item
    QString itemType; // Add this to differentiate item types (e.g., radar, gun)
};


#endif // ARSENALITEM_H
