/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef GINGERTHREAD_H
#define GINGERTHREAD_H

#include <QThread>

class GingerConnection;

class GingerThread : public QThread
{
    Q_OBJECT

public:
    GingerThread(int descriptor, QObject *parent);
    void run();
private:
    int socketDescriptor;

signals:
    void newConnection(GingerConnection *connection);
};

#endif // GINGERTHREAD_H
