HEADERS += \
    mainwindow.h \
    modelexml.h \
    xmlfilemanager.h \
    arbo.h \
    texthighlighter.h \
    notepad.h \
    iconbar.h \
    logger.h \
    xmleditor.h \
    dtdeditor.h \
    texteditor.h

SOURCES += \
    mainwindow.cpp \
    modelexml.cpp \
    xmlfilemanager.cpp \
    main.cpp \
    arbo.cpp \
    texthighlighter.cpp \
    notepad.cpp \
    iconbar.cpp \
    logger.cpp \
    xmleditor.cpp \
    dtdeditor.cpp \
    texteditor.cpp

QT += widgets
QT += xml
QT += xmlpatterns

CONFIG += qt

QMAKE_CXXFLAGS += -std=c++11
