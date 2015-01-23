/***************************************************************************
**
** GraffitiXmlManager provides XML Stream Reader and Writer Class.
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#include "graffitireader.h"
#include <QDebug>

GraffitiReader::GraffitiReader(const QString &string)
    : QXmlStreamReader(string)
    //,  QObject(0)
{
    //text = new QString("");
}

bool GraffitiReader::read()
{
    while (!atEnd()) {
        readNext();

        if (isStartElement()) {
            if (name() == "graffiti" && attributes().value("version") == "1.0")
                readGraffiti();
            else
                raiseError(QObject::tr("The XMLStream is not a IceCuBe::Graffiti version 1.0 file."));
        }
    }

    return !error();

}

void GraffitiReader::readUnknownElement()
{
    Q_ASSERT(isStartElement());

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
            readUnknownElement();
    }
}

void GraffitiReader::readGraffiti()
{
    Q_ASSERT(isStartElement() && name() == "graffiti");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "pencil")
                readPencil();
            else if (name() == "line")
                readLine();
            else if (name() == "rectangle")
                readRectangle();
            else if(name() == "ellipse")
                readEllipse();
            else if (name() == "eraser")
                readEraser();
            else if (name() == "text")
                readText();
            else if (name() == "image")
                readImage();
            else if (name() == "fill")
                readFill();
            else
                readUnknownElement();
        }
    }
}

void GraffitiReader::readColor()
{
    Q_ASSERT(isStartElement() && name() == "color");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if(name() == "r")
                r = readElementText();
            else if(name() == "g")
                g = readElementText();
            else if(name() == "b")
                b = readElementText();
        }
    }

    qDebug() << "RGB:: " << r <<" "<< g << " " << b <<"\n";
    col.setRed(r.toUInt());
    col.setGreen(g.toUInt());
    col.setBlue(b.toUInt());
}

void GraffitiReader::readPencil()
{
    Q_ASSERT(isStartElement() && name() == "pencil");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if(name() == "lastx")
              lastPos.setX(readElementText().toInt());
            else if (name() == "lasty")
              lastPos.setY(readElementText().toInt());
            else if (name() == "width")
              width = readElementText().toInt();
            else if (name() == "color")
              readColor();
            else
                readUnknownElement();
        }
    }
    //ROHIT do the D-BUG
    //emit updateScribble(pos, width, col);
    //emit updateScribble(pos, width, col);
    this->toolSentByPeer = "pencil";
}

void GraffitiReader::readEraser()
{
    Q_ASSERT(isStartElement() && name() == "eraser");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if(name() == "lastx")
              lastPos.setX(readElementText().toInt());
            else if (name() == "lasty")
              lastPos.setY(readElementText().toInt());
            else if (name() == "width")
              width = readElementText().toInt();
            else
                readUnknownElement();
        }
    }

    this->toolSentByPeer = "eraser";
}

void GraffitiReader::readText()
{
    Q_ASSERT(isStartElement() && name() == "text");

    this->text = "";

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if (name() == "msg")
              text = readElementText();
            else
                readUnknownElement();
        }
    }

    this->toolSentByPeer = "text";
}

void GraffitiReader::readLine()
{
        Q_ASSERT(isStartElement() && name() == "line");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if(name() == "lastx")
              lastPos.setX(readElementText().toInt());
            else if (name() == "lasty")
              lastPos.setY(readElementText().toInt());
            else if (name() == "width")
              width = readElementText().toInt();
            else if (name() == "color")
              readColor();
            else
                readUnknownElement();
        }
    }

    this->toolSentByPeer = "line";
}

void GraffitiReader::readRectangle()
{
    Q_ASSERT(isStartElement() && name() == "rectangle");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if(name() == "lastx")
              lastPos.setX(readElementText().toInt());
            else if (name() == "lasty")
              lastPos.setY(readElementText().toInt());
            else if (name() == "width")
              width = readElementText().toInt();
            else if (name() == "color")
              readColor();
            else
                readUnknownElement();
        }
    }

    this->toolSentByPeer = "rectangle";
}

void GraffitiReader::readEllipse()
{
    Q_ASSERT(isStartElement() && name() == "ellipse");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "x")
              pos.setX(readElementText().toInt());
            else if (name() == "y")
              pos.setY(readElementText().toInt());
            else if(name() == "lastx")
              lastPos.setX(readElementText().toInt());
            else if (name() == "lasty")
              lastPos.setY(readElementText().toInt());
            else if (name() == "width")
              width = readElementText().toInt();
            else if (name() == "color")
              readColor();
            else
                readUnknownElement();
        }
    }

    this->toolSentByPeer = "ellipse";
}

void GraffitiReader::readFill()
{
}

void GraffitiReader::readImage()
{

}
