
TARGET = QtRoot

TEMPLATE = lib
CONFIG  += plugin
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_EXTENSION_SHLIB = so


QTROOTDIRI = inc
QTROOTDIRS = src

OBJECTS_DIR = obj
#UI_DIR = .ui
#MOC_DIR = .moc

# Input
HEADERS += $$QTROOTDIRI/TQtRootGuiFactory.h
SOURCES += $$QTROOTDIRS/TQtRootGuiFactory.cxx

INCLUDEPATH += $$PWD/$$QTROOTDIRI $$PWD/../qt-root/inc
DEPENDPATH  += $$PWD/$$QTROOTDIRI $$PWD/../qt-root/inc
LIBS += $$PWD/../../../lib/libGQt.so
#LIBS += /Users/pospelov/nest/software/root/qtroot/qtroot/libGQt.dylib
#INCLUDEPATH +=$$PWD/$$QTROOTDIRI   /Users/pospelov/nest/software/root/qtroot/qtroot/qt/inc


# -----------------------------------------------------------------------------
# adding ROOT libraries
# -----------------------------------------------------------------------------
MYROOT = $$(ROOTSYS)
isEmpty(MYROOT) {
  message("Warning, ROOTSYS environment variable doesn't exist, trying to guess location")
  ROOT_CONFIG_FILE = root-config
  ROOT_CONFIG_FILE_LOCATIONS = /opt/local /usr/local /usr
  for(dir, ROOT_CONFIG_FILE_LOCATIONS): isEmpty(MYROOT): exists($${dir}/bin/$${ROOT_CONFIG_FILE}): MYROOT = $${dir}
  isEmpty(MYROOT): error("Can't find" $${ROOT_CONFIG_FILE} "in" $${ROOT_CONFIG_FILE_LOCATIONS})
  message("Probable ROOTSYS is" $${MYROOT})
}
!isEmpty(MYROOT) {
  !exists($${MYROOT}/bin/root-config): error("No config file "$${MYROOT}/bin/root-config)
  INCLUDEPATH += $$system($${MYROOT}/bin/root-config --incdir)
  #LIBS += $$system($${MYROOT}/bin/root-config --glibs )
  LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lGraf -lGpad -lRint -lpthread -lm -ldl
  MYROOTCINT = $${MYROOT}/bin/rootcint
}

# -----------------------------------------------------------------------------
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
# -----------------------------------------------------------------------------
CREATE_ROOT_DICT_FOR_CLASSES  = $$HEADERS $$QTROOTDIRI/LinkDef.h


DICTDEFINES += -DQT_VERSION=0x50000
QT_VERSION=$$[QT_VERSION]
contains( QT_VERSION, "^4.*" ) {
  DICTDEFINES -= -DQT_VERSION=0x50000
  DICTDEFINES *= -DQT_VERSION=0x40000
}
ROOT_CINT_TARGET = $${TARGET}
SOURCES         *= src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.target       = src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.commands    += $$MYROOTCINT
rootcint.commands    +=  -f $$rootcint.target  -c -I./inc $$CREATE_ROOT_DICT_FOR_CLASSES
#rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES

rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"
QMAKE_EXTRA_TARGETS += rootcintecho rootcint
QMAKE_CLEAN       +=  src/$${ROOT_CINT_TARGET}Dict.cpp src/$${ROOT_CINT_TARGET}Dict.h
QMAKE_DISTCLEAN  += $$PWD/obj/*.o

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_DISTCLEAN  += $$PWD/obj/*.o
QMAKE_POST_LINK = (make install)




######################################################################
# Automatically generated by qmake (1.07a) Mon Jun 20 18:27:55 2005
######################################################################
#TEMPLATE = lib

#CONFIG += thread dll
#CONFIG += create_prl

#TARGET = QtRoot

#QTROOTSYSPATHINSTALL = $(QTROOTSYSDIR)

#isEmpty(DESTDIR) {
#  DESTDIR=..
#}
#isEmpty(QTROOTSYSPATHINSTALL) {
#  QTROOTSYSPATHINSTALL = $$DESTDIR
#}

#QTROOTSYSDIR=$$DESTDIR

#GQTDIRI   = ../qt/inc

#QTROOTDIRS   = src
#QTROOTDIRI   = inc

#DEPENDPATH += $$QTROOTDIRI $$QTROOTDIRS
#INCLUDEPATH +=  $$QTROOTDIRI $$GQTDIRI

#unix {
#  LIBS += -L..
#}
## Input
#HEADERS += $$QTROOTDIRI/TQtRootGuiFactory.h
#SOURCES += $$QTROOTDIRS/TQtRootGuiFactory.cxx
           
#CREATE_ROOT_DICT_FOR_CLASSES  = $$HEADERS $$QTROOTDIRI/LinkDef.h

#!exists ($$GQTDIRI/rootcintrule.pri){
#     message "The rootcintrule.pri was not found"
#}
#exists ($$GQTDIRI/rootcintrule.pri){
#    include ($$GQTDIRI/rootcintrule.pri)
#}

#mac {
#    !exists ($$GQTDIRI/rootlibs.pri){
#        message "The rootlibs.pri was not found"
#    }
#    exists ($$GQTDIRI/rootlibs.pri){
#       include ($$GQTDIRI/rootlibs.pri)
#    }
##    LIBS -= -lGQt
#}

#headerfiles.path   = $$QTROOTSYSPATHINSTALL/include
#headerfiles.files = $$QTROOTDIRI/*.*
#headerfiles.files -= $$QTROOTDIRI/LinkDef.h
#target.path = $$QTROOTSYSPATHINSTALL/lib

#INSTALLS += headerfiles target


#DISTFILES += LICENSE.QPL Module.mk

#unix {
##  -- working directory
  
#  ROOTCINT_DIR = .rootcint
#  UI_DIR = .ui
#  MOC_DIR = .moc
#  OBJECTS_DIR = .obj

#}
##The following line was inserted by qt3to4
#QT += qt3support