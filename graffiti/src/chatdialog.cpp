///////////////////////////////////////////////////////////////////////////
// chatdialog.cpp
// IceCuBe Messenger
//
// © Rohit Yadav, Abhishek Kumar, 2008-2009.
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////
#include <QtGui>

#include "chatdialog.h"
#include "peermanager.h"

ChatDialog::ChatDialog(QWidget *parent) : OliveInterface(parent)
{
    msgInput->setFocusPolicy(Qt::StrongFocus);
    msgDisplay->setFocusPolicy(Qt::NoFocus);
    msgDisplay->setReadOnly(true);

    QColor color = msgDisplay->textColor();
    msgDisplay->setTextColor(Qt::gray);
    msgDisplay->append("");
    msgDisplay->setTextColor(color);

    logTextBox->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    refreshButton->setFocusPolicy(Qt::NoFocus);

    connect(msgInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    connect(&client, SIGNAL(newMessage(const QString &, const QString &)),
            this, SLOT(appendMessage(const QString &, const QString &)));

    connect(&client, SIGNAL(newGraffiti(const QString &, const QString &)),
            this, SLOT(updateGraffiti(const QString &, const QString &)));

    connect(&client, SIGNAL(newParticipant(const QString &)),
            this, SLOT(newParticipant(const QString &)));

    connect(&client, SIGNAL(participantLeft(const QString &)),
            this, SLOT(participantLeft(const QString &)));

    connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshUserCloud()));

    connect(graffiti, SIGNAL(sendGraffiti(const QString)), this, SLOT(sendGraffiti(const QString &)) );

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);
}

void ChatDialog::updateGraffiti(const QString &from, const QString &message)
{
    graffiti->updateGraffiti(from, message);//updateGraffiti
}

void ChatDialog::sendGraffiti(const QString &xml)
{
    client.sendGraffiti(xml);
}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QList<QString> list = from.split('@');
    QString msgSender = list.at(0) ;
    qDebug() << msgSender << "Nick:" << myNickName;

    QTextCursor cursor(msgDisplay->textCursor());
    cursor.movePosition(QTextCursor::End);

    QColor color = msgDisplay->textColor();

    if(from.compare(myNickName))
        msgDisplay->setTextColor(Qt::red);
    else
        msgDisplay->setTextColor(Qt::blue);

    msgDisplay->insertPlainText("<" + msgSender + "> ");
    msgDisplay->setTextColor(color);
    msgDisplay->insertPlainText(message);
    msgDisplay->append("\n");

    QScrollBar *bar = msgDisplay->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatDialog::returnPressed()
{
    QString text = msgInput->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        if(text == "/about")
            showInformation();
        else
        {
            QColor color = msgDisplay->textColor();
            msgDisplay->setTextColor(Qt::red);
            msgDisplay->append(tr("! Unknown command: %1")
                             .arg(text.left(text.indexOf(' '))));
            msgDisplay->setTextColor(color);
        }
    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    msgInput->clear();
}

void ChatDialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = logTextBox->textColor();
    logTextBox->append(tr("* %1 has joined IceCuBe").arg(nick));
    logTextBox->setTextColor(Qt::gray);
    logTextBox->append(tr("* %1 has joined IceCuBe").arg(nick));
    logTextBox->append("");
    logTextBox->setTextColor(color);

    listWidget->addItem(nick);
}

void ChatDialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = listWidget->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);

    QColor color = logTextBox->textColor();
    logTextBox->setTextColor(Qt::gray);
    logTextBox->append(tr("* %1 has left Graffiti").arg(nick));
    logTextBox->append("");
    logTextBox->setTextColor(color);
}

void ChatDialog::refreshUserCloud()
{
    this->client.peerManager->sendBroadcastDatagram();
}

void ChatDialog::showInformation()
{
    QMessageBox::information(this, tr("Graffiti"),
                             tr("Graffiti, the Interactive LAN Whiteboard (graffiti.sourceforge.net)\nCreated by Rohit Yadav (rohityadav.in) and Abhishek Kumar (theshowstopper.in).\n(c) 2008-11, All Rights Reserved."));
}
