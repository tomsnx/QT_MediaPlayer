QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    customtable.cpp \
    videoArea.cpp \
    main.cpp \
    mainwindow.cpp \
    menubar.cpp \
    playerbar.cpp \
    sidebar.cpp

HEADERS += \
    button.h \
    customtable.h \
    videoArea.h \
    mainwindow.h \
    menubar.h \
    playerbar.h \
    sidebar.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    MediaPlayer_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/icons/mediaplayer.icns

RESOURCES += \
    resources.qrc

ICON = mediaplayer.icns
