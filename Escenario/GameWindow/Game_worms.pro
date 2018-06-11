#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T11:51:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_worms
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES +=\
    game_view.cpp \
    worm_view.cpp \
    eventhandler.cpp \
    girder_view.cpp \
    camera.cpp \
    protocol.cpp \
    client.cpp \
    player.cpp \
    socket.cpp \
    movable.cpp \
    items.cpp \
    weapons_and_tools.cpp \
    target.cpp \
    gameclass.cpp \
    controler.cpp \
    weapon.cpp \
    projectile.cpp \
    gamewindow.cpp \
    roomcreator.cpp \
    mapSelection.cpp \
    client.cpp \
    button.cpp \
    waitRoom.cpp \
    clientmainwindow.cpp \
    window.cpp

HEADERS  += \
    game_view.h \
    worm_view.h \
    eventhandler.h \
    girder_view.h \
    camera.h \
    protocol.h \
    player.h \
    socket.h \
    movable.h \
    items.h \
    weapons_and_tools.h \
    target.h \
    gameclass.h \
    controler.h \
    weapon.h \
    projectile.h \
    gamewindow.h \
    roomcreator.h \
    mapSelection.h \
    clientmainwindow.h \
    button.h \
    waitRoom.h \
    window.h

FORMS    += \
    weapons_and_tools.ui \
    gamewindow.ui \
    roomcreator.ui \
    mapSelection.ui \
    clientmainwindow.ui \
    waitRoom.ui \
    window.ui
