/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#include "gingerthread.h"
#include "connection.h"

GingerThread::GingerThread( int descriptor, QObject *parent ): QThread( parent )
{
    socketDescriptor = descriptor;
}

void GingerThread::run()
{
    GingerConnection *connection = new GingerConnection(this);
    if(!(connection->setSocketDescriptor(socketDescriptor)))
    {
        qDebug( "Socket error!" );
        return;
    }

    emit newConnection(connection);
}
