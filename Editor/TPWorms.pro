#-------------------------------------------------
#
# Project created by QtCreator 2018-05-13T21:30:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TPWorms
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lyaml-cpp

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    editorubicable.cpp \
    editorworm.cpp \
    editorviga.cpp \
    editorusables.cpp \
    editor_worm_view.cpp \
    editor_viga_view.cpp \
    commonarchivo.cpp \
    editorBacgroun.cpp \
    editor_viga_grande_view.cpp \
    scene.cpp \
    parser.cpp \
    utilselection.cpp \
    mapeditor.cpp

HEADERS += \
        mainwindow.h \
    editorubicable.h \
    editorworm.h \
    editorviga.h \
    editorusables.h \
    editor_worm_view.h \
    editor_viga_view.h \
    commonarchivo.h \
    editorBacgroun.h \
    editor_viga_grande_view.h \
    scene.h \
    parser.h \
    utilselection.h \
    mapeditor.h

FORMS += \
        mainwindow.ui \
    editorpantalla.ui \
    editorseleccionarmasherramientas.ui \
    editorBacgroun.ui
