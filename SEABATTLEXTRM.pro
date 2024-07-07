QT       += core gui



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arsenal.cpp \
    board.cpp \
    clickablelabel.cpp \
    computerplayer.cpp \
    draggablebutton.cpp \
    gamewindow.cpp \
    globalVariables.cpp \
    humanplayer.cpp \
    main.cpp \
    player.cpp \
    playingwindow.cpp \
    releasablelabel.cpp \
    ship.cpp \
    thememanager.cpp

HEADERS += \
    arsenal.h \
    board.h \
    clickablelabel.h \
    computerplayer.h \
    draggablebutton.h \
    gamewindow.h \
    globalVariables.h \
    humanplayer.h \
    player.h \
    playingwindow.h \
    releasablelabel.h \
    ship.h \
    thememanager.h

FORMS += \
    gamewindow.ui \
    playingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

