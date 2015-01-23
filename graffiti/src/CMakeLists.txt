#
# Graffiti build system
# Authors: Rohit Yadav <rohit@scaleninja.com>
#

SET(GRAFFITI_SRCS # Put here cpp files
    chatdialog.cpp
    client.cpp
    connection.cpp
    gingerthread.cpp
    Main/main.cpp
    oliveinterface.cpp
    peermanager.cpp
    server.cpp
    qrc_iceqube.cpp
    Whiteboard/graffitiwriter.cpp
    Whiteboard/graffitireader.cpp
    Whiteboard/preview.cpp
    Whiteboard/graffitiarea.cpp
    Whiteboard/graffiti.cpp)

#IF (WIN32)
#    LIST ( APPEND GRAFFITI_SRCS Main/wingraffiti.cpp )
#ELSE (WIN32)
#    LIST( APPEND GRAFFITI_SRCS Main/graffiti.cpp )
#ENDIF(WIN32)

SET (GRAFFITI_HDRS # Put here Headers
    chatdialog.h
    client.h
    connection.h
    gingerthread.h
    oliveinterface.h
    peermanager.h
    server.h
    Whiteboard/preview.h
    Whiteboard/graffitiarea.h
    Whiteboard/graffiti.h)

SET(GRAFFITI_RCC
    ../resources.qrc
    #../ts/resources-ts.qrc
  )

# Include paths for graffiti
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src
  .
  graffiti
  Gui
  Main
  Whiteboard)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

     
SET(GRAFFITI_UIS # Add here ui files
    Gui/MainWindow.ui)

QT4_WRAP_UI(GRAFFITI_UIS_H ${GRAFFITI_UIS})
QT4_ADD_RESOURCES(GRAFFITI_RCC_SRCS ${GRAFFITI_RCC})
QT4_WRAP_CPP(GRAFFITI_MOC_SRCS ${GRAFFITI_HDRS})

IF( MINGW )
    # resource compilation for MinGW
    ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/icon.o
        COMMAND ${CMAKE_WINDRES} -I${CMAKE_SOURCE_DIR} -i${CMAKE_SOURCE_DIR}/cmake/icon.rc
        -o ${CMAKE_CURRENT_BINARY_DIR}/icon.o )
    SET(GRAFFITI_SRCS ${GRAFFITI_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/icon.o)
    SET(LINK_FLAGS -Wl,-subsystem,windows)
ENDIF( MINGW )

IF( WIN32 )
    SET( GUI_TYPE WIN32 )
ENDIF( WIN32 )

IF( APPLE )
    SET( GUI_TYPE MACOSX_BUNDLE )
    SET(GRAFFITI_SRCS ${GRAFFITI_SRCS} ../share/graffiti.icns)
    SET_SOURCE_FILES_PROPERTIES(../share/graffiti.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources)
    SET(MACOSX_BUNDLE_ICON_FILE graffiti.icns)
ENDIF( APPLE )

ADD_EXECUTABLE( graffiti ${GRAFFITI_SRCS} ${GRAFFITI_MOC_SRCS} ${GRAFFITI_UIS_H} ${GRAFFITI_RCC_SRCS} )
TARGET_LINK_LIBRARIES( graffiti ${GRAFFITI_LIBS} )

#ADD_DEPENDENCIES( GRAFFITI translations )

INSTALL(TARGETS graffiti
        BUNDLE  DESTINATION ${GRAFFITI_BIN_DIR}
        RUNTIME DESTINATION ${GRAFFITI_BIN_DIR})

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_SOURCE_DIR}/bin/graffiti
    COMMAND ${CMAKE_COMMAND} copy ${CMAKE_CURRENT_SOURCE_DIR}/graffiti ${CMAKE_SOURCE_DIR}/bin/graffiti
    DEPENDS ${CMAKE_BINARY_DIR}/src/graffiti)

ADD_DEFINITIONS( -W -Wall )

IF(UNIX)
    IF (WITH_PROFILING)
        ADD_DEFINITIONS( -pg )
        SET_TARGET_PROPERTIES( graffiti PROPERTIES LINK_FLAGS -pg )
    ENDIF(WITH_PROFILING)
ENDIF(UNIX)

IF( APPLE )
    ADD_CUSTOM_COMMAND(
        TARGET graffiti
        POST_BUILD
        COMMAND cp -r ${CMAKE_SOURCE_DIR}/contribs/* ${CMAKE_CURRENT_BINARY_DIR}/../bin/Graffiti.app/Contents/MacOS
    )

    ADD_CUSTOM_COMMAND(
        TARGET graffiti
        POST_BUILD
        COMMAND macdeployqt ${CMAKE_CURRENT_BINARY_DIR}/../bin/Graffiti.app -no-plugins #-dmg
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Deploying the Qt Framework onto the bundle"
    )
ENDIF( APPLE )
