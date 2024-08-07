QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat_llfc
TEMPLATE = app
RC_ICONS = icon.ico
DESIDIR = ./bin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    register_dialog.cpp

HEADERS += \
    login_dialog.h \
    mainwindow.h \
    register_dialog.h

FORMS += \
    login_dialog.ui \
    mainwindow.ui \
    register_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc
