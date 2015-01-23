/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#include <QtGui>
#include <QtDebug>
#include "preview.h"

//! [0]
Preview::Preview(QWidget *parent)
    : QFrame(parent),
image(250, 250, QImage::Format_RGB32)
{
    setAttribute(Qt::WA_StaticContents);
    image.fill(qRgb(255, 255, 255));
    setMinimumSize(250, 250);
    //resize(1, 60);
}


void Preview::updatePreview(QImage newImage)
{
    int newWidth , newHeight;
    if(newImage.width() > newImage.height()){
        newWidth = 250;
        newHeight = newImage.height()*(newImage.width()/newWidth);
     }
     else{
         newHeight = 250;
         newWidth = newImage.width()*(newImage.height()/newHeight);
     }



    QImage updateImage = newImage.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image = updateImage.convertToFormat(QImage::Format_RGB32);
    update();
}

void Preview::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    update();
}


void Preview::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}
