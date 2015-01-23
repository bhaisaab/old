
#include <QtGui>
#include <QtDebug>
#include "graffitiarea.h"

void GraffitiArea::backupGraffitiVars()
{
    tempCol = this->myPenColor;
    tempWidth = this->myPenWidth;
    tempLastPoint = this->lastPoint;
}

void GraffitiArea::restoreGraffitiVars()
{
    myPenColor = tempCol;
    myPenWidth = tempWidth;
    lastPoint  = tempLastPoint;
}

void GraffitiArea::showPeerLabel(const QString &from, QPoint pos)
{
    if(label != NULL)
        label->setVisible(false);

    QList<QString> list = from.split('@');
    QString graffitiSender = list.at(0) ;

    label = new QLabel(graffitiSender, this);
    label->setPalette(QColor(0,0,0));
    label->setVisible(false);
    label->setBackgroundRole(QPalette::Dark);
    label->setAutoFillBackground(false);
    int w = label->width();
    int h = label->height();
    label->setGeometry(pos.x(), pos.y(), w, h);

    label->setVisible(true);
    labelTimer.setInterval(400);
    labelTimer.setSingleShot(true);
    labelTimer.start();
    QObject::connect(&labelTimer, SIGNAL(timeout()), this, SLOT(hideLabel()));
}

void GraffitiArea::updateScribble(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
   /* qDebug() <<"Received col = "<< col
            << "width = " << width
            << "lastpoint = " << lastPos
            << "pos = " << pos << "from: ";*/

    //emit showPeerLabel(from, pos);
    showPeerLabel(from, pos);

    backupGraffitiVars();

    myPenColor = col;
    myPenWidth = width;
    lastPoint  = lastPos;

    drawLineTo(pos);

    restoreGraffitiVars();
}

void GraffitiArea::updateEraser(const QString &from, QPoint pos, QPoint lastPos, int width)
{
   /* qDebug() << "width = " << width
            << "lastpoint = " << lastPos
            << "pos = " << pos << "from: ";*/

    //emit showPeerLabel(from, pos);

    showPeerLabel(from, pos);

    backupGraffitiVars();

    int tempEraserWidth = myEraserWidth;
    this->myEraserWidth = width;
    lastPoint  = lastPos;

    eraseTo(pos);

    this->restoreGraffitiVars();
    myEraserWidth = tempEraserWidth;
}

void GraffitiArea::updateText(const QString &from, QPoint pos, QString &text)
{
    showPeerLabel(from, pos);

    this->drawText(pos, text);
    //qDebug() << "Received graffiti text msg: " << text;
}

void GraffitiArea::updateLine(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    showPeerLabel(from, pos);

    backupGraffitiVars();

    myPenColor = col;
    myPenWidth = width;
    lastPoint  = lastPos;

    drawLineTo(pos);

    restoreGraffitiVars();
}

void GraffitiArea::updateRectangle(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    showPeerLabel(from, pos);

    backupGraffitiVars();

    myPenColor = col;
    myPenWidth = width;
    lastPoint  = lastPos;

    drawRectangle(pos);

    restoreGraffitiVars();
}

void GraffitiArea::updateEllipse(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    qDebug() << "width = " << width
            << "lastpoint = " << lastPos
            << "pos = " << pos << "\n";

    showPeerLabel(from, pos);
    backupGraffitiVars();

    myPenColor = col;
    myPenWidth = width;
    lastPoint  = lastPos;



    this->drawEllipse(pos);

    restoreGraffitiVars();
}

void GraffitiArea::hideLabel()
{
    label->setVisible(false);
    //labelTimer.disconnect(&labelTimer, SIGNAL(timeout()), this, SLOT(hideLabel()) );
    labelTimer.stop();
    //qDebug() << "timer reached!\n";
}

//-- Graffiti Area --
GraffitiArea::GraffitiArea(QWidget *parent):
    QWidget(parent),
    image(800, 640, QImage::Format_RGB32),
    lastPoint(-1, -1)
{
    label = NULL;
    setAttribute(Qt::WA_StaticContents);
    //setAttribute(Qt::WA_NoBackground);
    pencil = false;
    eraser = false;
    line = false;
    rectangle = false;
    ellipse = false;
    fill = false;
    modified = false;
    scribbling = false;
    //lining = false;
    erasing = false;
    myPenWidth = 1;
    //myDrawWidth = 1;
   // myLineWidth = 1;
    myPenColor = Qt::black;
    myFillColor = Qt::black;
    myEraserWidth = 20;
    //fillPoints.num = 0;
    //adjustSize();
    //image.
    image.fill(qRgb(255, 255, 255));
    setMinimumSize(400, 300);
    resize(800,600);
    
}
//! [0]

//! [1]
bool GraffitiArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    setImage(loadedImage);
    return true;
}
//! [2]

//! [3]
bool GraffitiArea::saveImage(const QString &fileName, const char *fileFormat)
//! [3] //! [4]
{
    QImage visibleImage = image;
    //resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}
//! [4]
void GraffitiArea::setImage(const QImage &loadedImage)
{
    image = loadedImage.convertToFormat(QImage::Format_RGB32);
    resize(loadedImage.size());
    update();
    updateGeometry();
}
//! [5]
void GraffitiArea::setPenColor(const QColor &newColor)
//! [5] //! [6]
{
    myPenColor = newColor;
    setFillColor(newColor);
}
//! [6]

//! [7]
void GraffitiArea::setPenWidth(int newWidth)
//! [7] //! [8]
{
    myPenWidth = newWidth;
}
//! [8]

void GraffitiArea::setEraserWidth(int newWidth)
//! [7] //! [8]
{
    myEraserWidth = newWidth;
}
//! [8]

void GraffitiArea::setFillColor(const QColor &newColor)
//! [7] //! [8]
{
    myFillColor = newColor;
}
//! [8]

//! [9]
void GraffitiArea::clearImage()
//! [9] //! [10]
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}


//-- MousePress Event --
void GraffitiArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && pencil) {
        lastPoint = event->pos();
        qDebug() <<"Scribble:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y()<<"PencilWidth: "<<myPenWidth<<"PencilColour: "<<myPenColor;
        //printf("%d, %d", lastPoint.x(), lastPoint.y());
        scribbling = true;
    }
    else if(event->button() == Qt::LeftButton && line){
        lastPoint = event->pos();
        startingPoint = lastPoint;
        drawPoint();
        //qDebug() <<"Line:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y();
        //lining = true;
    }
    else if(event->button() == Qt::LeftButton && eraser){
        lastPoint = event->pos();
        qDebug() <<"Eraser:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y()<<"EraserWidth: "<<myEraserWidth;
        erasing = true;
    }
    else if(event->button() == Qt::LeftButton && rectangle){
        lastPoint = event->pos();
        startingPoint = lastPoint;
        drawPoint();
    }
    else if(event->button() == Qt::LeftButton && ellipse){
        lastPoint = event->pos();
        //drawPoint();
    }
    else if(event->button() == Qt::LeftButton && text){
        drawText(event->pos(), paintText);
        emit sendTextUpdate(event->pos(), paintText);
        update();
        }
    else if(event->button() == Qt::LeftButton && fill){
        lastPoint = event->pos();
        //drawPoint();
    }
    else if(event->button() == Qt::LeftButton && insertImage){
            lastPoint = event->pos();
    }
    else if(event->button() == Qt::LeftButton && colorSelection){
        QPoint curPoint = event->pos();
        myPenColor = selectedColor(curPoint);
        emit colorSelected();
    }
}

void GraffitiArea::drawText(QPoint pos, QString &text)
{
    QPainter painter(&image);
    //setupPainter(painter);
    //const QRectF boundingRect = pendingPath.boundingRect();
    painter.drawText(pos, text);
    qDebug() << "drawText: " << text;
}


//-- MouseMove Event --
void GraffitiArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        emit sendPencilUpdate(event->pos(), lastPoint, myPenWidth, myPenColor);
        drawLineTo(event->pos());
        QPoint lastPoint1 = event->pos();
        qDebug() <<"Scribble:: "<<"x: "<<lastPoint1.x()<<"y: "<<lastPoint1.y()<<"PencilWidth: "<<myPenWidth<<"PencilColour: "<<myPenColor;
    }
    else if ((event->buttons() & Qt::LeftButton) && erasing){
        emit sendEraserUpdate(event->pos(),lastPoint, myEraserWidth);
        eraseTo(event->pos());
        QPoint lastPoint1 = event->pos();
        qDebug() <<"Eraser:: "<<"x: "<<lastPoint1.x()<<"y: "<<lastPoint1.y()<<"EraserWidth: "<<myEraserWidth;
    }
    //emit updatePreview();
}



//-- MouseRelease Event --
void GraffitiArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        emit sendPencilUpdate(event->pos(), lastPoint, myPenWidth, myPenColor);
        drawLineTo(event->pos());
        scribbling = false;
    }
    else if(event->button() == Qt::LeftButton && line){
        emit sendLineUpdate(event->pos(), lastPoint, myPenWidth, myPenColor);
        drawLineTo(event->pos());
        endingPoint = event->pos();
        qDebug() <<"Line:: "<<"x1: "<<startingPoint.x()<<"y1: "<<startingPoint.y()<<"x2: "<<endingPoint.x()<<"y2: "<<endingPoint.y();
        //lining = false;
    }
    else if(event->button() == Qt::LeftButton && erasing){
        emit sendEraserUpdate(event->pos(),lastPoint, myEraserWidth);
        eraseTo(event->pos());
        erasing = false;
    }
    else if(event->button() == Qt::LeftButton && rectangle){
        emit sendRectangleUpdate(event->pos(), lastPoint, myPenWidth, myPenColor);
        drawRectangle(event->pos());
        endingPoint = event->pos();
        qDebug() <<"Rectangle:: "<<"x: "<<startingPoint.x()<<"y: "<<startingPoint.y()<<"Width: "<<endingPoint.x() - startingPoint.x()<<"Height: "<<endingPoint.y() - startingPoint.y();
    }
    else if(event->button() == Qt::LeftButton && ellipse){
        emit sendEllipseUpdate(event->pos(), lastPoint, myPenWidth, myPenColor);
        drawEllipse(event->pos());
    }
    
    else if(event->button() == Qt::LeftButton && fill){
        seedFill(lastPoint.x(), lastPoint.y(), image.pixel(lastPoint.x(), lastPoint.y()), myFillColor);//, true, true, true, true);
        update();
    }
    else if(event->button() == Qt::LeftButton && insertImage){
        drawInsertedImage(lastPoint, event->pos());
        update();
        insertImage = false;
        setCursor(Qt::ArrowCursor);
    }
    emit updatePreview();
}


//-- Paint Event --
void GraffitiArea::paintEvent(QPaintEvent * /* event */)

{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}


//-- PencilPress Event --
void GraffitiArea::pencilPressEvent()
{

    deSelectAll();
    pencil = true;

    QCursor cursor(QPixmap(":/tools/images/tools/pencil.png"),5,26);
    setCursor(cursor);
}



//-- LinePress Event --
void GraffitiArea::linePressEvent()
{
    deSelectAll();
    line = true;
    this->setCursor(QCursor(Qt::CrossCursor));
}




//-- EraserPress Event --
void GraffitiArea::eraserPressEvent()
{
    deSelectAll();
    eraser = true;
    QCursor cursor(QPixmap(":/tools/images/tools/eraser.png"),12,24);
    setCursor(cursor);
}



//-- RectanglePress Event --
void GraffitiArea::rectanglePressEvent()
{
    deSelectAll();
    rectangle = true;
    //QMessageBox::about(parent, tr("About Graffiti"));
    this->setCursor(QCursor(Qt::CrossCursor));
}




//-- EllipsePress Event --
void GraffitiArea::ellipsePressEvent()
{
    deSelectAll();
    ellipse = true;
    //QMessageBox::about(parent, tr("About Graffiti"));
    this->setCursor(QCursor(Qt::CrossCursor));
}



//-- FillPress Event --
void GraffitiArea::fillPressEvent()
{
    deSelectAll();
    fill = true;
    QCursor cursor(QPixmap(":/tools/images/tools/fill.png"),5,26);
    setCursor(cursor);
}



//-- TextPress Event --
void GraffitiArea::textPressEvent()
{
    deSelectAll();
    text = true;
    paintText = QInputDialog::getText(this, tr("Graffiti"), tr("Give Text"));
    //QMessageBox::about(parent, tr("About Graffiti"));
      // QCursor cursor(QPixmap(":/tools/images/tools/fill.png"),5,26);
    setCursor(Qt::CrossCursor);
}

//-- Color Selection Press Event --
void GraffitiArea::colorSelPressEvent()
{
    deSelectAll();
    colorSelection = true;
    setCursor(Qt::CrossCursor);

}

//-- ImagePress Event --
void GraffitiArea::imagePressEvent()
{

    deSelectAll();
    insertImage = true;
    QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty()){
            if (!insertedImage.load(fileName))
            qDebug() <<"No Image";
        }
    setCursor(Qt::CrossCursor);
}

//-- Draw Image --
void GraffitiArea::drawInsertedImage(QPoint start, QPoint end)
{
    int width = end.x() - start.x();
    int height = end.y() - start.y();

    if (width < 0)
    {
        start.setX(end.x());
        width = 0 - width;
    }
    QPainter painter(&image);
    insertedImage = insertedImage.scaled(width, height, Qt:: IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(start, insertedImage);
    update();
}

//-- DrawLineTo Function:: To draw Line from one point to other --
void GraffitiArea::drawLineTo(const QPoint &endPoint)
{   
    /*if (pencil == true)
    myDrawWidth = myPenWidth;
    else if (line == true)
    myDrawWidth = myLineWidth;*/
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}



//-- EraseTo Function:: To erase --
void GraffitiArea::eraseTo(const QPoint &endPoint)
{   
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white, myEraserWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myEraserWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}



//-- DrawLineTo Function:: To draw Line from one point to other --
void GraffitiArea::drawPoint()
//! [17] //! [18]
{
    /*if (pencil == true)
    myDrawWidth = myPenWidth;
    else if (line == true || rectangle == true || ellipse == true)
    myDrawWidth = myLineWidth;*/
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(lastPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, lastPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    //lastPoint = currentPoint;
}

void GraffitiArea::drawRectangle(const QPoint &endPoint)
//! [17] //! [18]
{
    //if (pencil == true)
    //myDrawWidth = myPenWidth;
    //else if (line == true)
    int width = endPoint.x() - lastPoint.x();
    int height = endPoint.y() - lastPoint.y();
    //myDrawWidth = myLineWidth;
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawRect(lastPoint.x(), lastPoint.y(), width, height);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void GraffitiArea::drawEllipse(const QPoint &endPoint)
{
    //if (pencil == true)
    //myDrawWidth = myPenWidth;
    //else if (line == true)
    int width = endPoint.x() - lastPoint.x();
    int height = endPoint.y() - lastPoint.y();
    if(width < 0)
        width = width * (-1);
    if(height < 0)
        height = height * (-1);
    //myDrawWidth = myLineWidth;
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawEllipse(lastPoint.x(), lastPoint.y(), width, height);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void GraffitiArea::seedFill(int x, int y, QRgb targetColor, QColor replacementColor )
{
    int m, n;
    QPoint temp = QPoint(x,y);
    QStack<QPoint> drawArea;
    QRgb color = replacementColor.rgb();
    drawArea.push(temp);

    while(drawArea.size() > 0)
    {
        temp = drawArea.pop();
        image.setPixel(temp, color);

        m = temp.x();
        n = temp.y();

        if(m > 0 && image.pixel(m-1,n) == targetColor)
            drawArea.push(QPoint(m-1,n));

        if(m < image.width()-1 && image.pixel(m+1,n) == targetColor)
            drawArea.push(QPoint(m+1,n));

        if(n > 0 && image.pixel(m,n-1) == targetColor)
            drawArea.push(QPoint(m,n-1));

        if(n < image.height()-1 && image.pixel(m,n+1) == targetColor)
            drawArea.push(QPoint(m,n+1));
    }
}

void GraffitiArea::deSelectAll()
{
    pencil = false;
    eraser = false;
    line = false;
    rectangle = false;
    ellipse = false;
    fill = false;
    colorSelection = false;
    text = false;
    modified = false;
    scribbling = false;
    erasing = false;
    insertImage = false;
}

QColor GraffitiArea::selectedColor(const QPoint &selectedPoint)
{
    qDebug() <<"Color:: "<<image.pixel(selectedPoint);
    QColor newColor = image.pixel(selectedPoint);
    if(newColor.isValid())
    return newColor;
    else
    return myPenColor;
}

void GraffitiArea::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
 
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
//! [21] //! [22]
    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}
