#-------------------------------------------------
#
# Project created by QtCreator 2018-11-17T18:54:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMO
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


SOURCES += \
    gui/mainwindow.cpp \
    core/src/application/Application.cpp \
    core/src/buffer/Buffer.cpp \
    core/src/functional/FunctionalModule.cpp \
    core/src/handler/Handler.cpp \
    core/src/source/Source.cpp \
    core/src/strategies/addition/FreeAddition.cpp \
    core/src/strategies/selection/RingSelection.cpp \
    core/src/strategies/timeBehavior/TimeBehaviour.cpp \
    main.cpp

HEADERS += \
    gui/mainwindow.h \
    core/src/application/Application.hpp \
    core/src/buffer/Buffer.hpp \
    core/src/functional/FunctionalModule.hpp \
    core/src/handler/Handler.hpp \
    core/src/source/Source.hpp \
    core/src/strategies/addition/AdditionStrategy.hpp \
    core/src/strategies/addition/FreeAddition.hpp \
    core/src/strategies/selection/RingSelection.hpp \
    core/src/strategies/selection/SelectionStrategy.hpp \
    core/src/strategies/timeBehavior/TimeBehaviour.hpp

FORMS += \
    gui/mainwindow.ui

RESOURCES += \

