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

#include "graffiti.h"
#include "graffitiarea.h"
#include "preview.h"
#include "graffitireader.h"
#include <QtGui>

void Graffiti::sendPencilUpdate(QPoint pos, QPoint lastPos, int width, QColor col)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writePencil(pos, lastPos, width, col);
    writer.end();
    emit sendGraffiti(sendXML);

    //qDebug() << "XML sent: " << sendXML << "\n";
}

void Graffiti::sendEraserUpdate(QPoint pos, QPoint lastPos, int width)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writeEraser(pos, lastPos, width);
    writer.end();
    emit sendGraffiti(sendXML);
    //qDebug() << "Eraser XML sent: " << sendXML << "\n";
}

void Graffiti::sendTextUpdate(QPoint pos, QString text)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writeText(pos, text);
    writer.end();
    emit sendGraffiti(sendXML);
    //qDebug() << "Eraser XML sent: " << sendXML << "\n";
}

void Graffiti::sendLineUpdate(QPoint pos, QPoint lastPos, int width, QColor col)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writeLine(pos, lastPos, width, col);
    writer.end();
    emit sendGraffiti(sendXML);

    //qDebug() << "XML sent: " << sendXML << "\n";
}

void Graffiti::sendRectangleUpdate(QPoint pos, QPoint lastPos, int width, QColor col)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writeRectangle(pos, lastPos, width, col);
    writer.end();
    emit sendGraffiti(sendXML);

    //qDebug() << "XML sent: " << sendXML << "\n";
}

void Graffiti::sendEllipseUpdate(QPoint pos, QPoint lastPos, int width, QColor col)
{
    sendXML = "";

    //-- Graffiti Writer --
    GraffitiWriter writer(sendXML);
    writer.write();
    writer.writeEllipse(pos, lastPos, width, col);
    writer.end();
    emit sendGraffiti(sendXML);

    //qDebug() << "XML sent: " << sendXML << "\n";
}

void Graffiti::updateGraffiti(const QString &from, const QString &xml)
{
    qDebug() << "XML rec: " << xml << "\n";

    GraffitiReader reader(xml);
    reader.read();

    QString tool = (reader.toolSentByPeer);

    if(tool == "pencil")
        updateScribble(from, reader.pos, reader.lastPos, reader.width, reader.col);
    if(tool == "eraser")
        updateEraser(from, reader.pos, reader.lastPos, reader.width);
    if(tool == "text")
        updateText(from, reader.pos, reader.text);
    if(tool == "line")
        updateLine(from, reader.pos, reader.lastPos, reader.width, reader.col);
    if(tool == "rectangle")
        updateRectangle(from, reader.pos, reader.lastPos, reader.width, reader.col);
    if(tool == "ellipse")
        updateEllipse(from, reader.pos, reader.lastPos, reader.width, reader.col);

}

//-- Print Received Pencil Updates --
void Graffiti::updateScribble(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    graffitiArea->updateScribble(from, pos, lastPos, width, col);
}

//-- Print Received Eraser Updates --
void Graffiti::updateEraser(const QString &from, QPoint pos, QPoint lastPos, int width)
{
    graffitiArea->updateEraser(from, pos, lastPos, width);
}

void Graffiti::updateText(const QString&from, QPoint pos, QString &text)
{
    graffitiArea->updateText(from, pos, text);
}

//-- Print Received Line Updates --
void Graffiti::updateLine(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    graffitiArea->updateLine(from, pos, lastPos, width, col);
}

//-- Print Received Rectangle Updates --
void Graffiti::updateRectangle(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    graffitiArea->updateRectangle(from, pos, lastPos, width, col);
}

//-- Print Received Ellipse Updates --
void Graffiti::updateEllipse(const QString &from, QPoint pos, QPoint lastPos, int width, QColor col)
{
    graffitiArea->updateEllipse(from, pos, lastPos, width, col);
}

Graffiti::Graffiti(QWidget *parent) : QWidget(parent)
{   
  valueRed = 0;
  valueGreen = 0;
  valueBlue = 0;

  mainFrame = new QFrame(this);  
  scrollArea = new QScrollArea(this);
  graffitiArea = new GraffitiArea(scrollArea);
  //utilityDock = new QDockWidget(this);

  //-- Getting Initial PenWidth & EraserWidth Of GraffitiArea --
  penWidthValue = graffitiArea->penWidth();
  eraserWidthValue = graffitiArea->eraserWidth();

  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(graffitiArea);


  //setCentralWidget(mainFrame);
  setWindowTitle(tr("Graffiti"));
    //resize(500, 500);
    
  quteBoardHBox = new QHBoxLayout(this);
  quteBoardHBox->setObjectName(QString::fromUtf8("quteBoardHBox"));
  
  quteBoardHBox->setMargin(0);
  
  toolGBox = new QGroupBox(this);
  toolGBox->setObjectName(QString::fromUtf8("toolGBox"));
  toolGBox->setAlignment(Qt::AlignLeft);
  
  InitToolGrid();

  QVBoxLayout *graffitiAreaVBox = new QVBoxLayout(this);
  graffitiAreaVBox->addWidget(scrollArea, 4);
  graffitiAreaVBox->addWidget(this->colorGroupBox, 1);
  //quteBoardHBox->addWidget(scrollArea, 4);
  quteBoardHBox->addLayout(graffitiAreaVBox, 4);
  //quteBoardHBox->addWidget(utilityDock, 1);
  createActions();
  createMenus();
  //mainFrame->setLayout(quteBoardHBox);
    connect(graffitiArea, SIGNAL(sendPencilUpdate(QPoint, QPoint, int, QColor)),
            this, SLOT(sendPencilUpdate(QPoint, QPoint, int, QColor)));

    connect(graffitiArea, SIGNAL(sendEraserUpdate(QPoint, QPoint, int)),
            this, SLOT(sendEraserUpdate(QPoint, QPoint, int)));

    connect(graffitiArea, SIGNAL(sendTextUpdate(QPoint, QString)),
            this, SLOT(sendTextUpdate(QPoint, QString)));

    connect(graffitiArea, SIGNAL(sendLineUpdate(QPoint, QPoint, int, QColor)),
            this, SLOT(sendLineUpdate(QPoint, QPoint, int, QColor)));

    connect(graffitiArea, SIGNAL(sendRectangleUpdate(QPoint, QPoint, int, QColor)),
            this, SLOT(sendRectangleUpdate(QPoint, QPoint, int, QColor)));

    connect(graffitiArea, SIGNAL(sendEllipseUpdate(QPoint, QPoint, int, QColor)),
            this, SLOT(sendEllipseUpdate(QPoint, QPoint, int, QColor)));
}

void Graffiti::showPeerLabel(const QString &peerName, QPoint pos)
{
    qDebug() << peerName << pos;
}

void Graffiti::InitToolGrid()
{
  toolGrid = new QGridLayout(toolGBox);
  toolGrid->setObjectName(QString::fromUtf8("toolGrid"));
  toolGrid->setMargin(0);
  toolGrid->setVerticalSpacing(2);
  toolGrid->setHorizontalSpacing(2);

  QIcon icon;

  //-- Eraser Tool --
  pencilTool = new QPushButton(toolGBox);
  pencilTool->setObjectName(QString::fromUtf8("pencilTool"));
  pencilTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/pencil.png")), QIcon::Normal, QIcon::Off);
  // icon.addPixmap(QPixmap(QString::fromUtf8(":/cursors/images/cursor/pencil-cursor.png")), QIcon::Normal, QIcon::Off);
  pencilTool->setIcon(icon);
  pencilTool->setIconSize(QSize(32, 32));

  //-- Pencil Tool --
  eraserTool = new QPushButton(toolGBox);
  eraserTool->setObjectName(QString::fromUtf8("eraserTool"));
  eraserTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/eraser.png")), QIcon::Normal, QIcon::Off);
  eraserTool->setIcon(icon);
  eraserTool->setIconSize(QSize(32, 32));

  //-- Selection Tool --
  colorSelectionTool = new QPushButton(toolGBox);
  colorSelectionTool->setObjectName(QString::fromUtf8("colorSelectionTool"));
  colorSelectionTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/eyedropper.png")), QIcon::Normal, QIcon::Off);
  colorSelectionTool->setIcon(icon);
  colorSelectionTool->setIconSize(QSize(32, 32));

  //-- Clear All Tool --
  clearTool = new QPushButton(toolGBox);
  clearTool->setObjectName(QString::fromUtf8("clearTool"));
  clearTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/bomb.png")), QIcon::Normal, QIcon::Off);
  clearTool->setIcon(icon);
  clearTool->setIconSize(QSize(32, 32));

  //-- Text Tool --
  textTool = new QPushButton(toolGBox);
  textTool->setObjectName(QString::fromUtf8("textTool"));
  textTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/text.png")), QIcon::Normal, QIcon::Off);
  textTool->setIcon(icon);
  textTool->setIconSize(QSize(32, 32));

  //-- Line Tool --
  lineTool = new QPushButton(toolGBox);
  lineTool->setObjectName(QString::fromUtf8("lineTool"));
  lineTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/line.png")), QIcon::Normal, QIcon::Off);
  lineTool->setIcon(icon);
  lineTool->setIconSize(QSize(32, 32));

  //-- Rectangle Tool --
  rectangleTool = new QPushButton(toolGBox);
  rectangleTool->setObjectName(QString::fromUtf8("rectangleTool"));
  rectangleTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/rectangle.png")), QIcon::Normal, QIcon::Off);
  rectangleTool->setIcon(icon);
  rectangleTool->setIconSize(QSize(32, 32));

  //-- Ellipse Tool --
  ellipseTool = new QPushButton(toolGBox);
  ellipseTool->setObjectName(QString::fromUtf8("ellipseTool"));
  ellipseTool->setMaximumSize(QSize(32, 32));
  icon.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/ellipse.png")), QIcon::Normal, QIcon::Off);
  ellipseTool->setIcon(icon);
  ellipseTool->setIconSize(QSize(32, 32));

  //-- Fill Tool --
  fillTool = new QPushButton(toolGBox);
  fillTool->setObjectName(QString::fromUtf8("fillTool"));
  fillTool->setMaximumSize(QSize(32, 32));
  QIcon icon0;
  icon0.addPixmap(QPixmap(QString::fromUtf8(":/tools/images/tools/fill.png")), QIcon::Normal, QIcon::Off);
  fillTool->setIcon(icon0);
  fillTool->setIconSize(QSize(32, 32));

  //-- Zoom Tool --
  zoomTool = new QPushButton(toolGBox);
  zoomTool->setObjectName(QString::fromUtf8("zoomTool"));
  zoomTool->setMaximumSize(QSize(32, 32));
  QIcon icon1;
  icon1.addPixmap(QPixmap(QString::fromUtf8(":/graffiti/images/graffiti_small.png")), QIcon::Normal, QIcon::Off);
  zoomTool->setIcon(icon1);
  zoomTool->setIconSize(QSize(32, 32));

  toolGrid->addWidget(eraserTool,     0, 0, 1, 1);
  toolGrid->addWidget(pencilTool,     0, 1, 1, 1);
  toolGrid->addWidget(colorSelectionTool,  1, 0, 1, 1);
  toolGrid->addWidget(clearTool,      1, 1, 1, 1);
  toolGrid->addWidget(textTool,       2, 0, 1, 1);
  toolGrid->addWidget(lineTool,       2, 1, 1, 1);
  toolGrid->addWidget(rectangleTool,  3, 0, 1, 1);
  toolGrid->addWidget(ellipseTool,    3, 1, 1, 1);
  toolGrid->addWidget(fillTool,       4, 0, 1, 1);
  toolGrid->addWidget(zoomTool,       4, 1, 1, 1);

  verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Maximum, QSizePolicy::Expanding);
  toolGrid->addItem(verticalSpacer, 5, 0, 1, 1);

  //-- ColorSwatchGrid --

    //-- ColorGroupBox --

        colorGroupBox = new  QGroupBox(this);
        colorGroupBox->setTitle("Colours");
        //colorGroupBox->setMaximumSize(220, 440);

/*#if defined(Q_OS_MAC)
        sliderRed = new QSlider(Qt::Horizontal, colorGroupBox);
        sliderGreen = new QSlider(Qt::Horizontal, colorGroupBox);
        sliderBlue = new QSlider(Qt::Horizontal, colorGroupBox);
#else*/
        sliderRed = new QSlider(Qt::Vertical, colorGroupBox);
        sliderGreen = new QSlider(Qt::Vertical, colorGroupBox);
        sliderBlue = new QSlider(Qt::Vertical, colorGroupBox);
/*#endif*/

        colorSwatch = new QPushButton(colorGroupBox);

        sliderRed->setRange(0,255);
        sliderGreen->setRange(0,255);
        sliderBlue->setRange(0,255);

        QLabel* labelRed = new QLabel(tr("Red"));
        QLabel* labelGreen = new QLabel(tr("Green"));
        QLabel* labelBlue = new QLabel(tr("Blue"));
        labelRedValue = new QLabel(tr("0"));
        labelGreenValue = new QLabel(tr("0"));
        labelBlueValue = new QLabel(tr("0"));


        sliderLayout = new QGridLayout();
        sliderLayout->setSizeConstraint(QLayout::SetMinimumSize);
        sliderLayout->setSpacing(10);
        sliderLayout->addWidget(labelRed, 0, 0);
        sliderLayout->addWidget(sliderRed, 0, 1);
        sliderLayout->addWidget(labelRedValue, 1, 0);

        sliderLayout->addWidget(labelGreen, 0, 2);
        sliderLayout->addWidget(sliderGreen, 0, 3);
        sliderLayout->addWidget(labelGreenValue, 1, 2);

        sliderLayout->addWidget(labelBlue, 0, 4);
        sliderLayout->addWidget(sliderBlue, 0, 5);
        sliderLayout->addWidget(labelBlueValue, 1, 4);
        sliderLayout->setMargin(0);
        //sliderLayout->setSpacing(0);


        colorSwatch->setFixedSize( 32, 32);
        QPixmap colorPixmap(32,32);
        colorPixmap.fill( Qt::black );
        colorSwatch->setFlat(true);
        colorSwatch->setIcon(QIcon(colorPixmap));
        colorSwatch->setIconSize(QSize(32, 32));

        //smallSwatchGroup = new QGroupBox(colorGroupBox);
        blackColorSwatch = new QPushButton(colorGroupBox);
        grayColorSwatch = new QPushButton(colorGroupBox);
        redColorSwatch = new QPushButton(colorGroupBox);
        darkRedColorSwatch = new QPushButton(colorGroupBox);
        magentaColorSwatch = new QPushButton(colorGroupBox);
        yellowColorSwatch = new QPushButton(colorGroupBox);
        greenColorSwatch = new QPushButton(colorGroupBox);
        darkGreenColorSwatch = new QPushButton(colorGroupBox);
        blueColorSwatch = new QPushButton(colorGroupBox);
        darkBlueColorSwatch = new QPushButton(colorGroupBox);
        cyanColorSwatch = new QPushButton(colorGroupBox);
        whiteColorSwatch = new QPushButton(colorGroupBox);


        QPixmap smallColorPixmap(20, 20);
        smallColorPixmap.fill( Qt::black );
        blackColorSwatch->setFlat(true);
        blackColorSwatch->setMaximumSize(20, 20);
        blackColorSwatch->setIcon(QIcon(smallColorPixmap));
        blackColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::red );
        redColorSwatch->setFlat(true);
        redColorSwatch->setMaximumSize(20, 20);
        redColorSwatch->setIcon(QIcon(smallColorPixmap));
        redColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::green );
        greenColorSwatch->setFlat(true);
        greenColorSwatch->setMaximumSize(20, 20);
        greenColorSwatch->setIcon(QIcon(smallColorPixmap));
        greenColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::blue );
        blueColorSwatch->setFlat(true);
        blueColorSwatch->setMaximumSize(20, 20);
        blueColorSwatch->setIcon(QIcon(smallColorPixmap));
        blueColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::white );
        whiteColorSwatch->setFlat(true);
        whiteColorSwatch->setMaximumSize(20, 20);
        whiteColorSwatch->setIcon(QIcon(smallColorPixmap));
        whiteColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::gray );
        grayColorSwatch->setFlat(true);
        grayColorSwatch->setMaximumSize(20, 20);
        grayColorSwatch->setIcon(QIcon(smallColorPixmap));
        grayColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::darkBlue );
        darkBlueColorSwatch->setFlat(true);
        darkBlueColorSwatch->setMaximumSize(20, 20);
        darkBlueColorSwatch->setIcon(QIcon(smallColorPixmap));
        darkBlueColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::darkRed );
        darkRedColorSwatch->setFlat(true);
        darkRedColorSwatch->setMaximumSize(20, 20);
        darkRedColorSwatch->setIcon(QIcon(smallColorPixmap));
        darkRedColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::darkGreen );
        darkGreenColorSwatch->setFlat(true);
        darkGreenColorSwatch->setMaximumSize(20, 20);
        darkGreenColorSwatch->setIcon(QIcon(smallColorPixmap));
        darkGreenColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::magenta );
        magentaColorSwatch->setFlat(true);
        magentaColorSwatch->setMaximumSize(20, 20);
        magentaColorSwatch->setIcon(QIcon(smallColorPixmap));
        magentaColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::yellow );
        yellowColorSwatch->setFlat(true);
        yellowColorSwatch->setMaximumSize(20, 20);
        yellowColorSwatch->setIcon(QIcon(smallColorPixmap));
        yellowColorSwatch->setIconSize(QSize(20, 20));

        smallColorPixmap.fill( Qt::cyan );
        cyanColorSwatch->setFlat(true);
        cyanColorSwatch->setMaximumSize(20, 20);
        cyanColorSwatch->setIcon(QIcon(smallColorPixmap));
        cyanColorSwatch->setIconSize(QSize(20, 20));

        smallSwatchLayout = new QGridLayout();
        smallSwatchLayout->setSizeConstraint(QLayout::SetMinimumSize);
        smallSwatchLayout->setMargin(0);
        smallSwatchLayout->addWidget(blackColorSwatch, 0, 0);
        smallSwatchLayout->addWidget(grayColorSwatch, 0, 1);
        smallSwatchLayout->addWidget(whiteColorSwatch, 0, 2);
        smallSwatchLayout->addWidget(redColorSwatch, 0, 3);
        smallSwatchLayout->addWidget(darkRedColorSwatch, 0, 4);
        smallSwatchLayout->addWidget(magentaColorSwatch, 0, 5);
        smallSwatchLayout->addWidget(greenColorSwatch, 1, 0);
        smallSwatchLayout->addWidget(darkGreenColorSwatch, 1, 1);
        smallSwatchLayout->addWidget(yellowColorSwatch, 1, 2);
        smallSwatchLayout->addWidget(cyanColorSwatch, 1, 3);
        smallSwatchLayout->addWidget(blueColorSwatch, 1, 4);
        smallSwatchLayout->addWidget(darkBlueColorSwatch, 1, 5);

        //smallSwatchGroup->setLayout(smallSwatchLayout);
        //smallSwatchGroup->setSizePolicy(QSizePolicy::Minimum);
        //smallSwatchGroup->setFlat(true);

        swatchLayout = new QHBoxLayout();
        swatchLayout->setMargin(0);
        swatchLayout->setAlignment(Qt::AlignCenter);
        swatchLayout->addLayout(smallSwatchLayout);
        swatchLayout->addWidget(colorSwatch, 1, Qt::AlignHCenter);


        colorBoxLayout = new QHBoxLayout();
        colorBoxLayout->addLayout(sliderLayout);
        colorBoxLayout->addLayout(swatchLayout);
        colorBoxLayout->setMargin(0);


        colorGroupBox->setLayout(colorBoxLayout);



  widthGroupBox = new  QGroupBox(this);
  widthGroupBox->setTitle("Set Width");
  widthGroupBox->setMaximumWidth(90);
    QLabel *labelPenWidth = new QLabel("Pencil");

    spinPenWidth = new QSpinBox(widthGroupBox);
    spinPenWidth->setValue(penWidthValue);
    spinPenWidth->setRange(1, 50);

    QLabel *labelEraserWidth = new QLabel("Eraser");
    spinEraserWidth = new QSpinBox(widthGroupBox);
    spinEraserWidth->setValue(eraserWidthValue);
    spinEraserWidth->setRange(1, 50);

        widthBoxLayout = new QGridLayout(widthGroupBox);
        widthBoxLayout->addWidget(labelPenWidth, 0 , 0);
        widthBoxLayout->addWidget(spinPenWidth, 1, 0);
        widthBoxLayout->addWidget(labelEraserWidth, 2, 0);
        widthBoxLayout->addWidget(spinEraserWidth, 3, 0);
        widthBoxLayout->setMargin(0);

    toolVBox = new QVBoxLayout();
    toolVBox->setMargin(0);
    toolVBox->addWidget(toolGBox, Qt::AlignLeft);
     //toolVBox->addWidget(colorGroupBox);
    toolVBox->addWidget(widthGroupBox);

    quteBoardHBox->addLayout(toolVBox);
  //quteBoardHBox->addWidget(toolGBox);
  //quteBoardHBox->addWidget(widthGroupBox);

}

//-- Close Event --
void Graffiti::closeEvent(QCloseEvent *event)

{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}


//-- Open Menu Item --
void Graffiti::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            graffitiArea->openImage(fileName);
    }
}


//-- Save Menu Item --
void Graffiti::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

//-- Change Color From Image Point Slot --
void Graffiti::colorChanged()
{
        updateColorBox(graffitiArea->penColor());
      //  qDebug() <<"Color:: ";
}

//-- Change Color Slot --
void Graffiti::changeColor()
{
    QColor newColor = QColorDialog::getColor(graffitiArea->penColor());
    if (newColor.isValid())
        graffitiArea->setPenColor(newColor);
        updateColorBox(newColor);
}


//-- Change Color to Black --
void Graffiti::changeColorBlack()
{
    if(graffitiArea->penColor() != Qt::black){
    QColor newColorToBlack = Qt::black;
    if (newColorToBlack.isValid()){
        graffitiArea->setPenColor(newColorToBlack);
        updateColorBox(newColorToBlack);
    }
  }
}

void Graffiti::changeColorRed()
//-- Change Color to Red --
{
    if(graffitiArea->penColor() != Qt::red){
    QColor newColorToRed = Qt::red;
    if (newColorToRed.isValid()){
        graffitiArea->setPenColor(newColorToRed);
        updateColorBox(newColorToRed);
    }
    }
}

//-- Change Color to Green --
void Graffiti::changeColorGreen()
{
    if(graffitiArea->penColor() != Qt::green){
    QColor newColorToGreen = Qt::green;
    if (newColorToGreen.isValid()){
        graffitiArea->setPenColor(newColorToGreen);
        updateColorBox(newColorToGreen);
    }
    }
}

//-- Change Color to Blue --
void Graffiti::changeColorBlue()
{
    if(graffitiArea->penColor() != Qt::blue){
    QColor newColorToBlue = Qt::blue;
    if (newColorToBlue.isValid()){
        graffitiArea->setPenColor(newColorToBlue);
        updateColorBox(newColorToBlue);
    }
    }
}

//-- Change Color to White --
void Graffiti::changeColorWhite()
{
    if(graffitiArea->penColor() != Qt::white){
    QColor newColorToWhite = Qt::white;
    if (newColorToWhite.isValid()){
        graffitiArea->setPenColor(newColorToWhite);
        updateColorBox(newColorToWhite);
    }
    }
}

//-- Change Color to Gray --
void Graffiti::changeColorGray()
{
    if(graffitiArea->penColor() != Qt::gray){
        QColor newColorToGray = Qt::gray;

        updateColorBox(newColorToGray);
        graffitiArea->setPenColor(newColorToGray);

 }
}

//-- Change Color to Cyan --
void Graffiti::changeColorCyan()
{
    if(graffitiArea->penColor() != Qt::cyan){
        graffitiArea->setPenColor(Qt::cyan);
        updateColorBox(Qt::cyan);
  }
}

//-- Change Color to Red --
void Graffiti::changeColorDarkRed()
{
    if(graffitiArea->penColor() != Qt::darkRed){
        graffitiArea->setPenColor(Qt::darkRed);
        updateColorBox(Qt::darkRed);
    }
}

//-- Change Color to Dark Green --
void Graffiti::changeColorDarkGreen()
{
    if(graffitiArea->penColor() != Qt::darkGreen){
    QColor newColorToDarkGreen = Qt::darkGreen;
        graffitiArea->setPenColor(Qt::darkGreen);
        updateColorBox(Qt::darkGreen);
    }
}

//-- Change Color to Dark Blue --
void Graffiti::changeColorDarkBlue()
{
    if(graffitiArea->penColor() != Qt::darkBlue){
         graffitiArea->setPenColor(Qt::darkBlue);
        updateColorBox(Qt::darkBlue);
    }
}

//-- Change Color to Magenta --
void Graffiti::changeColorMagenta()
{
    if(graffitiArea->penColor() != Qt::magenta){
        graffitiArea->setPenColor(Qt::magenta);
        updateColorBox(Qt::magenta);
    }
}

//-- Change Color to Yellow --
void Graffiti::changeColorYellow()
{
    if(graffitiArea->penColor() != Qt::yellow){
        updateColorBox(Qt::yellow);
        graffitiArea->setPenColor(Qt::yellow);
 }
}

//--  RedSlider Changed --
void Graffiti::redSliderChanged(int newValue)
{
    QColor newColor = QColor( newValue, valueGreen, valueBlue);
    graffitiArea->setPenColor(newColor);
    updateColorBox(newColor);
}

//-- GreenSlider Changed --
void Graffiti::greenSliderChanged(int newValue)
{
    QColor newColor = QColor( valueRed, newValue, valueBlue);
    graffitiArea->setPenColor(newColor);
    updateColorBox(newColor);
}

//-- BlueSlider Changed --
void Graffiti::blueSliderChanged(int newValue)
{
    QColor newColor = QColor(valueRed, valueGreen, newValue);
    graffitiArea->setPenColor(newColor);
    updateColorBox(newColor);
}

//-- penSliderChanged i.e., PenWidth Changed --
void Graffiti::penSliderChanged(int newWidth)
{
    graffitiArea->setPenWidth(newWidth);
    updatePenWidth(newWidth);
}

//-- eraserSliderChanged i.e., EraserWidth Changed --
void Graffiti::eraserSliderChanged(int newWidth)
{
    graffitiArea->setEraserWidth(newWidth);
    updateEraserWidth(newWidth);
}




//-- PenWidth --
void Graffiti::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInteger(this, tr("Graffiti"),
                                            tr("Select pen width:"),
                                            graffitiArea->penWidth(),
                                            1, 50, 1, &ok);
    if (ok){
        graffitiArea->setPenWidth(newWidth);
        updatePenWidth(newWidth);
    }

}

//-- Erase Width --
void Graffiti::eraserWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInteger(this, tr("Graffiti"),
                                            tr("Select eraser width:"),
                                            graffitiArea->eraserWidth(),
                                            1, 50, 1, &ok);
    if (ok){
        graffitiArea->setEraserWidth(newWidth);
        updateEraserWidth(newWidth);
    }

}


//-- Fill Color Change --
void Graffiti::fillColor()
{
    QColor newColor = QColorDialog::getColor(graffitiArea->fillColor());
    if (newColor.isValid())
        graffitiArea->setFillColor(newColor);

}

//-- About Menu --
void Graffiti::about()
{
    QMessageBox::about(this, tr("About Graffiti"),
            tr("<p>The <b>Graffiiti</b> -dunno what to write, will tell you later "
               "on completion.</p>"));
}

//-- Update Color Box --
void Graffiti::updateColorBox(QColor color)
{
    QPixmap colorPix(64, 64);
    colorPix.fill(color );
    colorSwatch->setIcon(QIcon(colorPix));
    valueRed = 0;
    valueGreen = 0;
    valueBlue = 0;
    color.getRgb(&valueRed, &valueGreen, &valueBlue);
    sliderRed->setSliderPosition(valueRed);
    sliderGreen->setSliderPosition(valueGreen);
    sliderBlue->setSliderPosition(valueBlue);
    QString rgbValue;
    rgbValue.setNum(valueRed);
    labelRedValue->setText(rgbValue);
    rgbValue.setNum(valueGreen);
    labelGreenValue->setText(rgbValue);
    rgbValue.setNum(valueBlue);
    labelBlueValue->setText(rgbValue);
  }

//-- Update Pen Width --
void Graffiti::updatePenWidth(int newWidth)
{
    spinPenWidth->setValue(newWidth);
}


//-- Update Eraser Width --
void Graffiti::updateEraserWidth(int newWidth)
{
    spinEraserWidth->setValue(newWidth);
}



//-- Create Actions Function --
void Graffiti::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), graffitiArea, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(changeColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));
    
    eraserWidthAct = new QAction(tr("Eraser &Width..."), this);
    connect(eraserWidthAct, SIGNAL(triggered()), this, SLOT(eraserWidth()));

    fillColorAct = new QAction(tr("F&ill Color..."), this);
    connect(fillColorAct, SIGNAL(triggered()), this, SLOT(changeColor()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            graffitiArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    
    connect(pencilTool, SIGNAL(clicked()), graffitiArea, SLOT(pencilPressEvent()));
    connect(clearTool, SIGNAL(clicked()), graffitiArea, SLOT(clearImage()));
    connect(lineTool, SIGNAL(clicked()), graffitiArea, SLOT(linePressEvent()));
    connect(eraserTool, SIGNAL(clicked()), graffitiArea, SLOT(eraserPressEvent()));
    connect(rectangleTool, SIGNAL(clicked()), graffitiArea, SLOT(rectanglePressEvent()));
    connect(ellipseTool, SIGNAL(clicked()), graffitiArea, SLOT(ellipsePressEvent()));
    connect(fillTool, SIGNAL(clicked()), graffitiArea, SLOT(fillPressEvent()));
    connect(textTool, SIGNAL(clicked()), graffitiArea, SLOT(textPressEvent()));
    connect(colorSelectionTool, SIGNAL(clicked()), graffitiArea, SLOT(colorSelPressEvent()));
    connect(spinPenWidth, SIGNAL(valueChanged(int)), this, SLOT(penSliderChanged(int)));
    //connect(labelPenWidthValue, SIGNAL(clicked()), this, SLOT(penWidth()));
    connect(spinEraserWidth, SIGNAL(valueChanged(int)), this, SLOT(eraserSliderChanged(int)));
    //connect(labelEraserWidthValue, SIGNAL(clicked()), this, SLOT(eraserWidth()));
    connect(colorSwatch, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(blackColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorBlack()));
    connect(redColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorRed()));
    connect(greenColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorGreen()));
    connect(blueColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorBlue()));
    connect(whiteColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorWhite()));
    connect(grayColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorGray()));
    connect(darkRedColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorDarkRed()));
    connect(yellowColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorYellow()));
    connect(cyanColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorCyan()));
    connect(darkGreenColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorDarkGreen()));
    connect(darkBlueColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorDarkBlue()));
    connect(magentaColorSwatch, SIGNAL(clicked()), this, SLOT(changeColorMagenta()));
    connect(sliderRed,  SIGNAL(valueChanged(int)), this, SLOT(redSliderChanged(int)));
    connect(sliderGreen,  SIGNAL(valueChanged(int)), this, SLOT(greenSliderChanged(int)));
    connect(sliderBlue,  SIGNAL(valueChanged(int)), this, SLOT(blueSliderChanged(int)));
    connect(zoomTool,  SIGNAL(clicked()), graffitiArea, SLOT(imagePressEvent()));
}


//-- Create Menus Function --
void Graffiti::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/graffiti/images/graffiti_small.png")), QIcon::Normal, QIcon::Off);
    saveAsMenu->setIcon(icon);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addAction(eraserWidthAct);
    optionMenu->addAction(fillColorAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    //menuBar()->addMenu(fileMenu);
    //menuBar()->addMenu(optionMenu);
    //menuBar()->addMenu(helpMenu);
}


//-- Maybe Save Or Not Check --
bool Graffiti::maybeSave()
{
    if (graffitiArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Graffiti"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
			  | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}


//-- Save File --
bool Graffiti::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString(fileFormat.toUpper()))
                               .arg(QString(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return graffitiArea->saveImage(fileName, fileFormat);
    }
}

