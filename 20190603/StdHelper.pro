#-------------------------------------------------
#
# Project created by QtCreator 2019-04-29T21:59:46
#
#-------------------------------------------------

QT       += core gui \
            network
RC_ICONS = icon/brain.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StdHelper
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

CONFIG += c++11

SOURCES += \
        Login.cpp \
        addclassdialog.cpp \
        classtable.cpp \
        classtableitem.cpp \
        link.cpp \
        main.cpp \
        mainwindow.cpp \
        qgraphicstableitem.cpp \
        sectionscombobox.cpp \
        sectionscomboboxdelegate.cpp \
        selectweekdialog.cpp \
        settingwindow.cpp \
        subclass.cpp \
        tablecolumn.cpp \
        tableitem.cpp \
        timeeditdelegate.cpp \
        weekbuttondelegate.cpp \
        weekcomboboxdelegate.cpp

HEADERS += \
        Login.h \
        addclassdialog.h \
        classtable.h \
        classtableitem.h \
        link.h \
        qgraphicstableitem.h \
        sectionscombobox.h \
        sectionscomboboxdelegate.h \
        selectweekdialog.h \
        settingwindow.h \
        subclass.h \
        tablecolumn.h \
        tableitem.h \
        mainwindow.h \
        timeeditdelegate.h \
        weekbuttondelegate.h \
        weekcomboboxdelegate.h

FORMS += \
        Login.ui \
        addclassdialog.ui \
        mainwindow.ui \
        sectionscombobox.ui \
        selectweekdialog.ui \
        settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
