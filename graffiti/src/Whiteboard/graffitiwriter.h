/***************************************************************************
**
** GraffitiXmlManager provides XML Stream Reader and Writer Class.
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef GRAFFITIWRITER_H
#define GRAFFITIWRITER_H

#include <QXmlStreamWriter>
#include <QPoint>
#include <QColor>

class GraffitiWriter : public QXmlStreamWriter
{
public:
    GraffitiWriter(QString &string);

    bool write();
    void end();
    //QString *text;

    void writePosition(QPoint pos);
    void writeLastPosition(QPoint lastPos);
    void writeColor(QColor col);

    //-- Pencil Tool --
    void writePencil(QPoint pos, QPoint lastPos, int width, QColor col);
    //-- Eraser Tool --
    void writeEraser(QPoint pos, QPoint lastPos, int width);
    //-- Text Tool --
    void writeText(QPoint pos, const QString text);
    //-- Line Tool --
    void writeLine(QPoint pos, QPoint lastPos, int width, QColor col);
    //-- Rectangle Tool --
    void writeRectangle(QPoint pos, QPoint lastPos, int width, QColor col);
    //-- Ellipse Tool --
    void writeEllipse(QPoint pos, QPoint lastPos, int width, QColor col);
}; //GraffitiWriter

#endif // GRAFFITIWRITER_H
