TEMPLATE = lib
CONFIG += static c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/ceppengine/math/angle.cpp \
    src/ceppengine/math/lrand.cpp \
    src/ceppengine/math/math.cpp \
    src/ceppengine/math/matrix4.cpp \
    src/ceppengine/math/transform.cpp \
    src/ceppengine/math/vector3.cpp \
    src/ceppengine/object.cpp \
    src/ceppengine/gameobject.cpp \
    src/ceppengine/engine.cpp \
    src/ceppengine/assets/assetloader.cpp \
    src/ceppengine/modules/module.cpp \
    src/ceppengine/scene.cpp

HEADERS += \
    src/ceppengine/math/angle.h \
    src/ceppengine/math/lrand.h \
    src/ceppengine/math/math.h \
    src/ceppengine/math/matrix4.h \
    src/ceppengine/math/transform.h \
    src/ceppengine/math/vector3.h \
    src/ceppengine/global.h \
    src/ceppengine/util/ref.h \
    src/ceppengine/object.h \
    src/ceppengine/gameobject.h \
    src/ceppengine/engine.h \
    src/ceppengine/assets/assetloader.h \
    src/ceppengine/modules/module.h \
    src/ceppengine/scene.h
