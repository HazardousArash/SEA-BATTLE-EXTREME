#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QMap>
#include <QPixmap>
#include <QString>

class ThemeManager {
public:
    ThemeManager();
    void setTheme(int themeNumber);
    QPixmap getIcon(const QString& iconName) const;
    QString getIconPath(const QString& iconName) const;  // Add this method

private:
    int currentTheme;
    QMap<QString, QPixmap> icons;
    void loadThemeResources();
};

#endif // THEMEMANAGER_H
