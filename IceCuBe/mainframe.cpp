///////////////////////////////////////////////////////////////////////////
// mainframe.cpp
// IceCuBe
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#import  <wx/wx.h>
#include <wx/srchctrl.h>
#include <wx/mstream.h>
#include <wx/bmpcbox.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/imaglist.h>
#include <wx/button.h>
#include <wx/utils.h>

#include "wx/socket.h"
#include "wx/wfstream.h"

#include "wx/dnd.h"
#include "wx/dataobj.h"
#include "wx/image.h"
#include "wx/clipbrd.h"
#include "wx/colordlg.h"
#include "wx/metafile.h"
#include "wx/file.h"

#include "mainframe.h"
#include "png.h"

// -- Embedd PNG Images --
#include "png/iconbig.h"
#include "png/iconsmall.h"
#include "png/smileys.h"

// -- IceCube Window Icon --
#include "icon.xpm"
#include <wx/icon.h>

///////////////////////////////////////////////////////////////////////////////
/// Event Table: Connect won't work everytime as in case of timers :-(
///////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
//  EVT_SIZE(MainFrame::OnSize)
  EVT_TOOL(ID_STATUS, MainFrame::OnStatusToggle)
	EVT_TOOL(ID_TOGGLE_USERLIST, MainFrame::OnUserListToggle)
  EVT_TOOL(ID_TOOLBAR_SEPARATOR, MainFrame::OnSeparatorToggle)
  EVT_TEXT_ENTER(ID_TEXT_INPUT, MainFrame::OnTextEnter)
  
  EVT_SOCKET(SERVER_ID,  MainFrame::OnServerEvent)
  EVT_SOCKET(SOCKET_ID,  MainFrame::OnSocketEvent)
  
  EVT_SOCKET(CLIENT_ID,  MainFrame::OnClientEvent)
  EVT_TOOL(ID_CONNECT,  MainFrame::OnOpenConnection)
  EVT_TOOL(CLIENT_CLOSE, MainFrame::OnCloseConnection)
END_EVENT_TABLE()


// -- About Box --
void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("Welcome to IceCuBe!\n")
                    _T("\n")
                    _T("This is \"Proof of Concept\" cross platform LAN messenger.\n")
                    _T("This is depreciated and ScuttleButt Messenger(Qt/C++) is in development by the author.\n")
                    _T("Author: Rohit Yadav (rohityadav89@gmail.com)")
                 ),
                 _T("About IceCuBe"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

// -- Quit Method --
void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
  Close(true);
  //wxExit();
}

// -- On Available --
void MainFrame::OnAvailable(wxCommandEvent& WXUNUSED(event))
{
	
}

// -- On Busy --
void MainFrame::OnBusy(wxCommandEvent& WXUNUSED(event))
{
	
}

// -- On Custom Msg --
void MainFrame::OnCustomMsg(wxCommandEvent& WXUNUSED(event))
{
	
}

// -- Toggle Status --
void MainFrame::OnStatusToggle(wxCommandEvent& event)
{
  if(status == true)
  {
	  ToolBar->SetToolNormalBitmap( ID_STATUS, GetPNG(busy) );
	  status = false;	
  }
  else
  {
	  ToolBar->SetToolNormalBitmap( ID_STATUS, GetPNG(available) );
	  status = true;	
  }
  StatusBar->ToggleStatus();
  ToolBar->Realize();
  //Call network Determiner!...send busy/available signal
}

// -- Toggle UserList Visibility --
void MainFrame::OnUserListToggle(wxCommandEvent& event)
{
  if( userlist == true )
  {
    userlist = false;
    ToolBar->SetToolNormalBitmap( ID_TOGGLE_USERLIST, GetPNG(userlistoff) );
    //MainSplitter->SetSashPosition( GetSplitRatio(false), true );
    HorizontalSplitter->Unsplit(NULL);
  }
  else
  {
    userlist = true;
    ToolBar->SetToolNormalBitmap( ID_TOGGLE_USERLIST, GetPNG(userliston) );
    //MainSplitter->SetSashPosition( GetSplitRatio(false), true );
    HorizontalSplitter->SplitHorizontally( NavPanel, UserPanel, 200 );
  }
  ToolBar->Realize();
}

// -- On CarbonGrid Separator is clicked --
void MainFrame::OnSeparatorToggle(wxCommandEvent& event)
{
  if( navbar == true )
  {
    navbar = false;
    HorizontalSplitter->SplitHorizontally( NavPanel, UserPanel, 200 );
    HorizontalSplitter->Unsplit(NavPanel);
  }
  else
  {
    navbar = true;
    HorizontalSplitter->SplitHorizontally( NavPanel, UserPanel, 200 );
    HorizontalSplitter->Unsplit(NULL);
  }
}

// -- Intialize StatusBar --
void MainFrame::InitStatusBar()
{
  SetStatusBar(NULL);
  StatusBar = new CarbonBar(this, ID_STATUSBAR);
  SetStatusBar(StatusBar);	
}

// -- Intialize FileMenu --
#define ADDMENU(MENU, ID, NAME, TAG)  MENU->Append(ID, wxT(NAME), _T(TAG))
#define SEP(MENU) MENU->AppendSeparator()
void MainFrame::InitFileMenu()
{ 
  MenuBar = new wxMenuBar;
  File    = new wxMenu;
  Edit    = new wxMenu;  
  Tools   = new wxMenu;
  Absence = new wxMenu;
  Help    = new wxMenu;


  //<--FileMenu-->
  ADDMENU(File, ID_NEW, "&New Message\tCtrl-N", "Compose a new message!");
  SEP(File);
  ADDMENU(File, ID_REFRESH, "&Refresh Buddy List\tCtrl-R", "Refresh IceCuBe User List!");
  ADDMENU(File, ID_CONNECT, "&Connect to IP/RANGE\tAlt-C", "Connect to IP or Scan IP range for IceCuBe Users");
  SEP(File);
  ADDMENU(File, ID_EXIT, "&Quit\tCtrl-Q", "Quit IceCuBe Messenger!");

  //<--EditMenu-->
  ADDMENU(Edit, ID_UNDO, "&Undo\tCtrl-Z", "Undo last action!");
  ADDMENU(Edit, ID_REDO, "&Redo\tCtrl-Y", "Redo last action!");
  SEP(Edit);
  ADDMENU(Edit, ID_CUT, "&Cut\tCtrl-X", "Cut Selected Text!");
  ADDMENU(Edit, ID_COPY, "C&opy\tCtrl-C", "Copy Selected Text!");
  ADDMENU(Edit, ID_PASTE, "P&aste\tCtrl-V", "Paste Text!");
  SEP(Edit);
  ADDMENU(Edit, ID_CLEAR, "Clear &All", "Clear all the text!");
  ADDMENU(Edit, ID_SELECT_ALL, "&Select All\tCtrl-A", "Select all the text!");

  //<--AbsenceMode--> 
  ADDMENU(Absence, ID_BUSY, "&Busy\tCtrl-B", "Don't Disturb!");   
  ADDMENU(Absence, ID_AVAILABLE, "Avai&lable", "Available for Chat!"); 
  SEP(Absence);
  ADDMENU(Absence, ID_CUSTOM_MSG, "Custom &Message\tAlt-C", "Create Custom Message!");

  //<--Tools-->
  Tools->AppendSubMenu(Absence, wxT("&Absence"), _T("Select Absence Mode"));
  ADDMENU(Tools, ID_ATTACHMENT_STATUS, "&Attachment Status", "See Attachment Status");
  ADDMENU(Tools, ID_LOG, "IceCuBe &Log", "IceCuBe Log Viewer");
  SEP(Tools);
  ADDMENU(Tools, ID_EDIT_PROFILE, "&Edit Avatar\tCtrl-E", "Edit your IceCuBe Avatar");
  ADDMENU(Tools, ID_SETTINGS, "&Preferences\tCtrl-P", "Configure IceCuBe Settings");

  //<--HelpMenu-->
  ADDMENU(Help, ID_HELP, "IceCuBe &Help\tF1", "IceCuBe Help");
  ADDMENU(Help, ID_ABOUT, "&About", "About IceCuBe Messenger");
  SEP(Help);
  ADDMENU(Help, ID_NOTES, "&Release Notes", "IceCuBe Release Notes");
  ADDMENU(Help, ID_ON_WEB, "&IceCuBe On Web\tCtrl-W", "Goto IceCuBe WebSite");

  //<--MainMenuBar-->
  MenuBar->Append( File, wxT("&File") );
  MenuBar->Append( Edit, wxT("&Edit") );    
  MenuBar->Append( Tools, wxT("&Tools") );
  MenuBar->Append( Help, wxT("&Help") ); 

  //SetMenuBar(MenuBar);
  this->SetMenuBar( MenuBar );

  //<-- Connect Routines -->>

  // --  Set Status --
  Connect(ID_AVAILABLE, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(MainFrame::OnAvailable));

  Connect(ID_BUSY, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(MainFrame::OnBusy));

  Connect(ID_CUSTOM_MSG, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(MainFrame::OnCustomMsg));

  Connect(ID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(MainFrame::OnQuit));
  Connect(ID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(MainFrame::OnAbout));
	
}

// -- Intialize ToolBar --
void MainFrame::InitToolBar()
{
  ToolBar = this->CreateToolBar( wxTB_HORIZONTAL | wxTB_TEXT , ID_TOOLBAR );
  ToolBar->SetToolBitmapSize( wxSize( 32, 32 ) );
  ToolBar->SetToolSeparation( 20 );
//  ToolBar->SetMargins( wxSize( 10,5 ) );
//  ToolBar->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 92, false, wxEmptyString ) );
//  ToolBar->SetForegroundColour( wxColour( 146, 146, 146 ) );
//  ToolBar->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );

  ToolBar->AddTool( ID_NEW, wxT("New Msg"), GetPNG(usermic), wxNullBitmap, wxITEM_NORMAL, wxT("Compose New Message"), wxT("Compose New Message") );
//  ToolBar->AddTool( ID_REFRESH, wxT("Refresh Buddy List"), GetPNG(refresh), wxNullBitmap, wxITEM_NORMAL, wxT("Refresh IceCuBe User List"), wxEmptyString );
  ToolBar->AddTool( ID_CONNECT, wxT("Connect"), GetPNG(connect), wxNullBitmap, wxITEM_NORMAL, wxT("Connect to IP or IP Range"), wxT("Connect to IP or IP Range") );
  ToolBar->AddTool( ID_STATUS, wxT("Set Status"), GetPNG(available), wxNullBitmap, wxITEM_NORMAL, wxT("Select Status: Available/Busy"), wxT("Select Status: Available/Busy") );
  ToolBar->AddTool( ID_TOGGLE_USERLIST, wxT("Toggle UserList"), GetPNG(userliston), wxNullBitmap, wxITEM_NORMAL, wxT("Show/Hide UserList"), wxT("Show/Hide UserList") );
  userlist = true;
  //ToolBar->AddSeparator();
  ToolBar->AddTool( ID_TOOLBAR_SEPARATOR, wxT(""), GetPNG(separator), wxNullBitmap, wxITEM_NORMAL,  wxT("See the Magic!"),  wxT("See the Magic") );
  ToolBar->AddTool( ID_SETTINGS, wxT("Settings"), GetPNG(configure), wxNullBitmap, wxITEM_NORMAL, wxT("Configure IceCuBe Settings"), wxT("Configure IceCuBe Settings") );
  ToolBar->AddTool( ID_EXIT, wxT("Exit"), GetPNG(tree), wxNullBitmap, wxITEM_NORMAL, wxT("Quit IceCuBe"), wxT("Quit IceCuBe") );
  ToolBar->Realize();

  //<-- Connect Routines -->>
  
  // -- Connect --
  Connect(ID_CONNECT, wxEVT_COMMAND_TOOL_CLICKED,
    wxCommandEventHandler(MainFrame::OnOpenConnection));
    
  // -- Toggle Status --
  Connect(ID_STATUS, wxEVT_COMMAND_TOOL_CLICKED,
    wxCommandEventHandler(MainFrame::OnStatusToggle));
  
  // -- Toggle UserList Visibility --
  Connect(ID_TOGGLE_USERLIST, wxEVT_COMMAND_TOOL_CLICKED,
    wxCommandEventHandler(MainFrame::OnUserListToggle));

  // -- Toggle Separator: It's some hidden thing! --
  Connect(ID_TOOLBAR_SEPARATOR, wxEVT_COMMAND_TOOL_CLICKED,
    wxCommandEventHandler(MainFrame::OnSeparatorToggle));
    
  // -- About and Quit Routines --
  Connect(ID_ABOUT, wxEVT_COMMAND_TOOL_CLICKED,
      wxCommandEventHandler(MainFrame::OnAbout));
  Connect(ID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
      wxCommandEventHandler(MainFrame::OnQuit));
}

// -- Intialize UserList --
void MainFrame::InitUserPanel()
{
  UserSBSizer = new wxStaticBoxSizer(wxVERTICAL, UserPanel, wxT("IceCuBe Buddy List"));		
	
  UserList = new wxListCtrl( UserPanel, wxID_ANY,
	                         wxDefaultPosition, wxSize(-1,-1),
	                         wxLC_REPORT | wxLC_SINGLE_SEL  | wxLC_EDIT_LABELS);

  UserList->SetImageList(ImageList, wxIMAGE_LIST_SMALL);
//  UserList->SetColumnWidth(0,16);
//  UserList->SetColumnWidth(1,80);
//  UserList->SetColumnWidth(2,50);
//  UserList->SetColumnWidth(3,50);  
  
//  column.SetText(wxT(""));
  column.SetMask(wxLIST_MASK_IMAGE);
  column.SetImage(0);
	UserList->InsertColumn(0, column);
//	UserList->InsertColumn(1, wxT(""), wxLIST_FORMAT_LEFT, 16);

  column.SetText(_T("Nick"));
	column.SetImage(-1);
	UserList->InsertColumn(1, column);	
//	UserList->InsertColumn(1, wxT("Nick"), wxLIST_FORMAT_LEFT, 20);

	column.SetText(_T("IP"));
	column.SetImage(-1);
	UserList->InsertColumn(2, column);

	column.SetText(_T("Group"));
	column.SetImage(-1);
	UserList->InsertColumn(3, column);

	column.SetText(_T("Hostname"));
	column.SetImage(-1);
	UserList->InsertColumn(4, column);

	column.SetText(_T("Description"));
	column.SetImage(-1);
	UserList->InsertColumn(5, column);
	
//  test = UserList->SetItem(0, 0, wxT(""), 7 );  
  for( int i=0; i< 10; i++)
  {
  wxString buf = wxT("");
  long tmp = UserList->InsertItem(i, buf, i);
  UserList->SetItemData(tmp, 0);

  buf.Printf(_T("Rohit Yadav %d"), i);
  UserList->SetItem(tmp, 1, buf);

  buf.Printf(_T("10.8.11.20%d"), i);
  UserList->SetItem(tmp, 2, buf);
  
  buf.Printf(_T("CompSci"));
  UserList->SetItem(tmp, 3, buf);

  buf.Printf(_T("SnowFlake"));
  UserList->SetItem(tmp, 4, buf);
  
  buf.Printf(_T("Tstin IC Msg..."));
  UserList->SetItem(tmp, 5, buf);
  }
  
//  UserList->InsertItem(0, 7 );

  UserList->SetColumnWidth( 0, wxLIST_AUTOSIZE );
  UserList->SetColumnWidth( 1, wxLIST_AUTOSIZE );
  UserList->SetColumnWidth( 2, wxLIST_AUTOSIZE );
  UserList->SetColumnWidth( 3, wxLIST_AUTOSIZE );
  UserList->SetColumnWidth( 4, wxLIST_AUTOSIZE );
  UserList->SetColumnWidth( 5, wxLIST_AUTOSIZE );
      
  wxBoxSizer* SearchAndRefresh;
  SearchAndRefresh  = new wxBoxSizer( wxHORIZONTAL );
  
  // -- Search Button --
  Search = new wxSearchCtrl( UserPanel, -1, wxT("Search IceCuBe Buddy"), wxDefaultPosition, wxSize(-1, -1),  wxEXPAND | wxTE_PROCESS_ENTER | wxTE_NOHIDESEL ); 
  Search->ShowSearchButton(true);
  Search->ShowCancelButton(true);
  
  // -- Refresh Button --
  Refresh = new wxButton(UserPanel, -1, wxT("Refresh"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);

  SearchAndRefresh->Add( Search, 1, wxALL|wxEXPAND, 5 );
  SearchAndRefresh->Add( Refresh, 0, wxALL|wxEXPAND, 5 );
    
  UserSBSizer->Add( UserList, 2, wxALL|wxEXPAND, 0 );
  UserSBSizer->Add( SearchAndRefresh, 0, wxALL|wxEXPAND, 5 );
}

// -- Fill the Navigation NoteBook --
void MainFrame::InitNavigation()
{
  wxBoxSizer* TransferSizer;
  wxBoxSizer* WBSizer;
  wxBoxSizer* LogSizer;
  
  Navigation  = new wxNotebook( NavPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
  Navigation->AssignImageList(ImageList);
  
  LogSizer   = new wxBoxSizer( wxVERTICAL );
  
  WBPanel       = new wxPanel( Navigation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  TransferPanel = new wxPanel( Navigation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  LogPanel      = new wxPanel( Navigation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

	Log =  new wxTextCtrl(LogPanel, ID_LOG, _("Welcome to IceCuBe Server Log\n"), 
                           wxDefaultPosition, wxDefaultSize,
                           wxTE_MULTILINE | wxTE_READONLY);

	LogSizer->Add( Log, 1, wxEXPAND | wxALL, 5 );	
	LogPanel->SetSizer( LogSizer );
	LogPanel->Layout();
	LogSizer->Fit( LogPanel );

	Navigation->AddPage( WBPanel, wxT("WB"), true, 7 );
	Navigation->AddPage( TransferPanel, wxT("Transfers"), false, 8 );	
	Navigation->AddPage( LogPanel, wxT("Log"), false, 6 );
  navbar = true;
}

// -- Intialize GUI Body --
void MainFrame::InitBody()
{	
// Rohit Yadav: We use this GUI Tree; use it to 
// add more GUI functionality. If you make any change
// mark change by adding //<your-name> <notes> at the end.

// MainFrame(wxFrame)
// +--MainSizer
//	+--MainSplitter(Splitter Window)
//	   +--LeftPanel
//		    +--LeftSizer
//           +--HorizontalSplitter
//              +--NavPanel
//                 +--NavSizer
//		                +--Navigation(Notebook): Log, Transfer, WB
//				      +--UserPanel
//				         +--UserSizer
//					          +--UserList(Ctrl) //Jr. Harshat suggests: Hide/Show user list
//					          +--Search
//	   +--RightPanel
//		    +--RightSizer
//				   +--MsgTextBox
//				   +--InputTextBox   //Avinash Yadav suggested to use RichTextCtrl
// -- End of GUI Tree -- 
// Credits for GUI: Rohit Yadav with the help of Avinash Yadav and Jr. Harshat for 
//there valuable suggestions.

  wxBoxSizer* MainSizer;
  wxBoxSizer* LeftSizer;
  wxBoxSizer* RightSizer;
  wxBoxSizer* NavSizer;
  wxBoxSizer* UserSizer;

  MainSizer  = new wxBoxSizer( wxVERTICAL );
  LeftSizer  = new wxBoxSizer( wxVERTICAL );
	NavSizer   = new wxBoxSizer( wxVERTICAL );
  UserSizer  = new wxBoxSizer( wxVERTICAL );
  RightSizer = new wxBoxSizer( wxVERTICAL );

  // -- MainSplitter: LeftPanel + RightPanel --
  MainSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE|wxSP_NOBORDER );
  MainSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::MainSplitterOnIdle ), NULL, this );
 
  LeftPanel  = new wxPanel( MainSplitter, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
  RightPanel = new wxPanel( MainSplitter, wxID_ANY, wxDefaultPosition, wxSize( -1, -1 ), wxTAB_TRAVERSAL );

  // -- LeftPanel:: Horizontal Splitter --  
	HorizontalSplitter = new wxSplitterWindow( LeftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER );
	HorizontalSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::HorizontalSplitterOnIdle ), NULL, this );

	NavPanel  = new wxPanel( HorizontalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  UserPanel = new wxPanel( HorizontalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
  
  // -- Navigation:: WB, Transfer, Log --
  InitNavigation();
	NavSizer->Add( Navigation, 1, wxEXPAND | wxALL, 5 );
	
	NavPanel->SetSizer( NavSizer );
	NavPanel->Layout();
	NavSizer->Fit( NavPanel );
	
  // -- UserPanel --
  InitUserPanel();
  UserSizer->Add(UserSBSizer, 1, wxALL|wxEXPAND, 0 );

  UserPanel->SetSizer( UserSizer );
  UserPanel->Layout();
  UserSizer->Fit( UserPanel );

	LeftSizer->Add( HorizontalSplitter, 1, wxALL|wxEXPAND, 5 );
	
	LeftPanel->SetSizer( LeftSizer );
	LeftPanel->Layout();
	LeftSizer->Fit( LeftPanel );	

  // -- Rightpanel:: MsgPanel --
  MsgSBSizer  = new wxStaticBoxSizer(wxVERTICAL, RightPanel, wxT("IceCuBe Common Room"));

  // -- MsgPanel --
  MsgTextBox   = new wxRichTextCtrl( RightPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
  InputTextBox = new wxTextCtrl( RightPanel, ID_TEXT_INPUT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_CHARWRAP|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE|wxTE_BESTWRAP );

//  InputTextBox->SetMaxSize( wxSize( -1,40 ) );
  InputTextBox->SetMaxLength(1024*256);
  InputTextBox->Connect(ID_STATUS, wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnTextEnter));

  MsgSBSizer->Add( MsgTextBox,   2, wxEXPAND | wxALL, 5 );
  MsgSBSizer->Add( InputTextBox, 0, wxEXPAND | wxALL | wxALIGN_BOTTOM, 5 );

  RightSizer->Add(MsgSBSizer, 1, wxEXPAND | wxALL, 5 );
  
  RightPanel->SetSizer( RightSizer );
	RightPanel->Layout();
	RightSizer->Fit( RightPanel );

  // -- Add panels to the splitted windows --
  HorizontalSplitter->SplitHorizontally( NavPanel, UserPanel, 200 );
  HorizontalSplitter->Unsplit(NavPanel);
  MainSplitter->SplitVertically( LeftPanel, RightPanel, 380 );

  MainSplitter->SetMinimumPaneSize( 250 );
  HorizontalSplitter->SetMinimumPaneSize( 250 );  
  
  sw_stat = true;

  MainSizer->Add( MainSplitter, 1, wxEXPAND, 5 );
  this->SetSizer( MainSizer );
  this->Layout();
}

wxColour MainFrame::GetUserNickColour()
{
  UserNickColour.Set(wxT("#0000FF"));
  return UserNickColour;	
}

wxString MainFrame::GetUserNick()
{
  UserNickName = wxT("Rohit: ");
  return UserNickName;	
}

/*
:(:-D:-/:-(:-)B-);-):Zz
cry :(   //
happy :-D //
hmm :-/ //
sad :-(  //
smile :-) //
cool B-)  //
wink ;-) 
yawn :Zz
*/


#define Smiley(first,name,j) \
if( (s.GetChar(j+2) == first) ) \
{ MsgTextBox->WriteImage(GetPNG(name), wxBITMAP_TYPE_PNG); j += 3; } \

// -- Function Jointly written by Abhishek Kumar and Rohit Yadav --
void MainFrame::PrintText(const wxString s)
{
//  const wxChar *input = s.c_str();
  wxString temp;
  int i;
  
  if(s == wxT("I Love IceCuBe"))
  {
    MsgTextBox->AppendText(wxT("I Love Rohit Yadav!"));
    MsgTextBox->Newline();
    MsgTextBox->WriteImage(GetPNG(tux), wxBITMAP_TYPE_PNG); return;
  }
  
  int length = s.Len();    
  
  for( i = 0; i < length; )
  { // -- Get Smileys :-) --
    if( (i+3) <= length )
    {
       if( s.GetChar(i) == ':' )
        {
          //if( (i+3) <= length )
          {
            if( ( s.GetChar(i+1) == '-' ) || ( s.GetChar(i+1) == 'Z' ) || ( s.GetChar(i+1) == '(' ) )
            {
              if(s.GetChar(i+1) == '(')
              {
                MsgTextBox->WriteImage(GetPNG(cry), wxBITMAP_TYPE_PNG);
                i += 2;
              }
              
              if( s.GetChar(i+1) == '-' )
               {
                  Smiley( 'D', happy, i )
                  Smiley( '/', hmm, i )
                  Smiley( '(', sad, i )
                  Smiley( ')', smile, i)
               }
               
              if( s.GetChar(i+1) == 'Z' )
               {
                 Smiley('z', yawn, i)
               }
            }
            else
            {
              temp.Clear();
              temp.Printf(_("%c"), s.GetChar(i));
              MsgTextBox->AppendText(temp);
              i++;
            }
          }
        }
       else 
       if( ( s.GetChar(i) == 'B' ) && ( s.GetChar(i+1) == '-' ) )
       {
         Smiley( ')', cool, i)
       }
       else
       if( ( s.GetChar(i) == ';' ) && ( s.GetChar(i+1) == '-' ) )
       {
         Smiley( ')', wink, i)
       }
       else
          {
            temp.Clear();
            temp.Printf(_("%c"), s.GetChar(i));
            MsgTextBox->AppendText(temp);
            i++;
          }
    }
    else
    {
      if( (s.GetChar(i) == ':') && (s.GetChar(i+1) == '(') )
      {
        MsgTextBox->WriteImage(GetPNG(cry), wxBITMAP_TYPE_PNG);
        i += 2;
      }
      else{
      temp.Clear();
      temp.Printf(_("%c"), s.GetChar(i));
      MsgTextBox->AppendText(temp);
      i++;}
    }
  }

}

void MainFrame::OnTextEnter( wxCommandEvent& event )
{
  if( InputTextBox->GetValue() != wxT("") ){
  SendText();
  MsgTextBox->BeginTextColour(GetUserNickColour());
  MsgTextBox->AppendText(GetUserNick());
  MsgTextBox->BeginTextColour(*wxBLACK);

  PrintText(InputTextBox->GetValue());
//  MsgTextBox->AppendText(InputTextBox->GetValue());
  MsgTextBox->Newline();
  MsgTextBox->ShowPosition(MsgTextBox->GetCaretPosition() + 1 );
  InputTextBox->Clear();}
}

splitlength MainFrame::GetSplitRatio(bool compartment)
{
// Rohit Yadav: I have divided the window width into 3
// compartments into ratio:
// +----------+----------+------------+
// |  navbar  |  msgbox  |  userlist  | 
// +----------+----------+------------+ 
//      5     :    6     :     4
// Compartment 0 length = navbar
//             1 length = navar + msgbox

  int width = this->GetSize().x;
  
//  printf("Width = %d\n", width);
//  printf("navWidth = %d\n", width * 5 / 15 );
//  printf("msgWidth = %d\n", width * 5 / 12);  
//  printf("userWidth = %d\n\n", width * 3 / 12);
  navbarLength = static_cast<int>(width * 2 / 5);
  msgboxLength = static_cast<int>(width * 3 / 4);
  
  if( navbarLength > 400 )           //Thresholds
    navbarLength = 400;
    
  if( (width - msgboxLength) > 280 ) //Thresholds
    msgboxLength = width - 280;

  if( (width - msgboxLength) < 200 ) //Thresholds
    msgboxLength = width - 200;    

  if(compartment == false) return navbarLength;
  else                     return msgboxLength;
}

//void MainFrame::OnSize(wxSizeEvent& event)
//{
//  if(sw_stat == true){
  //MainSplitter->SetSashPosition( GetSplitRatio(false), true );
  //RightSplitter->SetSashPosition( GetSplitRatio(true), true );}
//}

#define WINDOW_MIN_SIZE wxSize( 480 , 420 )
#define WINDOW_MAX_SIZE wxSize( -1 , -1 )

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
  //Mac OS Only:: Adds Metal-Carbon Look
  this->SetExtraStyle( wxFRAME_EX_METAL );
  //this->SetTransparent(250);
  this->SetIcon( wxIcon(icon_xpm) );

  this->SetSizeHints( WINDOW_MIN_SIZE, WINDOW_MAX_SIZE );
  
  //Make the ImageList
  ImageList = new wxImageList( 32, 32, true, 1);
  
	ImageList->Add(GetPNG(admin),wxNullBitmap);          //0
	ImageList->Add(GetPNG(attach),wxNullBitmap);         //1
	ImageList->Add(GetPNG(availablesmall),wxNullBitmap); //2
	ImageList->Add(GetPNG(busysmall),wxNullBitmap);      //3
	ImageList->Add(GetPNG(customsmall),wxNullBitmap);    //4
	ImageList->Add(GetPNG(ipmsg),wxNullBitmap);          //5
	ImageList->Add(GetPNG(public),wxNullBitmap);         //6
  ImageList->Add(GetPNG(user),wxNullBitmap);           //7
  ImageList->Add(GetPNG(close),wxNullBitmap);          //8
  ImageList->Add(GetPNG(open),wxNullBitmap);           //9
  			
  status   = true;    //Status: Available
  userlist = true;    //UserList Visibility
  sw_stat  = false;   //splitwindow_status
  
  InitStatusBar();    //Initialize StatusBar!
  InitFileMenu();     //Intialize File Menu
  InitToolBar();      //Initialize Carbon ToolBar
  InitBody();         //Initialize CommandCenter
  	
  this->Centre( wxBOTH );
  
  // Create the address - defaults to localhost:0 initially
  wxIPV4address addr;
  addr.Service(9090);

  // Create the socket
  iceServer = new wxSocketServer(addr);
  
  // We use Ok() here to see if the server is really listening
  if (! iceServer->Ok())
  {
    Log->AppendText(_("Could not listen at the specified port !\n\n"));
    return;
  }
  else
  {
    Log->AppendText(_("Server listening at port 9090.\n\n"));
  }
  
  // Setup the event handler and subscribe to connection events
  iceServer->SetEventHandler(*this, SERVER_ID);
  iceServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
  iceServer->Notify(true);

  busy = false;
  totalUsers = 0;
  
  // Create the socket for client
  cubeClient = new wxSocketClient();

  // Setup the event handler and subscribe to most events
  cubeClient->SetEventHandler(*this, CLIENT_ID);
  cubeClient->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
  cubeClient->Notify(true);
  UpdateStatusBar();
}

void MainFrame::SendText()
{
  const wxChar *msg1;
  size_t len;

  // Disable socket menu entries (exception: Close Session)
  busy = true;
  UpdateStatusBar();

  Log->AppendText(_("\n=== Sending Msg ===\n"));

  // Tell the server which test we are running
  unsigned char c = 0xCE;
  cubeClient->Write(&c, 1);

  // Here we use ReadMsg and WriteMsg to send messages with
  // a header with size information. Also, the reception is
  // event triggered, so we test input events as well.
  //
  // We need to set no flags here (ReadMsg and WriteMsg are
  // not affected by flags)

  cubeClient->SetFlags(wxSOCKET_WAITALL);

  wxString s = InputTextBox->GetValue();

  msg1 = s.c_str();
  len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);

  Log->AppendText(_("Sending the string with WriteMsg ..."));
  cubeClient->WriteMsg(msg1, len);
  Log->AppendText(cubeClient->Error() ? _("Sending Failed !\n") : _("Msg Sent\n"));
  Log->AppendText(_("Waiting for an event (timeout = 2 sec)\n"));

  // Wait until data available (will also return if the connection is lost)

  busy = false;
  UpdateStatusBar();
}

void MainFrame::OnOpenConnection(wxCommandEvent& WXUNUSED(event))
{
  wxIPV4address addr;

  // Ask user for server address
  wxString hostname = wxGetTextFromUser(
    _("Enter the address of the IceCuBe server:"),
    _("Connect to IceCuBe Server @:"),
    _("localhost"));

  if(hostname == wxT(""))
    hostname = wxT("localhost");
  addr.Hostname(hostname);
  addr.Service(9090);

  Log->AppendText(_("\nTrying to connect (timeout = 10 sec) ...\n"));
  cubeClient->Connect(addr, false);
  cubeClient->WaitOnConnect(10);

  if (cubeClient->IsConnected())
    Log->AppendText(_("Connection established\n"));
  else
  {
    cubeClient->Close();
    Log->AppendText(_("Unable to connect\n"));
    wxMessageBox(_("Can't connect to the specified host"), _("Alert !"));
    wxBell();
  }
  UpdateStatusBar();
}


void MainFrame::OnCloseConnection(wxCommandEvent& WXUNUSED(event))
{
  cubeClient->Close();
  UpdateStatusBar();
}

void MainFrame::OnClientEvent(wxSocketEvent& event)
{
  wxString s = _("ClientEvent: ");

  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT      : s.Append(_("wxSOCKET_INPUT\n")); break;
    case wxSOCKET_LOST       : s.Append(_("wxSOCKET_LOST\n")); break;
    case wxSOCKET_CONNECTION : s.Append(_("wxSOCKET_CONNECTION\n")); break;
    default                  : s.Append(_("Unexpected event !\n")); break;
  }

  Log->AppendText(s);
  UpdateStatusBar();
}

void MainFrame::Test2(wxSocketBase *sock)
{
#define MAX_MSG_SIZE 10000

  wxString s;
  wxChar *buf = new wxChar[MAX_MSG_SIZE];
  wxUint32 len;

  Log->AppendText(_("Msg Test Started\n"));

  // We don't need to set flags because ReadMsg and WriteMsg
  // are not affected by them anyway.

  // Read the message
  len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();
  s.Printf(_("%s\n"), buf);
  
  MsgTextBox->BeginTextColour(*wxRED);
  MsgTextBox->AppendText(_("Localhost: "));
  MsgTextBox->BeginTextColour(*wxBLACK);
  PrintText(s);
//  MsgTextBox->AppendText(s);
  MsgTextBox->Newline();
  MsgTextBox->ShowPosition(MsgTextBox->GetCaretPosition() + 1 );

  Log->AppendText(s);

  delete[] buf;

  Log->AppendText(_("Msg sent\n\n"));

#undef MAX_MSG_SIZE
}


void MainFrame::OnServerEvent(wxSocketEvent& event)
{
  wxString s = _("OnServerEvent: ");
  wxSocketBase *sock;

  switch(event.GetSocketEvent())
  {
    case wxSOCKET_CONNECTION : s.Append(_("Got SOCKET_CONNECTION\n")); break;
    default                  : s.Append(_("Unexpected event !\n")); break;
  }

  Log->AppendText(s);

  // Accept new connection if there is one in the pending
  // connections queue, else exit. We use Accept(false) for
  // non-blocking accept (although if we got here, there
  // should ALWAYS be a pending connection).

  sock = iceServer->Accept(false);

  if (sock)
  {
    Log->AppendText(_("New client connection accepted\n\n"));
  }
  else
  {
    Log->AppendText(_("Error: couldn't accept a new connection\n\n"));
    return;
  }

  sock->SetEventHandler(*this, SOCKET_ID);
  sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
  sock->Notify(true);

  totalUsers++;
  UpdateStatusBar();
}

void MainFrame::OnSocketEvent(wxSocketEvent& event)
{
  wxString s = _("Socket Event: ");
  wxSocketBase *sock = event.GetSocket();

  // First, print a message
  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT : s.Append(_("New IceCuBe Connection Received\n")); break;
    case wxSOCKET_LOST  : s.Append(_("New IceCuBe Connection Lost\n")); break;
    default             : s.Append(_("Unexpected event!\n")); break;
  }

  Log->AppendText(s);

  // Now we process the event
  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT:
    {
      // We disable input events, so that the test doesn't trigger
      // wxSocketEvent again.
      sock->SetNotify(wxSOCKET_LOST_FLAG);

      // Which test are we going to run?
      unsigned char c;
      sock->Read(&c, 1);
      wxIPV4address addr;
      
      sock->GetPeer(addr);
      Log->AppendText(wxT("IP: "));
      Log->AppendText(addr.IPAddress());
      Log->AppendText(_("\n"));
      switch (c)
      {
        case '&' :
        case 0xCE: Test2(sock); break;
        default:
          Log->AppendText(_("Intrusion Logged\n\n"));
      }
      // Enable input events again.
      sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
      break;
    }
    case wxSOCKET_LOST:
    {
      totalUsers--;

      // Destroy() should be used instead of delete wherever possible,
      // due to the fact that wxSocket uses 'delayed events' (see the
      // documentation for wxPostEvent) and we don't want an event to
      // arrive to the event handler (the frame, here) after the socket
      // has been deleted. Also, we might be doing some other thing with
      // the socket at the same time; for example, we might be in the
      // middle of a test or something. Destroy() takes care of all
      // this for us.

      Log->AppendText(_("Deleting socket.\n\n"));
      sock->Destroy();
      break;
    }
    default: ;
  }

  UpdateStatusBar();
}


void MainFrame::UpdateStatusBar()
{
  wxString s;
  s.Printf(_("Total Users: %d"), totalUsers);
  StatusBar->SetStatusText(s, 4);

  if (!cubeClient->IsConnected())
  {
    s.Printf(_("Not connected 2 server"));
  }
  else
  {
    wxIPV4address addr;

    cubeClient->GetPeer(addr);
    s.Printf(_("%s : %d"), (addr.Hostname()).c_str(), addr.Service());
  }
  Log->AppendText(s);
}

MainFrame::~MainFrame()
{
  //delete
   iceServer->Destroy();
//  delete 
//   cubeClient->Destroy();
}
