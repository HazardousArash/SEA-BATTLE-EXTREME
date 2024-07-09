#include "ArsenalWindow.h"
#include "ui_ArsenalWindow.h"
#include <QDebug>
#include <QFontDatabase>
#include "globalvariables.h"
#include "GameWindow.h"
#include <QInputDialog>
#include <QFormLayout>

class GameWindow;

ArsenalWindow::ArsenalWindow(GameWindow* gameWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArsenalWindow),
    themeManager(), // Ensure ThemeManager is properly initialized
    gameWindow(gameWindow) // Initialize gameWindow reference
{
    ui->setupUi(this);
    setupBackground(); // Setup background first
    setupButton(); // Setup the button icon
    setupIcons(); // Setup arsenal icons
    setupCustomFont(); // Setup custom font
    setupOilBar(); // Setup oil bar // Setup radar button
}
ArsenalWindow::~ArsenalWindow()
{
    delete ui;
}

QPushButton* ArsenalWindow::getStartButton() const {
    return ui->startButton;
}

void ArsenalWindow::setMode(int mode) {
    modeChosen = mode;
}

void ArsenalWindow::setPlayer(int player) {
    currentPlayer = player;
    resetArsenal(); // Reset arsenal items for the new player

    // Debugging statement
    qDebug() << "Current player set to:" << currentPlayer;

    // Hide all labels and buttons
    for (const QString& iconName : {"radarArsenal", "gunArsenal", "shieldArsenal", "missileArsenal", "bombArsenal"}) {
        for (int p = 1; p <= 2; ++p) {
            QLabel* label = findChild<QLabel*>(QString("label_%1_%2").arg(p).arg(iconName));
            QPushButton* button = findChild<QPushButton*>(QString("button_%1_%2").arg(p).arg(iconName));
            if (label) label->setVisible(p == player);
            if (button) button->setVisible(p == player);
        }
    }
}


void ArsenalWindow::setOil(int oil) {
    if (currentPlayer == 1) {
        gameWindow->setPlayerOneOil(oil);
    } else if (currentPlayer == 2) {
        gameWindow->setPlayerTwoOil(oil);
    }
    updateOil(0); // Update the oil bar display
}

int ArsenalWindow::getOil() const {
    return currentPlayer == 1 ? gameWindow->getPlayerOneOil() : gameWindow->getPlayerTwoOil();
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
    QMap<QString, int> oilCosts = {{"radarArsenal", 15}, {"gunArsenal", 12}, {"shieldArsenal", 10}, {"missileArsenal", 100}, {"bombArsenal", 5}};

    int yOffset = 70; // Initial Y position
    int iconSize = 60; // Icon size
    int spacing = 30; // Spacing between icons

    // Clear previous icons and buttons
    for (QLabel* label : findChildren<QLabel*>()) {
        if (iconNames.contains(label->objectName())) {
            delete label;
        }
    }
    for (QPushButton* button : findChildren<QPushButton*>()) {
        if (button->objectName().startsWith("button_")) {
            delete button;
        }
    }

    QVector<ArsenalItem>& currentArsenal = (currentPlayer == 1) ? gameWindow->getPlayerOneArsenal() : gameWindow->getPlayerTwoArsenal();
    currentArsenal.clear(); // Clear previous items for the current player

    for (const QString& iconName : iconNames) {
        ArsenalItem item;
        item.purchased = 0;
        item.limit = iconName == "missileArsenal" ? 1 : 2; // Set limit to 1 for missileArsenal
        item.oilCost = oilCosts[iconName];

        QLabel* iconLabel = new QLabel(this);
        iconLabel->setObjectName(iconName); // Set unique object name
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

        item.label = new QLabel(QString("0/%2 ").arg(item.limit), this);
        item.label->setObjectName("label_" + iconName); // Set unique object name for label
        item.label->move(100, yOffset + 15); // Position the label
        item.label->setStyleSheet("font: 20pt; color: black;"); // Adjust the style as needed

        item.button = new QPushButton("+", this);
        item.button->setObjectName("button_" + iconName); // Set unique object name for button
        item.button->setFixedSize(30, 30);
        item.button->move(170, yOffset + 15); // Position the button

        // Copy the item for use in the lambda
        ArsenalItem* itemPtr = new ArsenalItem(item);

        connect(item.button, &QPushButton::clicked, this, [this, itemPtr, iconName]() mutable {
            int& currentOil = (currentPlayer == 1) ? playerOneOil : playerTwoOil;
            qDebug() << "Button clicked for" << iconName << "Current oil:" << currentOil << "Oil cost:" << itemPtr->oilCost;
            if (itemPtr->purchased < itemPtr->limit && currentOil >= itemPtr->oilCost) {
                itemPtr->purchased++;
                updateOil(-itemPtr->oilCost);
                itemPtr->label->setText(QString("%1/%2 ").arg(itemPtr->purchased).arg(itemPtr->limit));
                qDebug() << iconName << "purchased: " << itemPtr->purchased;

                // Create objects based on the iconName
                if (iconName == "radarArsenal") {
                    ArsenalRadar* radar = new ArsenalRadar();
                    qDebug() << "Created ArsenalRadar object.";
                    if (currentPlayer == 1||currentPlayer ==0) {
                        playerOneNumberOfRadars++;
                        humanRadarCounts++;
                        qDebug() << "Human player radar count: " << humanRadarCounts;
                    } else if (currentPlayer == 2) {
                        playerTwoNumberOfRadars++;
                        qDebug() << "Player 2 radar count: " << playerTwoNumberOfRadars;
                    }
                } else if (iconName == "gunArsenal") {
                    ArsenalGun* gun = new ArsenalGun();
                    qDebug() << "Created ArsenalGun object.";
                    // Increment the gun count for the current player
                     if (currentPlayer == 1||currentPlayer ==0) {
                        playerOneNumberOfGuns++;
                        qDebug() << "Player 1 now has " << playerOneNumberOfGuns << " guns.";
                    } else {
                        playerTwoNumberOfGuns++;
                        qDebug() << "Player 2 now has " << playerTwoNumberOfGuns << " guns.";
                    }
                } else if (iconName == "shieldArsenal") {
                    ArsenalShield* shield = new ArsenalShield();
                    qDebug() << "Created ArsenalShield object.";
                    showShieldCoordinateDialog();
                } else if (iconName == "missileArsenal") {
                    ArsenalMissile* missile = new ArsenalMissile();
                    qDebug() << "Created ArsenalMissile object.";
                    if (currentPlayer == 1 || currentPlayer ==0) {
                        playerOneNumberOfMissiles++;
                    } else if (currentPlayer == 2) {
                        playerTwoNumberOfMissiles++;
                    }
                    qDebug() << "Player " << currentPlayer << " now has " << ((currentPlayer == 1) ? playerOneNumberOfMissiles : playerTwoNumberOfMissiles) << " missiles.";
                } else if (iconName == "bombArsenal") {
                    ArsenalBomb* bomb = new ArsenalBomb();
                    qDebug() << "Created ArsenalBomb object.";
                    // Show the coordinate dialog for bomb placement
                    showMineCoordinateDialog(*itemPtr);
                }

                if (currentPlayer == 1) {
                    gameWindow->getPlayerOneArsenal().append(*itemPtr);
                } else if (currentPlayer == 2) {
                    gameWindow->getPlayerTwoArsenal().append(*itemPtr);
                }
            } else {
                qDebug() << "Cannot purchase" << iconName << "either limit reached or insufficient oil.";
            }
        });

        yOffset += iconSize + spacing; // Update the yOffset for the next icon

        currentArsenal.append(item); // Add item to the current player's arsenal list
    }
}


void ArsenalWindow::setupOilBar() {
    oilBar = new QProgressBar(this);
    oilBar->setRange(0, 220);
    oilBar->setValue(getOil()); // Start with the current player's oil
    oilBar->setFormat("%v"); // Display the current oil value
    oilBar->setGeometry(20, 50, 200, 30); // Position the bar at the top left of the window
    oilBar->setStyleSheet(
        "QProgressBar {"
        "border: 2px solid grey; "
        "border-radius: 5px; "
        "text-align: center; "
        "color: white;" // Set the text color to white
        "}"
        "QProgressBar::chunk {"
        "background-color: #2E0854; " // Darker purple color
        "width: 20px; "
        "}"
        );
    oilBar->show();
    qDebug() << "Oil bar set up successfully with initial value:" << getOil();
}

void ArsenalWindow::updateOil(int amount) {
    int& currentOil = (currentPlayer == 1) ? playerOneOil : playerTwoOil;
    currentOil += amount;
    oilBar->setValue(currentOil);
    qDebug() << "Oil updated. Current oil:" << currentOil;
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
    qDebug() << "Next button in ArsenalWindow clicked";
    QVector<ArsenalItem> selectedArsenal = (currentPlayer == 1) ? playerOneArsenal : playerTwoArsenal;
    int remainingOil = (currentPlayer == 1) ? playerOneOil : playerTwoOil;

    // Emit the signal with the player number, remaining oil, and selected arsenal items
    emit arsenalSelectionComplete(currentPlayer, remainingOil, selectedArsenal);

    // Close the ArsenalWindow
    this->close();
}

void ArsenalWindow::resetArsenal() {
    if (currentPlayer == 1) {
        playerOneArsenal.clear();
    } else if (currentPlayer == 2) {
        playerTwoArsenal.clear();
    }

    // Clear existing widgets to prevent overlap and persistence
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {
        if (label->objectName().startsWith("label_") || label->objectName().startsWith("radarArsenal") ||
            label->objectName().startsWith("gunArsenal") || label->objectName().startsWith("shieldArsenal") ||
            label->objectName().startsWith("missileArsenal") || label->objectName().startsWith("bombArsenal")) {
            delete label;
        }
    }

    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        if (button->objectName().startsWith("button_")) {
            delete button;
        }
    }

    // Resetting oil
    oilBar->setValue(currentPlayer == 1 ? gameWindow->getPlayerOneOil() : gameWindow->getPlayerTwoOil());

    setupIcons(); // Re-setup icons
}

void ArsenalWindow::showMineCoordinateDialog(ArsenalItem& item) {
    bool validInput = false;
    while (!validInput) {
        QDialog dialog(this);
        dialog.setWindowTitle("Enter Coordinates for Mine Placement");
        QVBoxLayout layout(&dialog);

        QFormLayout formLayout;
        QLineEdit rowInput;
        QLineEdit colInput;
        formLayout.addRow("Row:", &rowInput);
        formLayout.addRow("Col:", &colInput);
        layout.addLayout(&formLayout);

        QHBoxLayout buttonLayout;
        QPushButton okButton("OK");
        buttonLayout.addWidget(&okButton);
        layout.addLayout(&buttonLayout);

        connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        if (dialog.exec() == QDialog::Accepted) {
            int row = rowInput.text().toInt();
            int col = colInput.text().toInt();

            Board* playerBoard = (currentPlayer == 1) ? &player1Board : &player2Board;

            // Check if the coordinates are within bounds and the cell is empty
            if (row >= 0 && row < playerBoard->getGrid().size() && col >= 0 && col < playerBoard->getGrid()[0].size() && playerBoard->getGrid()[row][col] == 0) {
                playerBoard->getGrid()[row][col] = 101;
                qDebug() << "Mine placed at (" << row << "," << col << ") on player" << currentPlayer << "board.";

                // Store the coordinates in humanBombs
                gameWindow->humanBombs.append(qMakePair(row, col));

                // Print the board for debugging
                qDebug() << "Current Board State:";
                for (const auto& rowVec : playerBoard->getGrid()) {
                    QString rowString;
                    for (int cell : rowVec) {
                        rowString += QString::number(cell) + " ";
                    }
                    qDebug() << rowString;
                }
                validInput = true;
            } else {
                QMessageBox::warning(this, "Invalid Input", "Invalid coordinates or cell is not empty. Please try again.");
            }
        }
    }
}

bool ArsenalWindow::validateMineCoordinate(int row, int col) {
    Board* playerBoard = currentPlayer == 1 ? &player1Board : &player2Board;
    return playerBoard->getCell(row, col) == 0; // Ensure the cell is empty
}

void ArsenalWindow::showShieldCoordinateDialog() {
    bool validInput = false;
    while (!validInput) {
        QDialog dialog(this);
        dialog.setWindowTitle("Enter Rows for Shield Placement");
        QVBoxLayout layout(&dialog);

        QFormLayout formLayout;
        QLineEdit row1Input;
        QLineEdit row2Input;
        formLayout.addRow("Row 1:", &row1Input);
        formLayout.addRow("Row 2:", &row2Input);
        layout.addLayout(&formLayout);

        QHBoxLayout buttonLayout;
        QPushButton okButton("OK");
        buttonLayout.addWidget(&okButton);
        layout.addLayout(&buttonLayout);

        connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        if (dialog.exec() == QDialog::Accepted) {
            int row1 = row1Input.text().toInt();
            int row2 = row2Input.text().toInt();

            // Validate the rows
            if (row1 >= 0 && row1 < 10 && row2 >= 0 && row2 < 10 && row1 != row2) {
                if (currentPlayer == 1||currentPlayer==0) {
                    gameWindow->playerOneShieldedRows = qMakePair(row1, row2);
                } else {
                    gameWindow->playerTwoShieldedRows = qMakePair(row1, row2);
                }
                qDebug() << "Shield rows set for player" << currentPlayer << ":" << row1 << "and" << row2;
                validInput = true;
            } else {
                QMessageBox::warning(this, "Invalid Input", "Invalid rows or rows are the same. Please try again.");
            }
        }
    }
}




