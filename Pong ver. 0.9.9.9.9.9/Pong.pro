QT       += gui declarative

TARGET = Pong
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameplay.cpp

HEADERS  += mainwindow.h \
    gameplay.h

FORMS    += mainwindow.ui

RESOURCES += \
    zasoby.qrc
