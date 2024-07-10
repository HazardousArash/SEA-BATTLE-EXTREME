QT       += core gui
QT       += sql
QT       +=core network

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
    clientProject.cpp \
    clientmenu.cpp \
    computerplayer.cpp \
    draggablebutton.cpp \
    forgetpassword.cpp \
    gamewindow.cpp \
    globalVariables.cpp \
    hostmenu.cpp \
    humanplayer.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    onlinemenu.cpp \
    player.cpp \
    playermenu.cpp \
    playingwindow.cpp \
    releasablelabel.cpp \
    serverproject.cpp \
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
    clientProject.h \
    clientmenu.h \
    computerplayer.h \
    draggablebutton.h \
    forgetpassword.h \
    gamewindow.h \
    globalVariables.h \
    hostmenu.h \
    humanplayer.h \
    login.h \
    mainwindow.h \
    onlinemenu.h \
    player.h \
    playermenu.h \
    playingwindow.h \
    releasablelabel.h \
    serverproject.h \
    ship.h \
    singu.h \
    statsmenu.h \
    storycharecters.h \
    thememanager.h

FORMS += \
    ArsenalWindow.ui \
    clientProject.ui \
    clientmenu.ui \
    forgetpassword.ui \
    gamewindow.ui \
    hostmenu.ui \
    mainwindow.ui \
    onlinemenu.ui \
    playermenu.ui \
    playingwindow.ui \
    serverproject.ui \
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

