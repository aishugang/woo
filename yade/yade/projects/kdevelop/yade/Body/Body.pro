# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./yade/Body
# Target is a library:  

LIBS += -rdynamic 
INCLUDEPATH = $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Body.hpp \
           ConnexBody.hpp \
           NonConnexBody.hpp \
           BodyContainer.hpp 
SOURCES += Body.cpp \
           ConnexBody.cpp \
           NonConnexBody.cpp \
           BodyContainer.cpp 
