#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T15:47:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacMan
TEMPLATE = app


SOURCES += main.cpp\
    model/character.cpp \
    model/collider.cpp \
    model/gamemap.cpp \
    model/pacman.cpp \
    model/picture.cpp \
    view/pcmainwindow.cpp

HEADERS  += model/character.h \
    model/collider.h \
    model/gamemap.h \
    model/pacman.h \
    model/picture.h \
    model/character.h \
    model/picture.h \
    model/collider.h \
    view/pcmainwindow.h
