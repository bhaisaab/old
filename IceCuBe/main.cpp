///////////////////////////////////////////////////////////////////////////
// main.cpp
// IceCuBe Messenger
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "mainframe.h"

#include "wx/image.h"
#include "wx/splash.h"
#include "wx/mediactrl.h"
#include "wx/dcclient.h"
    #include "wx/app.h"
    #include "wx/log.h"
    #include "wx/frame.h"
    #include "wx/panel.h"
    #include "wx/stattext.h"
    #include "wx/menu.h"
    #include "wx/layout.h"
    #include "wx/msgdlg.h"

IMPLEMENT_APP(IceCuBe)

bool IceCuBe::OnInit()
{
  wxInitAllImageHandlers();
  wxImage::AddHandler(new wxPNGHandler);
  
  SplashScreen = new CarbonSplash();
  SplashScreen->Show(true);

  CommandCenter = new MainFrame( NULL, ID_COMMAND_CENTER , wxT("IceCuBe Command Center"), wxDefaultPosition, wxSize( 540, 320 ), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
  CommandCenter->Show(true);

  return true;
}
