CONFIG += console c++11
CONFIG -= app_bundle

INCLUDEPATH += /usr/local/opt/llvm/include

QMAKE_CXX = /usr/local/Cellar/llvm/3.9.1/bin/clang++
QMAKE_CXXFLAGS += -march=native -O3
QMAKE_CXXFLAGS += -fopenmp

QMAKE_LFLAGS += /usr/local/opt/llvm/lib/libiomp5.dylib

TEMPLATE = app
SOURCES += main.cpp \


###  COMMON  ###################################################################

HEADERS +=\
common/common.h \
common/boundingbox.h \
common/brdfread.h \
common/color.h \
common/kdtree.h \
common/progressbar.h \
common/ray.h \
common/texture.h \
common/vector2d.h \
common/vector3d.h \

SOURCES +=\
common/boundingbox.cpp \
common/kdtree.cpp \
common/progressbar.cpp \
common/texture.cpp \



###  CAMERA  ###################################################################

HEADERS +=\
camera/camera.h \
camera/perspectivecamera.h \
camera/omnidirectionalcamera.h \

SOURCES += \
camera/perspectivecamera.cpp \
camera/omnidirectionalcamera.cpp \


###  LIGHT  ####################################################################

HEADERS +=\
light/directionallight.h \
light/light.h \
light/pointlight.h \
light/spotlight.h \
light/ambientlight.h \

SOURCES +=\
light/directionallight.cpp \
light/pointlight.cpp \
light/spotlight.cpp \
light/ambientlight.cpp \



###  PRIMITIVE  ################################################################

HEADERS +=\
primitive/primitive.h \
primitive/infiniteplane.h \
primitive/objmodel.h \
primitive/sphere.h \
primitive/smoothtriangle.h \
primitive/triangle.h \
primitive/texturedtriangle.h \

SOURCES +=\
primitive/infiniteplane.cpp \
primitive/objmodel.cpp \
primitive/sphere.cpp \
primitive/smoothtriangle.cpp \
primitive/triangle.cpp \
primitive/texturedtriangle.cpp \



###  RENDERER  #################################################################

HEADERS +=\
renderer/backgroundrenderer.h \
renderer/depthrenderer.h \
renderer/desaturationrenderer.h \
renderer/renderer.h \
renderer/hazerenderer.h \
renderer/simplerenderer.h \
renderer/superrenderer.h \
renderer/depthoffieldrenderer.h \

SOURCES +=\
renderer/backgroundrenderer.cpp \
renderer/depthrenderer.cpp \
renderer/desaturationrenderer.cpp \
renderer/hazerenderer.cpp \
renderer/simplerenderer.cpp \
renderer/superrenderer.cpp \
renderer/depthoffieldrenderer.cpp \



###  SCENE  ####################################################################

HEADERS +=\
scene/scene.h \
scene/simplescene.h \

SOURCES +=\
scene/scene.cpp \
scene/simplescene.cpp \



###  SHADER  ###################################################################

HEADERS +=\
shader/brdfshader.h \
shader/shader.h \
shader/flatshader.h \
shader/materialshader.h \
shader/phongshader.h \
shader/lambertshader.h \
shader/mirrorshader.h \
shader/refractionshader.h \
shader/simpleshadowshader.h \
shader/toonshader.h \


SOURCES +=\
shader/brdfshader.cpp \
shader/flatshader.cpp \
shader/materialshader.cpp \
shader/phongshader.cpp \
shader/lambertshader.cpp \
shader/mirrorshader.cpp \
shader/refractionshader.cpp \
shader/simpleshadowshader.cpp \
shader/toonshader.cpp \
