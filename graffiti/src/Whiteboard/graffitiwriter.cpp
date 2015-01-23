/***************************************************************************
**
** GraffitiXmlManager provides XML Stream Reader and Writer Class.
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#include "graffitiwriter.h"

GraffitiWriter::GraffitiWriter(QString &string) : QXmlStreamWriter(&string)
{
    setAutoFormatting(true);
}

bool GraffitiWriter::write()
{
    //setDevice(device);
    writeStartDocument();
    writeStartElement("graffiti");
    writeAttribute("version", "1.0");

    return true;
}

void GraffitiWriter::end()
{
    writeEndDocument();
}


void GraffitiWriter::writePosition(QPoint pos)
{
    QString temp;
    writeTextElement("x", temp.setNum(pos.x()) );
    writeTextElement("y", temp.setNum(pos.y()) );
}

void GraffitiWriter::writeLastPosition(QPoint lastPos)
{
    QString temp;
    writeTextElement("lastx", temp.setNum(lastPos.x()) );
    writeTextElement("lasty", temp.setNum(lastPos.y()) );
}

void GraffitiWriter::writeColor(QColor col)
{
    writeStartElement("color");

    QString temp;
    writeTextElement("r", temp.setNum(col.red()) );
    writeTextElement("g", temp.setNum(col.green()) );
    writeTextElement("b", temp.setNum(col.blue()) );

    writeEndElement();
}

void GraffitiWriter::writePencil(QPoint pos, QPoint lastPos, int width, QColor col)
{
    writeStartElement("pencil");

    writePosition(pos);
    writeLastPosition(lastPos);
    QString temp;
    writeTextElement("width", temp.setNum(width));
    writeColor(col);

    writeEndElement();
}

void GraffitiWriter::writeEraser(QPoint pos, QPoint lastPos, int width)
{
    writeStartElement("eraser");

    writePosition(pos);
    writeLastPosition(lastPos);
    QString temp;
    writeTextElement("width", temp.setNum(width));

    writeEndElement();
}

void GraffitiWriter::writeText(QPoint pos, const QString text)
{
    writeStartElement("text");

    writePosition(pos);
    writeTextElement("msg", text);

    writeEndElement();
}

void GraffitiWriter::writeLine(QPoint pos, QPoint lastPos, int width, QColor col)
{
    writeStartElement("line");

    writePosition(pos);
    writeLastPosition(lastPos);
    QString temp;
    writeTextElement("width", temp.setNum(width));
    writeColor(col);

    writeEndElement();
}

void GraffitiWriter::writeRectangle(QPoint pos, QPoint lastPos, int width, QColor col)
{
    writeStartElement("rectangle");

    writePosition(pos);
    writeLastPosition(lastPos);
    QString temp;
    writeTextElement("width", temp.setNum(width));
    writeColor(col);

    writeEndElement();
}

void GraffitiWriter::writeEllipse(QPoint pos, QPoint lastPos, int width, QColor col)
{
    writeStartElement("ellipse");

    writePosition(pos);
    writeLastPosition(lastPos);
    QString temp;
    writeTextElement("width", temp.setNum(width));
    writeColor(col);

    writeEndElement();
}
