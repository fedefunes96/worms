#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T11:51:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_worms
TEMPLATE = app


SOURCES += main.cpp\
    game_view.cpp \
    worm_view.cpp

HEADERS  += \
    game_view.h \
    worm_view.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
