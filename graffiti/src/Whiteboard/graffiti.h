/***************************************************************************
**
** Part of IceCuBe Messenger
**
** Copyright (c) 2008-2009 Rohit Yadav, Abhishek Kumar et al
**
** Released under GNU General Public License
**
***************************************************************************/

#ifndef GRAFFITI_H
#define GRAFFITI_H
#include <QtGui>
#include <QList>
#include <QMainWindow>
#include "preview.h"
#include "graffitireader.h"
#include "graffitiwriter.h"

class GraffitiArea;
//class SideDock;
class QScrollArea;

class Graffiti : public QWidget
{
    Q_OBJECT

public:
    Graffiti(QWidget *parent = 0);
    QHBoxLayout   *quteBoardHBox;
    QVBoxLayout   *toolVBox;
    //bool pen;
    //GraffitiReader *reader;
    //GraffitiWriter *writer;
    QString        sendXML; //for writer
    QString        getXML;  //for reader

    //-- Graffiti NetWork Func --
    void updateGraffiti(const QString &from, const QString &xml);

protected:
    void closeEvent(QCloseEvent *event);
    void updateColorBox(QColor color);
    void updatePenWidth(int newWidth);
    void updateEraserWidth(int newWidth);

public slots:
    void open();
    void save();
private slots:
    void showPeerLabel(const QString &peerName, QPoint pos);
    void changeColor();
    void colorChanged();
    //void rgbSliderChanged(int newValue);
    void redSliderChanged(int newValue);
    void greenSliderChanged(int newValue);
    void blueSliderChanged(int newValue);
    void changeColorBlack();
    void changeColorRed();
    void changeColorGreen();
    void changeColorBlue();
    void changeColorWhite();
    void changeColorGray();
    void changeColorMagenta();
    void changeColorDarkRed();
    void changeColorDarkGreen();
    void changeColorDarkBlue();
    void changeColorYellow();
    void changeColorCyan();
    void penWidth();
    void penSliderChanged(int newWidth);
    void eraserWidth();
    void eraserSliderChanged(int newWidth);
    void fillColor();
    void about();

public slots:
    void updateScribble(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateEraser(const QString &from, QPoint pos, QPoint lastPos, int width);
    void updateText(const QString &from, QPoint pos, QString &text);
    void updateLine(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateRectangle(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);
    void updateEllipse(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col);

//signals:
    void sendPencilUpdate(QPoint pos, QPoint lastPos, int width, QColor col);
    void sendEraserUpdate(QPoint pos, QPoint lastPos, int width);
    void sendTextUpdate(QPoint pos, QString text);
    void sendLineUpdate(QPoint pos, QPoint lastPos, int width, QColor col);
    void sendRectangleUpdate(QPoint pos, QPoint lastPos, int width, QColor col);
    void sendEllipseUpdate(QPoint pos, QPoint lastPos, int width, QColor col);

signals:
    void sendGraffiti(const QString &sendXML);

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    void InitToolGrid();
    
    QFrame *mainFrame;

    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *eraserWidthAct;
    QAction *fillColorAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    
    
    QGroupBox     *toolGBox;
    QVBoxLayout   *verticalLayout;
    GraffitiArea  *graffitiArea;
    QScrollArea   *scrollArea;
    QGridLayout   *toolGrid;
    
    QPushButton   *eraserTool;
    QPushButton   *pencilTool;
    QPushButton   *colorSelectionTool;
    QPushButton   *clearTool;
    QPushButton   *textTool;
    QPushButton   *lineTool;
    QPushButton   *rectangleTool;
    QPushButton   *ellipseTool;
    QPushButton   *fillTool;
    QPushButton   *zoomTool;
    QSpacerItem   *verticalSpacer;


    QDockWidget *utilityDock;

   // QFrame *dockContent;
    QFrame *dockContent;

    QVBoxLayout     *dockLayout;
    QGroupBox       *widthGroupBox;
    QGridLayout    *widthBoxLayout;
    QSpinBox             *spinPenWidth;
    QSpinBox             *spinEraserWidth;
    QGroupBox       *colorGroupBox;
    QHBoxLayout     *colorBoxLayout;
    QGridLayout        * sliderLayout;
    QSlider *sliderRed;
    QSlider *sliderGreen;
    QSlider *sliderBlue;
    QLabel* labelRedValue;
    QLabel* labelGreenValue;
    QLabel* labelBlueValue;

    QHBoxLayout    *swatchLayout;
    QPushButton     *colorSwatch;
    QGridLayout    *smallSwatchLayout;
    /*QPushButton     *blackColorSwatch;
    QPushButton     *redColorSwatch;
    QPushButton     *greenColorSwatch;
    QPushButton     *blueColorSwatch;
    QPushButton     *whiteColorSwatch;
    QPushButton     *grayColorSwatch;*/
    QPushButton *blackColorSwatch;
    QPushButton *grayColorSwatch;
    QPushButton *redColorSwatch;
    QPushButton *darkRedColorSwatch;
    QPushButton *magentaColorSwatch;
    QPushButton *yellowColorSwatch;
    QPushButton *greenColorSwatch;
    QPushButton *darkGreenColorSwatch;
    QPushButton *blueColorSwatch;
    QPushButton *darkBlueColorSwatch;
    QPushButton *cyanColorSwatch;
    QPushButton *whiteColorSwatch;

    QHBoxLayout     *imageBoxLayout;

    QSpacerItem     *spacerUtilityPane;

    int penWidthValue;
    int eraserWidthValue;
    int valueRed;
    int valueGreen;
    int valueBlue;

  public:
        QMenu *saveAsMenu;
        QGroupBox        *imageGroupBox;
};

#endif
