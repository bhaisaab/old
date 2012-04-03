///////////////////////////////////////////////////////////////////////////
// splash.cpp
// IceCuBe
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include "splash.h"
#include "png.h"

#include "png/splash_png.h"
#include "png/mask_png.h"

#include <wx/wx.h>


#define ID_TIMER 2000

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CarbonSplash, wxFrame)
    EVT_TIMER( ID_TIMER, CarbonSplash::OnTimer)
#ifdef __WXGTK__
    EVT_WINDOW_CREATE(CarbonSplash::OnWindowCreate)
#endif
END_EVENT_TABLE()


// frame constructor
CarbonSplash::CarbonSplash() : wxFrame((wxFrame *)NULL, wxID_ANY, wxEmptyString,
                  wxDefaultPosition, wxSize(-1, -1),
                  wxFRAME_SHAPED | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP )
{
  splash = GetPNG(splash);

  mask   = GetPNG(mask);

#ifndef __WXGTK__
  // On wxGTK we can't do this yet because the window hasn't been created
  // yet so we wait until the EVT_WINDOW_CREATE event happens.  On wxMSW and
  // wxMac the window has been created at this point so we go ahead and set
  // the shape now.
  SetWindowShape();
#endif

  wxStaticBitmap* m_bitmap = new wxStaticBitmap( this, wxID_ANY, splash, wxDefaultPosition, wxDefaultSize, 0 );
  m_bitmap->SetBackgroundColour( wxColour( 0, 0, 0 ) );
  

  this->SetSize( wxSize(splash.GetWidth(), splash.GetHeight()) );
  this->SetToolTip(wxT("IceCuBe Messenger\n© Rohit Yadav"));
  this->SetTransparent(240);
  this->Layout();
  this->Centre( wxBOTH );
 
  timer = new wxTimer(this, ID_TIMER);
  timer->Start(3000, true);

  Connect(ID_TIMER, wxTimerEventHandler(CarbonSplash::OnTimer) );
  
}

void CarbonSplash::OnTimer(wxTimerEvent& WXUNUSED(event))
{
    timer->Stop();
	Close(true);
}

CarbonSplash::~CarbonSplash()
{
	timer->Stop();
}

void CarbonSplash::SetWindowShape()
{
    wxRegion region( mask );
    SetShape(region);
}

void CarbonSplash::OnWindowCreate(wxWindowCreateEvent& WXUNUSED(evt))
{
    SetWindowShape();
}
