# AutoQt Makefile.am Example 
# Author: Rohit Yadav <rohityadav89@gmail.com>

#Debug options
DEBUG = -g -O0

#AUTOMAKE_OPTIONS = foreign
AUTOMAKE_OPTIONS = subdir-objects
MOSTLYCLEANFILES = $(UIH)
SUFFIXES = .ui .h .moc.cpp

#Add here custom CPP flags
AM_CPPFLAGS = \
    $(QTCORE_CFLAGS) \
    $(QTGUI_CFLAGS) \
    $(QTSVG_CFLAGS)

#Name of the Bin/Output
bin_PROGRAMS = autoqt

#LD Flags
autoqt_LDFLAGS = -export-dynamic

#Link
autoqt_LDADD = \
    $(QTCORE_LIBS) \
    $(QTGUI_LIBS) \
    $(QTSVG_LIBS)

autoqt_SOURCES = \
    main.cpp \
    resources.cpp \
    autoqt.cpp \
    autoqt.h

#Put here files that will be generated from moc and uic
nodist_autoqt_SOURCES = \
    interface.h \
    autoqt.moc.cpp

BUILT_SOURCES = $(nodist_autoqt_SOURCES)

resources.cpp: resources.qrc
	$(RCC) -name resources -o $@ $<

.ui.h:
	$(UIC) $< -o $@

.h.moc.cpp:
	$(MOC) $(CPPFLAGS) -o $@ $<

EXTRA_DIST = \
    resources.qrc \
    interface.ui

CLEANFILES = \
    $(nodist_SOURCES_autoqt) \
    resources.cpp

