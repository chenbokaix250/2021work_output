TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ModuleC
DESTDIR += ../../../bin/



CONFIG(debug, debug|release) {
    OBJECTS_DIR = ./tmp_Debug
}
CONFIG(release, debug|release) {
    OBJECTS_DIR = ./tmp_Release
}


SOURCES += \
    ModuleC.cc \
    ModuleCLoopmain.cc


HEADERS += \
    ModuleC.hh


INCLUDEPATH += \
    ../../message \
    /opt/rcslib/build/include \

LIBS += \
    -L/usr/local/lib \
    -L/usr/lib/x86_64-linux-gnu/ \
    -L/opt/rcslib/build/lib \
    -lrcs \
    ../../../lib/libTest.a \

