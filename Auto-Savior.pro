#-------------------------------------------------
#
# Project created by QtCreator 2018-10-05T12:31:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Auto-Savior
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        login_interface.cpp \
    create_dash_account.cpp \
    forgot_dash_password.cpp \
    website_lobby.cpp \
    about.cpp \
    search_password.cpp \
    add_websites.cpp \
    change_password_website.cpp

HEADERS += \
        login_interface.h \
    create_dash_account.h \
    forgot_dash_password.h \
    website_lobby.h \
    about.h \
    search_password.h \
    add_websites.h \
    change_password_website.h

FORMS += \
        login_interface.ui \
    create_dash_account.ui \
    forgot_dash_password.ui \
    website_lobby.ui \
    about.ui \
    search_password.ui \
    add_websites.ui \
    change_password_website.ui

RESOURCES += \
    Resource/src.qrc
