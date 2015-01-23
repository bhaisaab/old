///////////////////////////////////////////////////////////////////////////
// oliveinterface.cpp
// IceCuBe Messenger
//
// © Rohit Yadav, Abhishek Kumar, 2008-2009.
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include "oliveinterface.h"

OliveInterface::OliveInterface(QWidget *parent) : QMainWindow(parent)
{
  //this->isMainGui = isMainGui;

  //-- Tray Icon and Menu --
  //if(isMainGui == true)
    createTrayIcon();

  InitBody(1);
  InitFileMenu();
  //if(isMainGui == true)
  //InitToolBar();
  InitStatusBar();
  ReTranslate();
  //setAttribute(Qt::WA_MacBrushedMetal);
  int col;
  #ifdef MAC
  col = 140;
  #else
  col = 200;
  #endif
  //this->setPalette(QColor(col, col, col));
}

void OliveInterface::createTrayIcon()
{
  QIcon appIcon(":/graffiti/images/graffiti_small.png");//("/images/trash.svg");

  createTrayIconMenu();
  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setIcon(appIcon);
  trayIcon->setContextMenu(trayIconMenu);
  trayIcon->setToolTip(QString("Click to Launch a New Message"));
  trayIcon->show();

  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
           this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

  setWindowIcon(appIcon);
}

void OliveInterface::createTrayIconMenu()
{
  QAction* newMsgAction = new QAction(tr("&New Message"), this);
  connect(newMsgAction, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  QAction* minimizeAction = new QAction(tr("Mi&nimize"), this);
  connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

  QAction* maximizeAction = new QAction(tr("Ma&ximize"), this);
  connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

  QAction* restoreAction = new QAction(tr("&Restore"), this);
  connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

  QAction* quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(newMsgAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(minimizeAction);
  trayIconMenu->addAction(maximizeAction);
  trayIconMenu->addAction(restoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);
}

void OliveInterface::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        OnNewMsg();
        printf("Double Click\n");
        break;
    case QSystemTrayIcon::MiddleClick:
        OnNewMsg();
        printf("Middle Click\n");
        break;
    default:
        ;
    }
}

void OliveInterface::InitFileMenu()
{
    QIcon icon;

    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));

    QMenu *fileMenu = new QMenu(menuBar);
    fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
    fileMenu->setTitle("&File");

    QAction *actionNew = new QAction(this);
    actionNew->setText("&New Msg");
    icon.addPixmap(QPixmap(QString::fromUtf8(":/32x32/images/PNGs/32x32/icon.png")), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon);

    QAction *actionQuit = new QAction(this);
    actionQuit->setText("&Quit");
    icon.addPixmap(QPixmap(QString::fromUtf8(":/32x32/images/PNGs/32x32/open.png")), QIcon::Normal, QIcon::Off);
    actionQuit->setIcon(icon);
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    fileMenu->addAction(actionNew);
    fileMenu->addMenu(graffiti->saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(actionQuit);

    menuBar->addMenu(fileMenu);
    //menuBar->addMenu(graffiti->saveAsMenu);

    this->setMenuBar(menuBar);

}

void OliveInterface::InitToolBar()
{
  QPixmap newPix(":/32x32/images/PNGs/32x32/usermic.png");
  QPixmap connectPix(":/32x32/images/PNGs/32x32/connect.png");
  QPixmap statusPix(":/32x32/images/PNGs/32x32/available.png");
  QPixmap settingsPix(":/32x32/images/PNGs/32x32/configure.png");
  QPixmap separatorPix(":/32x32/images/PNGs/32x32/separator.png");
  QPixmap quitPix(":/32x32/images/PNGs/32x32/userliston.png");

  toolBar = new QToolBar(this);
  toolBar->setObjectName(QString::fromUtf8("toolBar"));

  this->addToolBar(toolBar);

  QAction *newMsg = toolBar->addAction(QIcon(newPix), "New Msg.");
  newMsg->setShortcut(tr("Ctrl+N"));
  newMsg->setStatusTip(tr("Create New IceMessage!"));
  connect(newMsg, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  QAction *connectTo = toolBar->addAction(QIcon(connectPix), "Connect to IP/Range");
  connectTo->setShortcut(tr("Ctrl+D"));
  connectTo->setStatusTip(tr("Connect to IP/Range"));
  connect(connectTo, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  QAction *status = toolBar->addAction(QIcon(statusPix), "Status");
  status->setShortcut(tr("Ctrl+T"));
  status->setStatusTip(tr("Toggle Availablity Status"));
  connect(status, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  QAction *preferences = toolBar->addAction(QIcon(settingsPix), "Preferences");
  preferences->setShortcut(tr("Ctrl+P"));
  preferences->setStatusTip(tr("Configure IceQuBe Settings"));
  connect(preferences, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  QAction *separator = toolBar->addAction(QIcon(separatorPix), "Hide Left Panel");
  separator->setStatusTip(tr("Toggle Navigation NoteBook Panel Visibility"));
  connect(separator, SIGNAL(triggered()), this, SLOT(OnNewMsg()));

  //toolBar->addSeparator();

  QAction *quit = toolBar->addAction(QIcon(quitPix), "Exit IceQuBe");
  quit->setStatusTip(tr("Exit IceQuBe"));
  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

  this->setUnifiedTitleAndToolBarOnMac(true);
}

void OliveInterface::InitStatusBar()
{
  statusBar = new QStatusBar(this);
  statusBar->setObjectName(QString::fromUtf8("statusbar"));

  this->setStatusBar(statusBar);
}

void OliveInterface::InitBody(bool isMainGui)
{
// MainGUI Tree (To be completed)

    mainFrame = new QWidget(this);
    mainFrame->setObjectName(QString::fromUtf8("mainFrame"));

    mainHBox = new QHBoxLayout(mainFrame);
    mainHBox->setObjectName(QString::fromUtf8("mainHBox"));

    leftVBox = new QVBoxLayout();
    leftVBox->setObjectName(QString::fromUtf8("leftVBox"));

    userCloudWidget = new QWidget(this);
    graffitiWidget = new QWidget(this);
    logWidget = new QWidget(this);

    leftVBox->addWidget(graffitiWidget, 1);

    //-- BuddyCloud --
    peerCloudVBox = new QVBoxLayout();
    peerCloudVBox->setMargin(0);

    listWidget = new QListWidget();

    peerCloud = new QTreeWidget(this);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/16x16/images/PNGs/16x16/user.png")), QIcon::Normal, QIcon::Off);
    peerCloud->headerItem()->setIcon(0, icon);

    peerCloud->setObjectName(QString::fromUtf8("peerCloud"));
    peerCloud->setEditTriggers(QAbstractItemView::NoEditTriggers);
    peerCloud->setSelectionMode(QAbstractItemView::MultiSelection);
    peerCloud->setSortingEnabled(true);
    peerCloud->setWordWrap(true);
    peerCloud->setColumnCount(5);

    //peerCloud->setVisible(false);

    peerCloud->headerItem()->setText(0, "");
    peerCloud->headerItem()->setText(1, "Nick");
    peerCloud->headerItem()->setText(2, "IP");
    peerCloud->headerItem()->setText(3, "Port");
    peerCloud->headerItem()->setText(4, "Group");
    peerCloud->headerItem()->setText(5, "Description");

    peerSearchTextBox = new QLineEdit("Search Peer");
    peerSearchTextBox->setBackgroundRole(QPalette::Light);
    peerSearchTextBox->setFocusPolicy(Qt::NoFocus);
    refreshButton = new QPushButton("Refresh");

    QHBoxLayout *peerListHBox = new QHBoxLayout();
    //peerCloudVBox->addWidget(peerCloud);
    peerListHBox->addWidget(peerSearchTextBox);
    peerListHBox->addWidget(refreshButton);

    peerCloudVBox->addWidget(listWidget);
    peerCloudVBox->addLayout(peerListHBox);
    peerCloudVBox->addWidget(refreshButton);
    peerCloudVBox->setMargin(10);

    //-- Graffiti: The IceQuBe WhiteBoard --
    graffiti = new Graffiti(this);
    QHBoxLayout *graffitiHBox = new QHBoxLayout(graffitiWidget);
    graffitiHBox->addWidget(graffiti);
    //graffitiHBox->setMargin(0);

    //-- IceQuBe Log --
    logTextBox = new QTextEdit();
    logTextBox->setObjectName(QString::fromUtf8("logTextBox"));
    logTextBox->setText("Logging!");

    QHBoxLayout *logHBox = new QHBoxLayout(logWidget);
    logHBox->addWidget(logTextBox);


  //--Right VBox: ChatGBox->ChatHBox --
  rightVBox = new QVBoxLayout();
  rightVBox->setObjectName(QString::fromUtf8("rightVBox"));
  rightVBox->setMargin(5);

  //-- IceQuBe ChatGBox--
  chatGBox = new QGroupBox(mainFrame);
  chatGBox->setObjectName(QString::fromUtf8("chatGBox"));
  chatGBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
  chatGBox->setMaximumSize(QSize(300, 16777215));
  chatGBox->setMinimumSize(QSize(250, 250));
  chatGBox->setFlat(false);

  //-- Add IceQuBe ChatWindow --
  chatVBox = new QVBoxLayout(chatGBox);
  chatVBox->setObjectName(QString::fromUtf8("chatVBox"));

  msgDisplay = new QTextEdit(chatGBox);
  msgDisplay->setObjectName(QString::fromUtf8("msgDisplay"));
  msgDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  msgDisplay->setReadOnly(true);

  msgInput = new QLineEdit(chatGBox);
  msgInput->setObjectName(QString::fromUtf8("msgInput"));
  msgInput->setMaximumSize(QSize(16777215, 50));

  chatVBox->addWidget(msgDisplay);
  chatVBox->addWidget(msgInput);

  msgDisplay->raise();
  msgInput->raise();

//  rightVBox->SetMaximumSize(QSize(300, 16777215));
//  rightVBox->SetMinimumSize(QSize(250, 400));
  rightVBox->addWidget(listWidget);
  rightVBox->addWidget(logWidget);//peerCloud);
  rightVBox->addWidget(chatGBox);

  //-- Add Layouts to mainHBox --
  mainHBox->addLayout(leftVBox);
  mainHBox->addLayout(rightVBox);
  mainHBox->setMargin(0);

  //setLayout(mainHBox);

  this->setCentralWidget(mainFrame);
}

void OliveInterface::ReTranslate()
{
  Q_UNUSED(this);
}

void OliveInterface::OnNewMsg()
{
  statusBar->showMessage("Launching New Message", 2000);
}
