///////////////////////////////////////////////////////////////////////////
// statusbar.h
// IceCuBe Messenger
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include <wx/statusbr.h>
#include <wx/statbmp.h>
#include <wx/bmpbuttn.h>

///////////////////////////////////////////////////////////////////////////////
/// CarbonBar: StatusBar Class Declaration
///////////////////////////////////////////////////////////////////////////////
class CarbonBar : public wxStatusBar
{
  public:
    CarbonBar(wxWindow *parent, wxWindowID id);
    virtual ~CarbonBar();
    void OnSize(wxSizeEvent& event);
    void ToggleStatus();

  private:
    //enums
    enum
    {
        Field_Text,
        Field_StatusBitmap,
        Field_Status,
        Field_UserBitmap,
        Field_Users,
        Field_Space,
        Field_Max
    };

    wxStaticBitmap *status;
    wxStaticBitmap *user;

	bool CurrentStatus;

    DECLARE_EVENT_TABLE()	
};
