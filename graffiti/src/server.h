/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef GINGERSERVER_H
#define GINGERSERVER_H

#include <QtNetwork>

class GingerConnection;

class GingerServer : public QTcpServer
{
    Q_OBJECT

public:
    GingerServer(QObject *parent = 0);

signals:
    void newConnection(GingerConnection *connection);

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void emitConnection(GingerConnection* connection);
};

#endif // GINGERSERVER_H
