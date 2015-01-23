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

#include "client.h"
#include "connection.h"
#include "peermanager.h"

PepperClient::PepperClient()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(server.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, SIGNAL(newConnection(GingerConnection *)),
                     this, SLOT(newConnection(GingerConnection *)));
    QObject::connect(&server, SIGNAL(newConnection(GingerConnection *)),
                     this, SLOT(newConnection(GingerConnection *)));
}

void PepperClient::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    QList<GingerConnection *> connections = peers.values();
    foreach (GingerConnection *connection, connections)
        connection->sendMessage(message);
}

void PepperClient::sendGraffiti(const QString &graffiti)
{
    if (graffiti.isEmpty())
        return;

    QList<GingerConnection *> connections = peers.values();
    foreach (GingerConnection *connection, connections)
        connection->sendGraffiti(graffiti);
}

QString PepperClient::nickName() const
{
    return QString(peerManager->userName()) + "@" + QHostInfo::localHostName()
           + ":" + QString::number(server.serverPort());
}

bool PepperClient::hasConnection(const QHostAddress &senderIp, int senderPort) const
{
    if (senderPort == -1)
        return peers.contains(senderIp);

    if (!peers.contains(senderIp))
        return false;

    QList<GingerConnection *> connections = peers.values(senderIp);
    foreach (GingerConnection *connection, connections) {
        if (connection->peerPort() == senderPort)
            return true;
    }

    return false;
}

void PepperClient::newConnection(GingerConnection *connection)
{
    connection->setGreetingMessage(peerManager->userName());

    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(connection, SIGNAL(readyForUse()), this, SLOT(readyForUse()));
}

void PepperClient::readyForUse()
{
    GingerConnection *connection = qobject_cast<GingerConnection *>(sender());
    if (!connection || hasConnection(connection->peerAddress(),
                                     connection->peerPort()))
        return;

    connect(connection, SIGNAL(newMessage(const QString &, const QString &)),
            this, SIGNAL(newMessage(const QString &, const QString &)));

    connect(connection, SIGNAL(newGraffiti(const QString &, const QString &)),
            this, SIGNAL(newGraffiti(const QString &, const QString &)));

    peers.insert(connection->peerAddress(), connection);
    QString nick = connection->name();
    if (!nick.isEmpty())
        emit newParticipant(nick);
}

void PepperClient::disconnected()
{
    if (GingerConnection *connection = qobject_cast<GingerConnection *>(sender()))
        removeConnection(connection);
}

void PepperClient::connectionError(QAbstractSocket::SocketError /* socketError */)
{
    if (GingerConnection *connection = qobject_cast<GingerConnection *>(sender()))
        removeConnection(connection);
}

void PepperClient::removeConnection(GingerConnection *connection)
{
    if (peers.contains(connection->peerAddress())) {
        peers.remove(connection->peerAddress());
        QString nick = connection->name();
        if (!nick.isEmpty())
            emit participantLeft(nick);
    }
    connection->deleteLater();
}
