///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
private:

protected:
	wxPanel* m_panel3;
	wxGrid* m_PlayerOffers;
	wxNotebook* m_ItemsNotebook;
	wxPanel* m_panel8;
	wxGrid* m_Items;
	wxNotebook* m_WinnersNotebook;
	wxPanel* m_panel7;
	wxGrid* m_Winners;
	wxPanel* m_panel4;
	wxStaticText* m_staticText8;
	wxStaticText* m_staticText2;
	wxSpinCtrl* m_nPlayers;
	wxStaticText* m_staticText3;
	wxSpinCtrl* m_nItems;
	wxStaticText* m_staticText4;
	wxSpinCtrl* m_MaxComplements;
	wxStaticText* m_staticText5;
	wxSpinCtrl* m_MaxItemsPerPlayer;
	wxStaticText* m_staticText6;
	wxSpinCtrl* m_Seed;
	wxStaticText* m_staticText7;
	wxSpinCtrl* m_MaxPrice;
	wxPanel* m_panel2;
	wxStaticText* m_staticText1;
	wxListBox* m_Methods;
	wxButton* m_ComputeButton;
	wxButton* m_ResetButton;
	wxButton* m_RandomButton;
	wxPanel* m_panel6;
	wxGrid* m_grid4;

	// Virtual event handlers, overide them in your derived class
	virtual void m_nPlayersOnSpinCtrl(wxSpinEvent& event) { event.Skip(); }
	virtual void m_ComputeButtonClick(wxCommandEvent& event) { event.Skip(); }
	virtual void m_ResetButtonClick(wxCommandEvent& event) { event.Skip(); }
	virtual void m_RandomButtonClick(wxCommandEvent& event) { event.Skip(); }


public:

	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1070, 677), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainFrame();

};

