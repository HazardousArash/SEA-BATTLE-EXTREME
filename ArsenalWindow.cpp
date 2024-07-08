#include "ArsenalWindow.h"
#include "ui_ArsenalWindow.h"
#include <QDebug>
#include <QFontDatabase>

// Include your arsenal classes
#include "ArsenalRadar.h"
#include "ArsenalGun.h"
#include "ArsenalShield.h"
#include "ArsenalMissile.h"
#include "ArsenalBomb.h"

// Add these declarations to your class definition in the header file
struct ArsenalItem {
    int purchased;
    int limit;
    QLabel* label;
    QPushButton* button;
};

ArsenalWindow::ArsenalWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArsenalWindow),
    themeManager() // Ensure ThemeManager is properly initialized
{
    ui->setupUi(this);
    setupBackground(); // Setup background first
    setupButton(); // Setup the button icon
    setupIcons(); // Setup arsenal icons
    setupCustomFont(); // Setup custom font
}

ArsenalWindow::~ArsenalWindow()
{
    delete ui;
}

QPushButton* ArsenalWindow::getStartButton() const {
    return ui->startButton;
}

void ArsenalWindow::setupBackground() {
    QPixmap backgroundPixmap = QPixmap(themeManager.getIconPath("table")); // Get the "table" image from ThemeManager
    if (!backgroundPixmap.isNull()) {
        ui->backgroundLabel->setPixmap(backgroundPixmap);
        ui->backgroundLabel->setScaledContents(true);
        qDebug() << "Background image set successfully.";
    } else {
        qDebug() << "Failed to load background image!";
    }

    // Ensure the button is on top and visible
    ui->startButton->raise();
    qDebug() << "Start button raised to front.";
}

void ArsenalWindow::setupButton() {
    QPixmap nextPixmap(themeManager.getIconPath("next"));
    if (!nextPixmap.isNull()) {
        // Set the button size to be 3 times larger
        QSize buttonSize = ui->startButton->size() * 3;
        QPixmap scaledPixmap = nextPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Set the scaled pixmap as the button icon
        ui->startButton->setIcon(QIcon(scaledPixmap));
        ui->startButton->setIconSize(buttonSize);

        // Adjust the button size to fit the icon
        ui->startButton->setFixedSize(buttonSize);
        ui->startButton->setStyleSheet("QPushButton { border: none; background: transparent; }");

        // Remove the default text
        ui->startButton->setText("");
        qDebug() << "Start button icon set successfully.";
    } else {
        qDebug() << "Failed to load next button icon!";
    }

    connect(ui->startButton, &QPushButton::clicked, this, &ArsenalWindow::onStartButtonClicked);
    qDebug() << "Start button click connected.";
}

void ArsenalWindow::setupIcons() {
    QStringList iconNames = {"radarArsenal", "gunArsenal", "shieldArsenal", "missileArsenal", "bombArsenal"};
    int yOffset = 70; // Initial Y position
    int iconSize = 60; // Icon size
    int spacing = 30; // Spacing between icons

    for (const QString& iconName : iconNames) {
        ArsenalItem item;
        item.purchased = 0;
        item.limit = 2;

        QLabel* iconLabel = new QLabel(this);
        iconLabel->setFixedSize(iconSize, iconSize);
        iconLabel->setStyleSheet("background: transparent;"); // Remove background
        QString iconPath = themeManager.getIconPath(iconName);
        qDebug() << "Attempting to load icon:" << iconName << "from path:" << iconPath; // Debugging path
        QPixmap iconPixmap = QPixmap(iconPath);
        if (!iconPixmap.isNull()) {
            iconLabel->setPixmap(iconPixmap.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            iconLabel->setScaledContents(true); // Make pixmap fit label borders
            iconLabel->raise(); // Bring the label to the front
            qDebug() << "Icon" << iconName << "set successfully.";
        } else {
            qDebug() << "Failed to load icon:" << iconName << "from path:" << iconPath;
        }

        // Hide the text of the label
        iconLabel->setText("");

        // Position the icons
        iconLabel->move(30, yOffset);
        qDebug() << "Icon" << iconName << "positioned at (" << 30 << ", " << yOffset << ").";

        item.label = new QLabel(QString("%1/%2 +").arg(item.purchased).arg(item.limit), this);
        item.label->move(100, yOffset + 15); // Position the label
        item.label->setStyleSheet("font: 20pt; color: black;"); // Adjust the style as needed

        item.button = new QPushButton("+", this);
        item.button->setFixedSize(30, 30);
        item.button->move(170, yOffset + 15); // Position the button
        connect(item.button, &QPushButton::clicked, this, [this, &item]() {
            if (item.purchased < item.limit) {
                item.purchased++;
                item.label->setText(QString("%1/%2 +").arg(item.purchased).arg(item.limit));
            }
        });

        yOffset += iconSize + spacing; // Update the yOffset for the next icon

        arsenalItems.append(item); // Add the item to the list
    }
}

void ArsenalWindow::setupCustomFont() {
    int fontId = QFontDatabase::addApplicationFont(":/fonts/rdr.ttf");
    if (fontId == -1) {
        qDebug() << "Failed to load font.";
        return;
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    qDebug() << "Font loaded successfully:" << fontFamily;

    QFont font(fontFamily);
    ui->label->setFont(font);
    ui->label->setStyleSheet("font: 65pt; color: rgb(235, 0, 0); border: 5px solid rgb(255, 255, 255);");
    qDebug() << "Custom font applied to label.";
}

void ArsenalWindow::onStartButtonClicked() {
    // Logic for what happens when the next button is clicked
    qDebug() << "Next button in ArsenalWindow clicked";
    // For example, show the next window or close the current one
}
