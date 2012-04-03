# wxMakefile v8.12.4 
# By
# Rohit Yadav
# Copyright 2008

APP=IceCuBe
SRC="main.cpp mainframe.cpp splash.cpp statusbar.cpp"

if [ "$1" = "1" ]
then
	echo "Cleaning Previous Build"
	rm -frv $APP.app
else

g++ $SRC -o $APP \
-I/Users/Rohit/wxMac-2.8.9/build-release/lib/wx/include/mac-ansi-release-static-2.8 \
-I/Users/Rohit/wxMac-2.8.9/include -I/Users/Rohit/wxMac-2.8.9/contrib/include \
-D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXMAC__ \
-L/Users/Rohit/wxMac-2.8.9/build-release/lib \
-framework IOKit -framework Carbon -framework Cocoa -framework System \
-framework QuickTime -framework OpenGL -framework AGL  \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_richtext-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_aui-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_xrc-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_qa-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_html-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_adv-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_mac_core-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_base_carbon_xml-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_base_carbon_net-2.8.a \
/Users/Rohit/wxMac-2.8.9/build-release/lib/libwx_base_carbon-2.8.a \
-framework WebKit -lwxregex-2.8 -lwxexpat-2.8 -lwxtiff-2.8 \
-lwxjpeg-2.8 -lwxpng-2.8 -lwxzlib-2.8 -lpthread -liconv

mkdir -p $APP.app
mkdir -p $APP.app/Contents
mkdir -p $APP.app/Contents/MacOS
mkdir -p $APP.app/Contents/Resources
cp -f ./Mac/icon.icns $APP.app/Contents/Resources/icon.icns
cp -f ./Mac/Info.plist $APP.app/Contents/Info.plist
cp -f ./Mac/PkgInfo $APP.app/Contents/PkgInfo
mv $APP $APP.app/Contents/MacOS
chmod +x $APP.app
echo "$APP.app Made!!!"
fi