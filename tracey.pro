CONFIG += console c++11

TEMPLATE = app
SOURCES += main.cpp



###  COMMON  ###################################################################

HEADERS +=\
common/common.h \
common/boundingbox.h \
common/color.h \
common/ray.h \
common/texture.h \
common/vector2d.h \
common/vector3d.h

SOURCES +=\
common/boundingbox.cpp \
common/color.cpp\
common/texture.cpp \
common/vector2d.cpp \
common/vector3d.cpp \



###  CAMERA  ###################################################################

HEADERS +=\
camera/camera.h \
camera/perspectivecamera.h \

SOURCES += \
camera/perspectivecamera.cpp \



###  LIGHT  ####################################################################

HEADERS +=\
light/light.h \
light/pointlight.h \
light/spotlight.h \
light/ambientlight.h \

SOURCES +=\
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

SOURCES +=\
primitive/infiniteplane.cpp \
primitive/objmodel.cpp \
primitive/sphere.cpp \
primitive/smoothtriangle.cpp \
primitive/triangle.cpp \



###  RENDERER  #################################################################

HEADERS +=\
renderer/renderer.h \
renderer/simplerenderer.h \

SOURCES +=\
renderer/simplerenderer.cpp \



###  SCENE  ####################################################################

HEADERS +=\
scene/scene.h \
scene/simplescene.h \

SOURCES +=\
scene/scene.cpp \
scene/simplescene.cpp \



###  SHADER  ###################################################################

HEADERS +=\
shader/shader.h \
shader/flatshader.h \
shader/lambertshader.h \
shader/mirrorshader.h \
shader/refractionshader.h \
shader/simpleshadowshader.h \

SOURCES +=\
shader/flatshader.cpp \
shader/lambertshader.cpp \
shader/mirrorshader.cpp \
shader/refractionshader.cpp \
shader/simpleshadowshader.cpp \

