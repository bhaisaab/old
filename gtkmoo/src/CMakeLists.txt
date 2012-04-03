#
# GtkMoo
# The Game of Bulls n Cows written in C using Gtk+. 
#
# Author: Rohit Yadav <rohityadav89 AT gmail.com>
#

SET(GTKMOO_SRCS
  main.cpp
  mooGui.cpp
  mooGame.cpp
  mooAbout.cpp
  mooGuessTable.cpp
  mooInputBox.cpp
  mooLevel.cpp
  mooMenuBar.cpp
  mooStatusBar.cpp
  mooToolBar.cpp
  mooRules.cpp
)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src
  .
)

ADD_EXECUTABLE(gtkmoo ${GTKMOO_SRCS})
TARGET_LINK_LIBRARIES(gtkmoo ${LIBS})

INSTALL(TARGETS gtkmoo
        BUNDLE  DESTINATION ${GTKMOO_BIN_DIR}
        RUNTIME DESTINATION ${GTKMOO_BIN_DIR})

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_SOURCE_DIR}/bin/gtkmoo
    COMMAND ${CMAKE_COMMAND} copy ${CMAKE_CURRENT_SOURCE_DIR}/gtkmoo ${CMAKE_SOURCE_DIR}/bin/gtkmoo
    DEPENDS ${CMAKE_BINARY_DIR}/src/gtkmoo
)

ADD_DEFINITIONS(-W -Wall)

