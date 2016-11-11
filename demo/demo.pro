TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

unix|win32: LIBS += -L$$PWD/../lib/ -llibEGL -llibGLESv2

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-CeppEngine/release/ -lCeppEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-CeppEngine/debug/ -lCeppEngine
else:unix: LIBS += -L$$PWD/../build-CeppEngine/ -lCeppEngine

INCLUDEPATH += $$PWD/../ceppengine/src
DEPENDPATH += $$PWD/../ceppengine/src

msvc: LIBS += -luser32
msvc: LIBS += -lgdi32
