TEMPLATE += app
QT += widgets script
CONFIG += C++17
QMAKE_CXXFLAGS += -std=c++1z

CONFIG(debug, debug|release) {
    unix:DESTDIR = ../debug/unix
    unix:OBJECTS_DIR = ../debug/unix/objects
    unix:MOC_DIR = ../debug/unix/moc
    unix:RCC_DIR = ../debug/unix/moc
    TARGET = GetSunsetRiseProd
    win32:DESTDIR = ../debug/win32
    win32:OBJECTS_DIR = ../debug/win32/objects
    win32:MOC_DIR = ../debug/win32/moc
    win32:RCC_DIR = ../debug/win32/moc
} else {
unix:DESTDIR = ../release/unix
    unix:OBJECTS_DIR = ../release/unix/objects
    unix:MOC_DIR = ../release/unix/moc
    unix:RCC_DIR = ../release/unix/moc
    TARGET = GetSunsetRisePro
    win32:DESTDIR = ../release/win32
    win32:OBJECTS_DIR = ../release/win32/objects
    win32:MOC_DIR = ../release/win32/moc
    win32:RCC_DIR = ../release/win32/moc
}

SOURCES += main.cpp \
    GetSunsetRise.cpp \
    SunsetRise.cpp \
    functions.cpp

HEADERS += \
    GetSunsetRise.h \
    SunsetRise.h \
    functions.h

FORMS += \
    GetSunsetRise.ui

RESOURCES += \
    GetSunsetRise.qrc
