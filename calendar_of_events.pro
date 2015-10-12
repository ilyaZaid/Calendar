#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T11:01:05
#
#-------------------------------------------------

QT       += core gui xml

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calendar_of_events
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../CalendarWidget/calendarofevents.cpp \
    ../../EventsWidget/events.cpp \
    ../../EventsWidget/comboboxdelegate.cpp \
    ../../EventsWidget/designationdialog.cpp

HEADERS  += mainwindow.h \
    ../../CalendarWidget/calendarofevents.h \
    ../../CalendarWidget/labelbutton.h \
    ../../EventsWidget/events.h \
    ../../EventsWidget/comboboxdelegate.h \
    ../../EventsWidget/designationdialog.h

FORMS    += mainwindow.ui
