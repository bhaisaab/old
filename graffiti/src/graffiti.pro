# #####################################################################
# Authors: Rohit Yadav(Admin/Maintainer), Abhishek Kumar
# contact: rohityadav89 AT gmail.com
# #####################################################################

TEMPLATE = app
TARGET = graffiti

DEPENDPATH += . \
    Whiteboard
INCLUDEPATH += . \
    Whiteboard
QT += network \
    svg \
    xml

CONFIG += debug
OBJECTS_DIR = build
MOC_DIR = build/moc
UI_DIR = build/ui

HEADERS += chatdialog.h \
    client.h \
    connection.h \
    gingerthread.h \
    oliveinterface.h \
    peermanager.h \
    server.h \
    Whiteboard/graffitiwriter.h \
    Whiteboard/graffitireader.h \
    Whiteboard/preview.h \
    Whiteboard/graffitiarea.h \
    Whiteboard/graffiti.h
SOURCES += chatdialog.cpp \
    client.cpp \
    connection.cpp \
    gingerthread.cpp \
    Main/main.cpp \
    oliveinterface.cpp \
    peermanager.cpp \
    server.cpp \
    qrc_iceqube.cpp \
    Whiteboard/graffitiwriter.cpp \
    Whiteboard/graffitireader.cpp \
    Whiteboard/preview.cpp \
    Whiteboard/graffitiarea.cpp \
    Whiteboard/graffiti.cpp

FORMS += \
    Gui/MainWindow.ui
