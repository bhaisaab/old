/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#include <QtNetwork>

#include "server.h"
#include "connection.h"
#include "gingerthread.h"
#undef USE_THREAD
//#define USE_THREAD
GingerServer::GingerServer(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void GingerServer::incomingConnection(int socketDescriptor)
{
    #ifdef USE_THREAD
    GingerThread *thread = new GingerThread(socketDescriptor, this);

    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );
    thread->start();

    QObject::connect(thread, SIGNAL(newConnection(Connection *)),
                     this, SLOT(emitConnection(Connection *)));

    #else
    GingerConnection *connection = new GingerConnection(this);
    if(!(connection->setSocketDescriptor(socketDescriptor)))
    {
        qDebug( "Socket error!" );
        return;
    }

    emit newConnection(connection);
    #endif
}

void GingerServer::emitConnection(GingerConnection *connection)
{
    emit newConnection(connection);
}
