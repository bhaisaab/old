///////////////////////////////////////////////////////////////////////////
// mainframe.h
// IceCuBe
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/gauge.h>
#include <wx/frame.h>
#include <wx/srchctrl.h>
#include <wx/splitter.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/imaglist.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>

#include "wx/dnd.h"
#include "wx/dataobj.h"
#include "wx/image.h"
#include "wx/clipbrd.h"
#include "wx/colordlg.h"
#include "wx/metafile.h"
#include "wx/file.h"

#include "statusbar.h"

#include "wx/socket.h"
#include "wx/wfstream.h"

typedef int splitlength;

///////////////////////////////////////////////////////////////////////////////
/// Enumerations
///////////////////////////////////////////////////////////////////////////////
enum
{
  ID_MULTICAST_TEXTBOX,
  ID_TEXT_INPUT,
  ID_STATUSBAR,
  ID_TOOLBAR,
  ID_TOOLBAR_SEPARATOR,
  ID_TOGGLE_USERLIST,

  ID_NEW = wxID_NEW,
  ID_REFRESH = wxID_REFRESH,
  ID_CONNECT,
  
  ID_UNDO = wxID_UNDO,
  ID_REDO = wxID_REDO,
  ID_CUT = wxID_CUT,
  ID_COPY = wxID_COPY,
  ID_PASTE = wxID_PASTE,
  ID_CLEAR = wxID_CLEAR,
  ID_SELECT_ALL = wxID_SELECTALL,

  ID_STATUS,
  ID_AVAILABLE,
  ID_BUSY,
  ID_CUSTOM_MSG,

  ID_ATTACHMENT_STATUS,
  ID_LOG,
  ID_EDIT_PROFILE,
  ID_SETTINGS = wxID_PREFERENCES,

  ID_HELP = wxID_HELP,
  ID_NOTES,
  ID_ON_WEB,
  ID_ABOUT = wxID_ABOUT,
  ID_EXIT = wxID_EXIT,
  // -- IDs for sockets --
  SERVER_ID = 900,
  SOCKET_ID,
  CLIENT_OPEN = 1000,
  CLIENT_TEST2,
  CLIENT_CLOSE,
  CLIENT_DGRAM,
  CLIENT_ID
};

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
  private:
	  DECLARE_EVENT_TABLE()
 	  wxSocketServer* iceServer;
    wxSocketClient* cubeClient;
    int             totalUsers;
    bool            busy;

  public:
    void OnServerEvent(wxSocketEvent& event);
    void OnSocketEvent(wxSocketEvent& event);
    void Test2(wxSocketBase *sock);
    
    // event handlers for Socket menu
    void OnClientEvent(wxSocketEvent& event);
    void OnOpenConnection(wxCommandEvent& event);
    void OnCloseConnection(wxCommandEvent& event);
    void SendText();

  protected:
    //StatusBar
    //wxStatusBar*   StatusBar;
	  CarbonBar*     StatusBar;
    
    //MenuBar
    wxMenuBar*     MenuBar;
    wxMenu*        File;
    wxMenu*        Edit;
    wxMenu*        Tools;
    wxMenu*        Absence;
    wxMenu*        Help;

    wxToolBar* ToolBar;
    bool status;
    bool userlist;
    bool navbar;
    bool sw_stat;
    
    wxImageList* ImageList;
    
    splitlength navbarLength;
    splitlength msgboxLength;
    
    wxSplitterWindow* MainSplitter;
	  wxSplitterWindow* HorizontalSplitter;
	  
	  wxPanel*          LeftPanel;
	  wxPanel*          NavPanel;
    wxPanel*          WBPanel;
    wxPanel*          TransferPanel;
    wxPanel*          LogPanel;
	  wxPanel*          UserPanel;
	      
	  wxPanel*          RightPanel;
	  wxPanel*          MsgPanel;    
	
	  wxNotebook*       Navigation;
	  wxTextCtrl*       Log;
	
	  wxStaticBoxSizer* MsgSBSizer;
	  wxRichTextCtrl*   MsgTextBox;
	  wxTextCtrl*       InputTextBox;
	  wxColour          UserNickColour;
    wxString          UserNickName; 

    wxStaticBoxSizer* UserSBSizer;
	  wxListCtrl*       UserList;
	  wxListItem        column;
	  wxSearchCtrl*     Search;
    wxButton*         Refresh;
	
  public:
    MainFrame( wxWindow* parent, wxWindowID id , const wxString& title , const wxPoint& pos, const wxSize& size, long style );
    ~MainFrame();
    
//    void OnSize(wxSizeEvent& event);
    void UpdateStatusBar();
    
    splitlength GetSplitRatio(bool compartment);

	  void OnAvailable(wxCommandEvent& event);
	  void OnBusy(wxCommandEvent& event);
	  void OnCustomMsg(wxCommandEvent& event);
	
    void OnStatusToggle(wxCommandEvent& event);
    void OnUserListToggle(wxCommandEvent& event);
    void OnSeparatorToggle(wxCommandEvent& event);
    	
    void PrintText(const wxString s);
	  void OnTextEnter(wxCommandEvent& event);
	  wxString GetUserNick();
	  wxColour GetUserNickColour();
	  
	  void OnAbout( wxCommandEvent& event );
	  void OnQuit( wxCommandEvent& event );
	
    void InitStatusBar();
    void InitFileMenu();
    void InitToolBar();
    void InitBody();
    void InitNavigation();
    void InitUserPanel();

	void MainSplitterOnIdle( wxIdleEvent& )
	{
	  MainSplitter->SetSashPosition( GetSplitRatio(false), true );
	  MainSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::MainSplitterOnIdle ), NULL, this );
	}
	
	void HorizontalSplitterOnIdle( wxIdleEvent& )
	{
	  HorizontalSplitter->SetSashPosition( 50 );
	  HorizontalSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::HorizontalSplitterOnIdle ), NULL, this );
	}
	
};

#endif //MAIN__H

