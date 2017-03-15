#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T15:05:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OOP_L10
TEMPLATE = app


SOURCES += main.cpp\
    Domain/medicament.cpp \
    Teste/tests.cpp \
    UI/meniu.cpp \
    gui_w.cpp

HEADERS  += \
    Controller/controller.h \
    Domain/medicament.h \
    Repository/Repository.h \
    Teste/tests.h \
    UI/meniu.h \
    Undo/Undo.h \
    Utilities/Iterator.h \
    Utilities/VectorDinamic.h \
    gui_w.h \
    gui_cos.h \
    observer.h \
    gui_graphic.h \
    model.h

FORMS    += widget.ui
