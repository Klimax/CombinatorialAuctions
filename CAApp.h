#pragma once

#include <wx/wx.h>

class CAApp : public wxApp
{
public:
	bool OnInit();
	int OnExit();
};

wxDECLARE_APP(CAApp);
