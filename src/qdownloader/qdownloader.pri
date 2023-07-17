# !!! important !!!
# on sailfish you must declare CONFIG += sailfishapp before the qdownloader.pri include

HEADERS += $$PWD/qdownloader.h \
    $$PWD/qdownloaderservice.h

SOURCES +=  $$PWD/qdownloader.cpp \
    $$PWD/qdownloaderservice.cpp

sailfishapp {
    QT +=  dbus
    LIBS += -lnemonotifications-qt5
}
