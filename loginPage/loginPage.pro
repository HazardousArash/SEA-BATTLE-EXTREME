QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    forgetpassword.cpp \
    main.cpp \
    mainwindow.cpp \
    playermenu.cpp \
    singu.cpp \
    statsmenu.cpp \
    storycharecters.cpp


HEADERS += \
    forgetpassword.h \
    mainwindow.h \
    playermenu.h \
    singu.h \
    statsmenu.h \
    storycharecters.h

QT += sql


FORMS += \
    forgetpassword.ui \
    mainwindow.ui \
    playermenu.ui \
    singu.ui \
    statsmenu.ui \
    storycharecters.ui

FORMS +=


TRANSLATIONS += \
    loginPage_en_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    photos/background.jpg \
    photos/new.jpg

RESOURCES += \
    newRc.qrc