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
    worm.cpp \
    camera.cpp \
    mybutton.cpp \
    bazooka.cpp \
    dialogchooseweapon.cpp \
    protocol.cpp \
    client.cpp \
    player.cpp \
    thread.cpp \
    game.cpp \
    common_socket.cpp \
    graphicitem.cpp

HEADERS  += \
    game_view.h \
    worm_view.h \
    eventhandler.h \
    girder_view.h \
    worm.h \
    camera.h \
    mybutton.h \
    bazooka.h \
    dialogchooseweapon.h \
    protocol.h \
    player.h \
    thread.h \
    game.h \
    socket.h \
    movable.h

FORMS    += \
    dialogchooseweapon.ui

RESOURCES += \
    resources.qrc
