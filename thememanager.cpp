#include "ThemeManager.h"
#include <QDirIterator>
#include <QDebug>

ThemeManager::ThemeManager() : currentTheme(1) {
    qDebug() << "ThemeManager constructor started";
    loadThemeResources();
}

void ThemeManager::setTheme(int themeNumber) {
    currentTheme = themeNumber;
    loadThemeResources();
}

QPixmap ThemeManager::getIcon(const QString& iconName) const {
    return icons.value(iconName);
}

void ThemeManager::loadThemeResources() {
    icons.clear();

    QString themePath = QString(":/themes/theme%1").arg(currentTheme);
    QStringList iconNames = {"paperGrid", "paperGridEnemy", "table", "back", "next", "shuffle", "rank", "level", "opponent", "largeShip", "midShip", "smallShip", "tinyShip"};

    qDebug() << "Loading resources from" << themePath;
    for (const QString &iconName : iconNames) {
        QString filePath = QString("%1/%2.png").arg(themePath).arg(iconName);
        QPixmap icon(filePath);
        if (!icon.isNull()) {
            icons.insert(iconName, icon);
            qDebug() << "Loaded icon:" << filePath;
        } else {
            qDebug() << "Failed to load icon:" << filePath;
        }
    }
}
