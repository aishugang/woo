# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/CollisionFunctor/CollisionFunctor4ErrorTolerant/Box2Sphere4ErrorTolerant
# Target is a library:  

LIBS += -lBody \
        -lEngine \
        -lInteraction \
        -lGeometry \
        -lMultiMethods \
        -lFactory \
        -lMath \
        -lErrorTolerantContactModel \
        -lSerialization \
        -lBox \
        -lSphere \
        -rdynamic 
INCLUDEPATH = $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../yade/Body/$(YADEDYNLIBPATH) \
               ../../../../yade/Engine/$(YADEDYNLIBPATH) \
               ../../../../yade/Interaction/$(YADEDYNLIBPATH) \
               ../../../../yade/Geometry/$(YADEDYNLIBPATH) \
               ../../../../yade/MultiMethods/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Libraries/Factory/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Libraries/Math/$(YADEDYNLIBPATH) \
               ../../../../plugins/InteractionModel/ErrorTolerantContactModel/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../../plugins/GeometricalModel/Box/$(YADEDYNLIBPATH) \
               ../../../../plugins/GeometricalModel/Sphere/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Box2Sphere4ErrorTolerant.hpp 
SOURCES += Box2Sphere4ErrorTolerant.cpp 
