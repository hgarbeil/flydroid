#############################################################################
# Makefile for building: beaglebone
# Generated by qmake (2.01a) (Qt 4.8.2) on: Wed Feb 5 13:02:27 2014
# Project:  beaglebone.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile beaglebone.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/hbeta/harold/workdir/build-qwt-beaglebone-Debug/include -I/usr/local/include/seabreeze -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/arm-linux-gnueabihf -L/hbeta/harold/workdir/build-qwt-beaglebone-Debug/lib -lqwt-qt4 -L/home/harold/workdir/seabreeze-17Nov09/seabreeze -lseabreeze -lphidget21 -L/hbeta/harold/workdir/nmealib/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		myplot.cpp \
		myspectrometer.cpp \
		phidgetsMot.cpp \
		calscan.cpp \
		gpsinfodialog.cpp \
		mygps.cpp \
		nmea.cpp moc_mainwindow.cpp \
		moc_myplot.cpp \
		moc_myspectrometer.cpp \
		moc_calscan.cpp \
		moc_gpsinfodialog.cpp \
		moc_mygps.cpp
OBJECTS       = main.o \
		mainwindow.o \
		myplot.o \
		myspectrometer.o \
		phidgetsMot.o \
		calscan.o \
		gpsinfodialog.o \
		mygps.o \
		nmea.o \
		moc_mainwindow.o \
		moc_myplot.o \
		moc_myspectrometer.o \
		moc_calscan.o \
		moc_gpsinfodialog.o \
		moc_mygps.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		beaglebone.pro
QMAKE_TARGET  = beaglebone
DESTDIR       = 
TARGET        = beaglebone

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_gpsinfodialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: beaglebone.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/arm-linux-gnueabihf/libQtGui.prl \
		/usr/lib/arm-linux-gnueabihf/libQtCore.prl
	$(QMAKE) -o Makefile beaglebone.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/arm-linux-gnueabihf/libQtGui.prl:
/usr/lib/arm-linux-gnueabihf/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile beaglebone.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/beaglebone1.0.0 || $(MKDIR) .tmp/beaglebone1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/beaglebone1.0.0/ && $(COPY_FILE) --parents mainwindow.h myplot.h myspectrometer.h phidgetsMot.h calscan.h gpsinfodialog.h mygps.h nmea.h .tmp/beaglebone1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp myplot.cpp myspectrometer.cpp phidgetsMot.cpp calscan.cpp gpsinfodialog.cpp mygps.cpp nmea.cpp .tmp/beaglebone1.0.0/ && $(COPY_FILE) --parents mainwindow.ui gpsinfodialog.ui .tmp/beaglebone1.0.0/ && (cd `dirname .tmp/beaglebone1.0.0` && $(TAR) beaglebone1.0.0.tar beaglebone1.0.0 && $(COMPRESS) beaglebone1.0.0.tar) && $(MOVE) `dirname .tmp/beaglebone1.0.0`/beaglebone1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/beaglebone1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_myplot.cpp moc_myspectrometer.cpp moc_calscan.cpp moc_gpsinfodialog.cpp moc_mygps.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_myplot.cpp moc_myspectrometer.cpp moc_calscan.cpp moc_gpsinfodialog.cpp moc_mygps.cpp
moc_mainwindow.cpp: myspectrometer.h \
		phidgetsMot.h \
		calscan.h \
		myplot.h \
		mygps.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_myplot.cpp: myplot.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) myplot.h -o moc_myplot.cpp

moc_myspectrometer.cpp: myspectrometer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) myspectrometer.h -o moc_myspectrometer.cpp

moc_calscan.cpp: myspectrometer.h \
		phidgetsMot.h \
		myplot.h \
		calscan.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) calscan.h -o moc_calscan.cpp

moc_gpsinfodialog.cpp: mygps.h \
		gpsinfodialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gpsinfodialog.h -o moc_gpsinfodialog.cpp

moc_mygps.cpp: mygps.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mygps.h -o moc_mygps.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_gpsinfodialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_gpsinfodialog.h
ui_mainwindow.h: mainwindow.ui \
		myplot.h
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

ui_gpsinfodialog.h: gpsinfodialog.ui
	/usr/bin/uic-qt4 gpsinfodialog.ui -o ui_gpsinfodialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		myspectrometer.h \
		phidgetsMot.h \
		calscan.h \
		myplot.h \
		mygps.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		myspectrometer.h \
		phidgetsMot.h \
		calscan.h \
		myplot.h \
		mygps.h \
		ui_mainwindow.h \
		gpsinfodialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

myplot.o: myplot.cpp myplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myplot.o myplot.cpp

myspectrometer.o: myspectrometer.cpp myspectrometer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myspectrometer.o myspectrometer.cpp

phidgetsMot.o: phidgetsMot.cpp phidgetsMot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o phidgetsMot.o phidgetsMot.cpp

calscan.o: calscan.cpp calscan.h \
		myspectrometer.h \
		phidgetsMot.h \
		myplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calscan.o calscan.cpp

gpsinfodialog.o: gpsinfodialog.cpp gpsinfodialog.h \
		mygps.h \
		ui_gpsinfodialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gpsinfodialog.o gpsinfodialog.cpp

mygps.o: mygps.cpp mygps.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mygps.o mygps.cpp

nmea.o: nmea.cpp nmea.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nmea.o nmea.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_myplot.o: moc_myplot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myplot.o moc_myplot.cpp

moc_myspectrometer.o: moc_myspectrometer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myspectrometer.o moc_myspectrometer.cpp

moc_calscan.o: moc_calscan.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_calscan.o moc_calscan.cpp

moc_gpsinfodialog.o: moc_gpsinfodialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gpsinfodialog.o moc_gpsinfodialog.cpp

moc_mygps.o: moc_mygps.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mygps.o moc_mygps.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/home/root/programs/ || $(MKDIR) $(INSTALL_ROOT)/home/root/programs/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/home/root/programs/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/home/root/programs/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/home/root/programs/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:
