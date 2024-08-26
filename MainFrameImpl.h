#pragma once
#include "CAAppFrame.h"
class MainFrameImpl : public MainFrame
{
public:
	MainFrameImpl() :MainFrame(nullptr) { }
	virtual void m_nPlayersOnSpinCtrl(wxSpinEvent& event) override;
	virtual void m_ComputeButtonClick(wxCommandEvent& event) override;
	virtual void m_ResetButtonClick(wxCommandEvent& event) override;
	virtual void m_RandomButtonClick(wxCommandEvent& event) override;

private:
	wxGrid* AddNotebookPage(std::string name, wxNotebook* target, std::string column1, std::string column2);
	void AdjustResultGrids(int newcount);
	void AdjustGridRows(wxGrid* target, int newcount);
	void Init();


};

