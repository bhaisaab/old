# AutoQt
# Freedom to use in any constructive manner
# Template for GNU Build System for Qt
# http://en.wikipedia.org/wiki/GNU_build_system
# Author: Rohit Yadav <rohityadav89@gmail.com>

AC_COPYRIGHT([Copyright 2009 Rohit Yadav])
AC_INIT([autoqt], [0.1], [rohityadav89@gmail.com])
AM_INIT_AUTOMAKE( [-Wall -Werror foreign] )
AC_CONFIG_HEADERS([config.h])

# Checks for programs.

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AM_PROG_CC_C_O
AC_PROG_LIBTOOL

# Checks for libraries.
# Add more modules, XML, Networks etc...

PKG_CHECK_MODULES(QTGUI, [QtGui >= 4.4.0])
AC_SUBST(QTGUI_CFLAGS)
AC_SUBST(QTGUI_LIBS)

PKG_CHECK_MODULES(QTCORE, [QtCore >= 4.4.0])
AC_SUBST(QTCORE_CFLAGS)
AC_SUBST(QTCORE_LIBS)

PKG_CHECK_MODULES(QTSVG, [QtSvg >= 4.4.0])
AC_SUBST(QTSVG_CFLAGS)
AC_SUBST(QTSVG_LIBS)

AC_PATH_PROGS(MOC, [moc-qt4 moc], moc,`$PKG_CONFIG --variable=exec_prefix QtCore`/bin)
AC_SUBST(MOC)

AC_PATH_PROG(RCC, rcc, rcc,`$PKG_CONFIG --variable=exec_prefix QtCore`/bin)
AC_SUBST(RCC)

AC_PATH_PROGS(UIC, [uic-qt4 uic], uic,`$PKG_CONFIG --variable=exec_prefix QtCore`/bin)
AC_SUBST(UIC)

AC_CONFIG_FILES([
  Makefile
  src/Makefile
 ])

AC_OUTPUT
