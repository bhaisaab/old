/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef PEPPERCLIENT_H
#define PEPPERCLIENT_H

#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>

#include "server.h"
//#include "graffitireader.h"

class PeerManager;

class PepperClient : public QObject
{
    Q_OBJECT

public:
    PepperClient();

    PeerManager *peerManager;


    void sendMessage(const QString &message);
    void sendGraffiti(const QString &graffiti);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newGraffiti(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private slots:
    void newConnection(GingerConnection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyForUse();

private:
    void removeConnection(GingerConnection *connection);

    GingerServer server;
    QMultiHash<QHostAddress, GingerConnection *> peers;
};

#endif
