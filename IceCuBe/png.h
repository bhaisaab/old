///////////////////////////////////////////////////////////////////////////
// png.h
// IceCuBe
//
// © Rohit Yadav, 2008-2009.
// License: GNU GPL v2 or later
// ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////

#include <wx/mstream.h>
#include <wx/bitmap.h>

#define GetPNG(name) _GetPNG(name ## _png, sizeof(name ## _png))

inline wxBitmap _GetPNG(const unsigned char *data, int length) 
{
   wxMemoryInputStream is(data, length);
   return wxBitmap(wxImage(is, wxBITMAP_TYPE_PNG, -1), -1);
}
