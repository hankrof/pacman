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
        pcmainwindow.cpp \
    pacman.cpp \
    gamemap.cpp \
    character.cpp \
    picture.cpp \
    collider.cpp

HEADERS  += pcmainwindow.h \
    pacman.h \
    gamemap.h \
    character.h \
    picture.h \
    collider.h
