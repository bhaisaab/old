/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef GRAFFITIAREA_H
#define GRAFFITIAREA_H
#include <QtDebug>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QLabel>
#include <QTimer>


//! [0]
class GraffitiArea : public QWidget
{
    Q_OBJECT

public:
    GraffitiArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setEraserWidth(int newWidth);
    void setFillColor(const QColor &newColor);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    int eraserWidth() const { return myEraserWidth; }
    QColor fillColor() const { return myPenColor; }
    QImage graffitiImage() const { return image; }
    //void mouseRelease(QMouseEvent *event);
     void deSelectAll();
    //-- Graffiti Network Updaters
public:
    void backupGraffitiVars();
    void restoreGraffitiVars();

    QColor tempCol;
    int tempWidth;;
    QPoint tempLastPoint;;

    void showPeerLabel(const QString &from, QPoint pos);

    void updateScribble(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateEraser(const QString &from, QPoint pos, QPoint lastPos, int width);
    void updateText(const QString &from, QPoint pos, QString &text);
    void updateLine(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateRectangle(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateEllipse(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);

signals:
   void updatePreview();
   void colorSelected();
   void sendPencilUpdate(QPoint endingPoint, QPoint lastPoint, int myPenWidth, QColor myPenColor);
   void sendEraserUpdate(QPoint endingPoint, QPoint lastPoint, int myPenWidth);
   void sendTextUpdate(QPoint pos, QString text);
   void sendLineUpdate(QPoint endingPoint, QPoint lastPoint, int myPenWidth, QColor myPenColor);
   void sendRectangleUpdate(QPoint endingPoint, QPoint lastPoint, int myPenWidth, QColor myPenColor);
   void sendEllipseUpdate(QPoint endingPoint, QPoint lastPoint, int myPenWidth, QColor myPenColor);

public slots:
    void clearImage();
    void print();
    void pencilPressEvent();
    void linePressEvent();
    void eraserPressEvent();
    void rectanglePressEvent();
    void ellipsePressEvent();
    void fillPressEvent();
    void textPressEvent();
    void colorSelPressEvent();
    void hideLabel();
    void imagePressEvent();
protected:
    //void pencilPressEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    //void resizeEvent(QResizeEvent *event);
    void setImage(const QImage &loadedImage);

private:
    struct queue{
            int front;
           QPoint pointQueue[1000000];
            int rear;
       }fillPoints;

    void addToQueue(int X, int Y);
    void deQueue();
    void eraseTo(const QPoint &endPoint);
    void drawText(QPoint pos, QString &text);
    void drawLineTo(const QPoint &endPoint);
    void drawPoint();
    void drawRectangle(const QPoint &endPoint);
    void drawEllipse(const QPoint &endPoint);
    void seedFill(int x, int y, QRgb targetColor, QColor replacementColor);
    void drawInsertedImage(QPoint start, QPoint end);
     QColor selectedColor(const QPoint &selectedPoint);
    //void resizeImage(QImage *image, const QSize &newSize);

    bool pencil;
    bool eraser;
    bool line;
    bool rectangle;
    bool ellipse;
    bool fill;
    bool text;
    bool colorSelection;
    bool modified;
    bool scribbling;
    bool lining;
    bool erasing;
    bool filling;
    int myPenWidth;
    bool insertImage;
    //int myLineWidth;
    //int myDrawWidth;
    QImage insertedImage;
    int myEraserWidth;
    QColor myPenColor;
    QColor myFillColor;
    QImage image;
    QPoint lastPoint;
    QPoint startingPoint;
    QPoint endingPoint;
    QString paintText;
public:
    QLabel *label;
    QTimer labelTimer;
};
//! [0]

#endif
