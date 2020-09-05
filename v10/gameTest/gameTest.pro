QT       += core gui \
         multimedia
         RC_ICONS += Icon1.ico
QT                += sql widgets widgets
requires(qtConfig(tableview))
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountcreation.cpp \
    ammo.cpp \
    angledbullet.cpp \
    background.cpp \
    bullet.cpp \
    display.cpp \
    enemy.cpp \
    game.cpp \
    gamewindow.cpp \
    health.cpp \
    hpbar.cpp \
    infoplayer.cpp \
    infoship.cpp \
    infoturret.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    score.cpp \
    ship.cpp \
    stationaryObject.cpp \
    turret.cpp \
    user.cpp


HEADERS += \
    accountcreation.h \
    ammo.h \
    angledbullet.h \
    background.h \
    bullet.h \
    display.h \
    enemy.h \
    game.h \
    gamewindow.h \
    health.h \
    hpbar.h \
    infoplayer.h \
    infoship.h \
    infoturret.h \
    mainwindow.h \
    player.h \
    score.h  \
    ship.h \
    stationaryObject.h \
    turret.h \
    user.h

FORMS += \
    accountcreation.ui \
    gamewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
