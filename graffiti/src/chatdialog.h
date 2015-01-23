///////////////////////////////////////////////////////////////////////////
// chatdialog.cpp
// IceCuBe Messenger
//
// © Rohit Yadav, Abhishek Kumar, 2008-2009.
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////
#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "client.h"
#include "oliveinterface.h"

class ChatDialog : public OliveInterface
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void appendMessage(const QString &from, const QString &message);
    void updateGraffiti(const QString &from, const QString &message);
    void sendGraffiti(const QString &xml);

private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void showInformation();
    void refreshUserCloud();

private:
    PepperClient client;
    QString myNickName;
    QTextTableFormat tableFormat;
};

#endif
