/***************************************************************************
**
** GraffitiXmlManager provides XML Stream Reader and Writer Class.
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

/*<nick>  :: Peer information
  <msg>   :: Msg encapsulation
  <wb>    :: Graffiti::WhiteBoard
  <info>  :: Info:SocketAddr Etc..
*/

#ifndef GRAFFITIREADER_H
#define GRAFFITIREADER_H

#include <QXmlStreamReader>
#include <QtGui>
//#include <QObject>

class GraffitiReader : public QXmlStreamReader //, public QObject
{
    //Q_OBJECT
public:
    GraffitiReader(const QString &string);

    bool read();
    //QString* text;

    //-- Read the Protocol Header --
    //void readHeader();

private:
    void readUnknownElement();
    void readGraffiti();

    //-- Graffiti: WhiteBoard Parsers --
    void readPencil();
    void readRectangle();
    void readEllipse();
    void readLine();
    void readEraser();
    void readText();
    void readImage();
    void readFill();

    void readColor();
    
public:
    //-- Structure Capsules --
    //struct Pencil pencil;
    QString toolSentByPeer;
    QPoint pos;
    QPoint lastPos;
    QColor col;
    QString r, g, b;
    int width;
    int height;
    QString text;

//signals:
    //void updateScribble(QPoint pos, int width, QColor col);

}; //GraffitiReader

#endif // GRAFFITIREADER_H
