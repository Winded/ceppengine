TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/math/angle.cpp \
    src/math/lrand.cpp \
    src/math/math.cpp \
    src/math/matrix4.cpp \
    src/math/transform.cpp \
    src/math/vector3.cpp

HEADERS += \
    src/math/angle.h \
    src/math/lrand.h \
    src/math/math.h \
    src/math/matrix4.h \
    src/math/transform.h \
    src/math/vector3.h \
    src/global.h
