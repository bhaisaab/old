///////////////////////////////////////////////////////////////////////////
// splash.h
// IceCuBe
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include "wx/image.h"
#include "wx/timer.h"
#include "wx/wx.h"

#ifndef SPLASH_H
#define SPLASH_H

class CarbonSplash : public wxFrame
{
  public:
	CarbonSplash();
    ~CarbonSplash();
    void SetWindowShape();

    void OnWindowCreate(wxWindowCreateEvent& evt);
	void OnTimer(wxTimerEvent& event);
	
  private:
	wxBitmap splash;
	wxBitmap mask;

	wxTimer* timer;
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

#endif //SPLASH_H
