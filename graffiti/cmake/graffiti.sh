#!/bin/sh

BIN="bin/graffiti"
if [ -f $BIN ]; then
    exec $BIN "$@"
else
    echo "Graffiti is not build, please read INSTALL first"
fi
