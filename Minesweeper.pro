QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    GameOverDialog.cpp \
    game.cpp \
    gamesettings.cpp \
    main.cpp \
    view.cpp

HEADERS += \
    GameOverDialog.h \
    game.h \
    gamesettings.h \
    view.h

RESOURCES += \
    resource.qrc

