#include "CAApp.h"
#include "MainFrameImpl.h"

wxIMPLEMENT_APP(CAApp);

bool CAApp::OnInit()
{
	wxInitAllImageHandlers();
	MainFrame* frame = new MainFrameImpl();
	SetTopWindow(frame);
	frame->Show();

	return true;
}

int CAApp::OnExit()
{
	return 0;
}