///////////////////////////////////////////////////////////////////////////
// oliveinterface.h
// IceCuBe Messenger
//
// © Rohit Yadav, Abhishek Kumar, 2008-2009.
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#ifndef OLIVEINTERFACE_H
#define OLIVEINTERFACE_H

#include <QtGui>
#include "graffiti.h"

class OliveInterface : public QMainWindow
{
  Q_OBJECT

  public:
    OliveInterface(QWidget *parent = 0 );
    void InitFileMenu();
    void InitBody(bool isMainGui);
    void InitToolBar();
    void InitStatusBar();
    void ReTranslate();

    void createTrayIcon();
    void createTrayIconMenu();

    Graffiti *graffiti;

  private:
    //bool  isMainGui;

    QMenuBar    *menuBar;
    QStatusBar  *statusBar;
    QToolBar    *toolBar;

    QWidget     *mainFrame;
    QHBoxLayout *mainHBox;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;

    public:
    QWidget     *userCloudWidget;
    QWidget     *graffitiWidget;
    QWidget     *logWidget;

    QVBoxLayout *peerCloudVBox;
    QTreeWidget *peerCloud;
    QPushButton *refreshButton;
    QLineEdit   *peerSearchTextBox;

    QVBoxLayout *logVBox;
    QTextEdit   *logTextBox;

    public:
    QGroupBox   *chatGBox;
    //IceQuBe     *chatWindow;
    QVBoxLayout *chatVBox;
    QTextEdit   *msgDisplay;
    QLineEdit   *msgInput;

    QListWidget *listWidget;

    //-- SysTray Icon --
    QSystemTrayIcon *trayIcon;
    QMenu           *trayIconMenu;

  private slots:
    void OnNewMsg();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // OLIVEINTERFACE_H
