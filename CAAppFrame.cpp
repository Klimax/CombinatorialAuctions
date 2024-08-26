///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CAAppFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer(2, 3, 0, 0);

	m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer(0, 0, 0, 0);

	m_PlayerOffers = new wxGrid(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_PlayerOffers->CreateGrid(10, 2);
	m_PlayerOffers->EnableEditing(true);
	m_PlayerOffers->EnableGridLines(true);
	m_PlayerOffers->EnableDragGridSize(true);
	m_PlayerOffers->SetMargins(0, 0);

	// Columns
	m_PlayerOffers->SetColSize(0, 80);
	m_PlayerOffers->SetColSize(1, 114);
	m_PlayerOffers->EnableDragColMove(false);
	m_PlayerOffers->EnableDragColSize(true);
	m_PlayerOffers->SetColLabelSize(30);
	m_PlayerOffers->SetColLabelValue(0, wxT("Offers"));
	m_PlayerOffers->SetColLabelValue(1, wxT("Complements"));
	m_PlayerOffers->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	m_PlayerOffers->EnableDragRowSize(true);
	m_PlayerOffers->SetRowLabelSize(80);
	m_PlayerOffers->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	m_PlayerOffers->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	gSizer2->Add(m_PlayerOffers, 0, wxALL | wxEXPAND, 5);


	m_panel3->SetSizer(gSizer2);
	m_panel3->Layout();
	gSizer2->Fit(m_panel3);
	gSizer1->Add(m_panel3, 1, wxEXPAND | wxALL, 5);

	m_ItemsNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	m_panel8 = new wxPanel(m_ItemsNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer(0, 0, 0, 0);

	m_Items = new wxGrid(m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_Items->CreateGrid(0, 2);
	m_Items->EnableEditing(false);
	m_Items->EnableGridLines(true);
	m_Items->EnableDragGridSize(true);
	m_Items->SetMargins(0, 0);

	// Columns
	m_Items->EnableDragColMove(false);
	m_Items->EnableDragColSize(true);
	m_Items->SetColLabelSize(30);
	m_Items->SetColLabelValue(0, wxT("Buyer"));
	m_Items->SetColLabelValue(1, wxT("Value"));
	m_Items->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	m_Items->EnableDragRowSize(true);
	m_Items->SetRowLabelSize(80);
	m_Items->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	m_Items->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	gSizer4->Add(m_Items, 0, wxALL | wxEXPAND, 5);


	m_panel8->SetSizer(gSizer4);
	m_panel8->Layout();
	gSizer4->Fit(m_panel8);
	m_ItemsNotebook->AddPage(m_panel8, wxT("Result"), false);

	gSizer1->Add(m_ItemsNotebook, 1, wxEXPAND | wxALL, 5);

	m_WinnersNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	m_panel7 = new wxPanel(m_WinnersNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer(0, 0, 0, 0);
	fgSizer3->SetFlexibleDirection(wxBOTH);
	fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	m_Winners = new wxGrid(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_Winners->CreateGrid(10, 2);
	m_Winners->EnableEditing(false);
	m_Winners->EnableGridLines(true);
	m_Winners->EnableDragGridSize(true);
	m_Winners->SetMargins(0, 0);

	// Columns
	m_Winners->EnableDragColMove(false);
	m_Winners->EnableDragColSize(true);
	m_Winners->SetColLabelSize(30);
	m_Winners->SetColLabelValue(0, wxT("Bid"));
	m_Winners->SetColLabelValue(1, wxT("Value"));
	m_Winners->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	m_Winners->EnableDragRowSize(true);
	m_Winners->SetRowLabelSize(80);
	m_Winners->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	m_Winners->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	fgSizer3->Add(m_Winners, 0, wxALL | wxEXPAND, 5);


	m_panel7->SetSizer(fgSizer3);
	m_panel7->Layout();
	fgSizer3->Fit(m_panel7);
	m_WinnersNotebook->AddPage(m_panel7, wxT("Result"), false);

	gSizer1->Add(m_WinnersNotebook, 1, wxEXPAND | wxALL, 5);

	m_panel4 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	m_staticText8 = new wxStaticText(m_panel4, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText8->Wrap(-1);
	fgSizer1->Add(m_staticText8, 0, wxALL, 5);


	fgSizer1->Add(0, 0, 1, wxEXPAND, 5);

	m_staticText2 = new wxStaticText(m_panel4, wxID_ANY, wxT("Number of players"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	fgSizer1->Add(m_staticText2, 0, wxALL, 5);

	m_nPlayers = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 10);
	fgSizer1->Add(m_nPlayers, 0, wxALL | wxEXPAND, 5);

	m_staticText3 = new wxStaticText(m_panel4, wxID_ANY, wxT("Number of items (only for random gen)"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	fgSizer1->Add(m_staticText3, 0, wxALL, 5);

	m_nItems = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 5);
	fgSizer1->Add(m_nItems, 0, wxALL | wxEXPAND, 5);

	m_staticText4 = new wxStaticText(m_panel4, wxID_ANY, wxT("Maximum of complements"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	fgSizer1->Add(m_staticText4, 0, wxALL, 5);

	m_MaxComplements = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 5);
	fgSizer1->Add(m_MaxComplements, 0, wxALL | wxEXPAND, 5);

	m_staticText5 = new wxStaticText(m_panel4, wxID_ANY, wxT("Max items per player"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	fgSizer1->Add(m_staticText5, 0, wxALL, 5);

	m_MaxItemsPerPlayer = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 5);
	fgSizer1->Add(m_MaxItemsPerPlayer, 0, wxALL | wxEXPAND, 5);

	m_staticText6 = new wxStaticText(m_panel4, wxID_ANY, wxT("Seed"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	fgSizer1->Add(m_staticText6, 0, wxALL, 5);

	m_Seed = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -214748364, 214748364, 0);
	fgSizer1->Add(m_Seed, 0, wxALL | wxEXPAND, 5);

	m_staticText7 = new wxStaticText(m_panel4, wxID_ANY, wxT("Max price"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText7->Wrap(-1);
	fgSizer1->Add(m_staticText7, 0, wxALL, 5);

	m_MaxPrice = new wxSpinCtrl(m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999999, 666);
	fgSizer1->Add(m_MaxPrice, 0, wxALL | wxEXPAND, 5);


	m_panel4->SetSizer(fgSizer1);
	m_panel4->Layout();
	fgSizer1->Fit(m_panel4);
	gSizer1->Add(m_panel4, 1, wxEXPAND | wxALL, 5);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	m_staticText1 = new wxStaticText(m_panel2, wxID_ANY, wxT("Solver"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	fgSizer2->Add(m_staticText1, 0, wxALL, 5);

	m_Methods = new wxListBox(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED | wxLB_NEEDED_SB);
	m_Methods->Append(wxT("Greedy - value-only"));
	m_Methods->Append(wxT("Greedy - value and complements"));
	m_Methods->Append(wxT("Greedy - Normalized"));
	m_Methods->Append(wxT("Greedy - VC normalized"));
	m_Methods->Append(wxT("Greedy - LOS"));
	m_Methods->Append(wxT("Greedy - VC LOS"));
	m_Methods->Append(wxT("LP - Simplex"));
	m_Methods->Append(wxT("LP - Simplex - alt rounding"));
	m_Methods->Append(wxT("LP - Interior point"));
	fgSizer2->Add(m_Methods, 0, wxALL | wxEXPAND, 5);
	m_Methods->SetSelection(0);

	m_ComputeButton = new wxButton(m_panel2, wxID_ANY, wxT("Compute"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer2->Add(m_ComputeButton, 0, wxALL, 5);

	m_ResetButton = new wxButton(m_panel2, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer2->Add(m_ResetButton, 0, wxALL, 5);

	m_RandomButton = new wxButton(m_panel2, wxID_ANY, wxT("Random"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer2->Add(m_RandomButton, 0, wxALL, 5);

	m_panel2->SetSizer(fgSizer2);
	m_panel2->Layout();
	fgSizer2->Fit(m_panel2);
	gSizer1->Add(m_panel2, 1, wxEXPAND | wxALL, 5);

	m_panel6 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxGridSizer* gSizer8;
	gSizer8 = new wxGridSizer(0, 0, 0, 0);

	m_grid4 = new wxGrid(m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_grid4->CreateGrid(10, 9);
	m_grid4->EnableEditing(true);
	m_grid4->EnableGridLines(true);
	m_grid4->EnableDragGridSize(false);
	m_grid4->SetMargins(0, 0);

	// Columns
	m_grid4->EnableDragColMove(false);
	m_grid4->EnableDragColSize(true);
	m_grid4->SetColLabelSize(30);
	m_grid4->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	m_grid4->EnableDragRowSize(true);
	m_grid4->SetRowLabelSize(80);
	m_grid4->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	m_grid4->SetRowLabelValue(0, "Max value");
	m_grid4->SetRowLabelValue(1, "Max complements");
	m_grid4->SetRowLabelValue(2, "Winning bids");
	m_grid4->SetRowLabelValue(3, "Winning complements");
	m_grid4->SetRowLabelValue(4, "Winning offers");
	m_grid4->SetRowLabelValue(5, "Delta from bids");
	m_grid4->SetRowLabelValue(6, "Delta from complements");
	m_grid4->SetRowLabelValue(7, "Delta from total");
	m_grid4->SetRowLabelValue(8, "No of winners");
	m_grid4->SetRowLabelValue(9, "No of winning complements");

	// Label Appearance

	// Cell Defaults
	m_grid4->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	gSizer8->Add(m_grid4, 0, wxALL | wxEXPAND, 5);


	m_panel6->SetSizer(gSizer8);
	m_panel6->Layout();
	gSizer8->Fit(m_panel6);
	gSizer1->Add(m_panel6, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(gSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_nPlayers->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MainFrame::m_nPlayersOnSpinCtrl), NULL, this);
	m_ComputeButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_ComputeButtonClick), NULL, this);
	m_ResetButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_ResetButtonClick), NULL, this);
	m_RandomButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_RandomButtonClick), NULL, this);
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_nPlayers->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MainFrame::m_nPlayersOnSpinCtrl), NULL, this);
	m_ComputeButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_ComputeButtonClick), NULL, this);
	m_ResetButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_ResetButtonClick), NULL, this);
	m_RandomButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::m_RandomButtonClick), NULL, this);

}
