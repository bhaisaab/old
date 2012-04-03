#!/bin/sh

GTK_FILE="gtk+-bundle_2.22.0-20101016_win32.zip"
GTK_URL="http://ftp.gnome.org/pub/gnome/binaries/win32/gtk+/2.22/gtk+-bundle_2.22.0-20101016_win32.zip"

ROOT_FOLDER=`pwd`
DOWNLOADS_FOLDER=$ROOT_FOLDER/downloads

# Get the dependencies, Qt
mkdir -p $DOWNLOADS_FOLDER
cd $DOWNLOADS_FOLDER

if [ ! -f $GTK_FILE ]; then
    wget $GTK_URL ;
else
    echo "Gtk+ 2.xx OK";
fi

cd $ROOT_FOLDER

# Now set up contribs
