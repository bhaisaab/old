#!/bin/sh

BIN="bin/gtkmoo"
if [ -f $BIN ]; then
    exec $BIN "$@"
else
    echo "GtkMoo not build, read INSTALL first"
fi
