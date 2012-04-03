///////////////////////////////////////////////////////////////////////////////
// statusbar.cpp
// IceCuBe Messenger
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>
#include <wx/statusbr.h>
#include <wx/statbmp.h>
#include <wx/bmpbuttn.h>

#include "statusbar.h"

#include "png.h"
#include "png/iconsmall.h"

///////////////////////////////////////////////////////////////////////////////
/// Enumerations
///////////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(CarbonBar, wxStatusBar)
    EVT_SIZE(CarbonBar::OnSize)
END_EVENT_TABLE()

#define BITMAP_SIZE_X 24
#define BITMAP_SIZE_Y 16

#define THRESHOLD_X   2
#define THRESHOLD_Y   2

///////////////////////////////////////////////////////////////////////////////
/// CarbonBar Class
///////////////////////////////////////////////////////////////////////////////
CarbonBar::CarbonBar(wxWindow *parent, wxWindowID id)
           : wxStatusBar(parent, id, wxSB_NORMAL | wxFULL_REPAINT_ON_RESIZE)
{
  CurrentStatus = false;
  static const int widths[Field_Max] = { -1, BITMAP_SIZE_X, 180, BITMAP_SIZE_X, 100, 16 };

  SetFieldsCount(Field_Max);
  SetStatusWidths(Field_Max, widths);
  SetStatusText(_T("Welcome to IceCuBe!!!"), Field_Text);  
  SetStatusText(_T("Total Users: 0"), Field_Users);  

  status = new wxStaticBitmap(this, wxID_ANY, GetPNG(availablesmall), wxDefaultPosition, wxDefaultSize);
  user   = new wxStaticBitmap(this, wxID_ANY, GetPNG(public), wxDefaultPosition, wxDefaultSize);

  ToggleStatus();

  SetMinHeight(BITMAP_SIZE_Y);
}

CarbonBar::~CarbonBar()
{

}

void CarbonBar::OnSize(wxSizeEvent& event)
{
  wxRect rect;
  wxSize size;

  GetFieldRect(Field_StatusBitmap, rect);
  size = status->GetSize();
  status->Move(rect.x + (rect.width - size.x) / 2,
               rect.y + (rect.height - size.y) / 2 + THRESHOLD_Y);
		  
  GetFieldRect(Field_UserBitmap, rect);
  size = user->GetSize();
  user->Move(rect.x + (rect.width - size.x) / 2,
		       rect.y + (rect.height - size.y) / 2 + THRESHOLD_Y);

  event.Skip();
}

void CarbonBar::ToggleStatus()
{
  if(CurrentStatus == true)
  {
    status->SetBitmap(GetPNG(busysmall));
    SetStatusText(wxT("Status: Busy"), Field_Status);
    CurrentStatus = false;
  }  
  else
  {
    status->SetBitmap(GetPNG(availablesmall));
    SetStatusText(wxT("Status: Available"), Field_Status);
	CurrentStatus = true;	
  }
}
