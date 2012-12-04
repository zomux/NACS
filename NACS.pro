QT += webkit
QT += network
TARGET = NACS
TEMPLATE = app
SOURCES += main.cpp \
    browser.cpp \
    nacsif.cpp \
    nacs_func.cpp \
    nacs.cpp \
    dialoglogin.cpp \
    insrdrv.cpp
HEADERS += browser.h \
    nacsif.h \
    nacs_func.h \
    nacs.h \
    dialoglogin.h \
    insrdrv.h
RESOURCES = systray.qrc
FORMS += dialoglogin.ui
OTHER_FILES += 
LIBS += -lole32
LIBS += -luuid
