#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T22:42:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = gobang
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    chessboard.cpp \
    humanplayer.cpp \
    computerplayer.cpp \
    player.cpp

HEADERS += \
    chessboard.h \
    humanplayer.h \
    computerplayer.h \
    player.h
