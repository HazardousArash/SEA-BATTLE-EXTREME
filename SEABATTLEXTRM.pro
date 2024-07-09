QT       += core gui
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArsenalWindow.cpp \
    Game.cpp \
    arsenalbomb.cpp \
    arsenalgun.cpp \
    arsenalitem.cpp \
    arsenalmissile.cpp \
    arsenalradar.cpp \
    arsenalshield.cpp \
    board.cpp \
    clickablelabel.cpp \
    computerplayer.cpp \
    draggablebutton.cpp \
    forgetpassword.cpp \
    gamewindow.cpp \
    globalVariables.cpp \
    humanplayer.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playermenu.cpp \
    playingwindow.cpp \
    releasablelabel.cpp \
    ship.cpp \
    singu.cpp \
    statsmenu.cpp \
    storycharecters.cpp \
    thememanager.cpp

HEADERS += \
    ArsenalWindow.h \
    Game.h \
    arsenalbomb.h \
    arsenalgun.h \
    arsenalitem.h \
    arsenalmissile.h \
    arsenalradar.h \
    arsenalshield.h \
    board.h \
    clickablelabel.h \
    computerplayer.h \
    draggablebutton.h \
    forgetpassword.h \
    gamewindow.h \
    globalVariables.h \
    humanplayer.h \
    login.h \
    mainwindow.h \
    player.h \
    playermenu.h \
    playingwindow.h \
    releasablelabel.h \
    ship.h \
    singu.h \
    statsmenu.h \
    storycharecters.h \
    thememanager.h

FORMS += \
    ArsenalWindow.ui \
    forgetpassword.ui \
    gamewindow.ui \
    mainwindow.ui \
    playermenu.ui \
    playingwindow.ui \
    singu.ui \
    statsmenu.ui \
    storycharecters.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc \
    icons.qrc \
    photos.qrc

