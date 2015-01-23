/*
    main.cpp

    IceCuBe Messenger: Graffiti Edition
    Copyright (C) 2008-09  Rohit Yadav

    The project started in early November 2008.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
*/
#include <QApplication>

#include "chatdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChatDialog window;
    window.show();
    window.setWindowTitle("Graffiti: The ultimate whiteboard for LAN");
    //window.resize(900, 560);
    return app.exec();
}
