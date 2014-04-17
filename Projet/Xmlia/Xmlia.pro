HEADERS += \
    mainwindow.h \
    modelexml.h \
    xmlfilemanager.h \
    attribute.h \
    arbo.h \
    texthighlighter.h \
    notepad.h \
    iconbar.h

SOURCES += \
    mainwindow.cpp \
    modelexml.cpp \
    xmlfilemanager.cpp \
    main.cpp \
    attribute.cpp \
    arbo.cpp \
    texthighlighter.cpp \
    notepad.cpp \
    iconbar.cpp

QT += widgets
QT += xml

CONFIG += qt

QMAKE_CXXFLAGS += -std=c++11
