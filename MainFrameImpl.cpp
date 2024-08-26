#include "MainFrameImpl.h"
#include <random>
#include <string>
#include "Auction.h"
#include <fstream>
#include <algorithm>
#include <set>
#include <numeric>
#include <format>

void MainFrameImpl::m_ComputeButtonClick(wxCommandEvent& event)
{
	Auction auction;
	Init();

	for (int i = 0; i < m_PlayerOffers->GetNumberRows(); i++)
	{
		auto offer = (std::string)m_PlayerOffers->GetCellValue(i, 0);//offer format: item:value,...
		auto complements = (std::string)m_PlayerOffers->GetCellValue(i, 1);//complement format: item1,item2:value;...
		std::vector<std::pair<int, int>> items;
		if (offer.size())
		{
			for (int j = 0; j < offer.size();)
			{
				int j_n = offer.find(':', j);
				auto item = offer.substr(j, j_n - j);
				j = j_n + 1;
				j_n = offer.find(',', j);
				auto value = offer.substr(j, j_n - j);
				items.emplace_back(std::make_pair(std::stoi(item), std::stoi(value)));
				if (j_n == std::string::npos) { break; }
				j = j_n + 1;
			}
		}
		else
		{
			continue;
		}

		std::vector<complement> vec_complements;
		if (complements.size())
		{
			for (int j = 0; j < complements.size();)
			{
				int j_n = complements.find(',', j);
				auto item1 = complements.substr(j, j_n - j);
				j = j_n + 1;
				j_n = complements.find(':', j);
				auto item2 = complements.substr(j, j_n - j);
				j = j_n + 1;
				j_n = complements.find(';', j);
				auto value = complements.substr(j, j_n - j);

				complement c;
				if (item1.size())
				{
					c.item1 = std::stoi(item1);
				}
				else
				{
					c.item1 = 0;
				}
				if (item2.size())
				{
					c.item2 = std::stoi(item2);
				}
				else
				{
					c.item2 = 0;
				}
				if (value.size())
				{
					c.value = std::stoi(value);
				}
				else
				{
					c.value = 0;
				}
				c.complementid = c.item1 < c.item2 ? item1 + "-" + item2 : item2 + "-" + item1;
				vec_complements.emplace_back(c);

				if (j_n == std::string::npos) { break; }
				j = j_n + 1;
			}
		}

		auction.AddOffer(i, items, vec_complements);
	}

	std::vector<int> modes;
	wxArrayInt wxselections;

	int nmodes = m_Methods->GetSelections(wxselections);

	for (int i = 0; i < nmodes; i++)
	{
		modes.emplace_back(wxselections.Item(i));
	}

	auction.Solve_RA(modes);

	if (auction.GetItemsCount() != m_nItems->GetValue()) { m_nItems->SetValue(auction.GetItemsCount()); }

	std::ofstream fout("results.txt");
	std::ofstream fitems("items.txt");
	std::ofstream fcomplements("complements.txt");
	std::ofstream fplayers("players.txt");

	std::vector<int> sets_winningoffers;
	std::vector<int> sets_winningcomplements;
	
	int colid = 0;
	for (auto mode : modes)
	{
		std::string methodname = (std::string)m_Methods->GetString(mode);
		std::string itemlisting, complementlisting, winnertotals, complementstotals;
		m_grid4->SetColLabelValue(colid, methodname);

		auto WinnerGrid = AddNotebookPage(methodname, m_WinnersNotebook, "Bid", "Value");
		auto ItemGrid = AddNotebookPage(methodname, m_ItemsNotebook, "Buyer", "Value");

		AdjustGridRows(WinnerGrid, m_nPlayers->GetValue());
		AdjustGridRows(ItemGrid, auction.GetItemsCount() + 1);

		int winningoffers = 0;

		for (auto it = auction.allocation[mode].cbegin(); it != auction.allocation[mode].cend(); it++)
		{
			std::string items;
			int value = 0;
			for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); it2++)
			{
				items += std::format("item: {},", it2->first);
				winningoffers += it2->second;
				value += it2->second;
				ItemGrid->SetCellValue(it2->first, 0, std::to_string(it->first));
				ItemGrid->SetCellValue(it2->first, 1, std::to_string(it2->second));

				itemlisting += std::format("item: {}:{} \n", it2->first, it2->second);
			}
			WinnerGrid->SetCellValue(it->first, 0, items);
			WinnerGrid->SetCellValue(it->first, 1, std::to_string(value));

			winnertotals += std::format("player: {}: {} \n", it->first, value);
		}

		int winningcomplements = 0;
		for (auto it = auction.allocation_complements[mode].cbegin(); it != auction.allocation_complements[mode].cend(); it++)
		{
			for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); it2++)
			{
				winningcomplements += it2->first.value;
				complementlisting += std::format("complement: {},{} : \n", it2->first.item1, it2->first.item2, it2->first.value);
			}
			complementstotals += std::format("player: {}:{} \n", it->first, winningcomplements);
		}

		fout << methodname << std::endl;
		fitems << methodname << std::endl << itemlisting << std::endl;
		fcomplements << methodname << std::endl << complementlisting << std::endl;
		fplayers << methodname << std::endl << winnertotals << complementstotals << std::endl;

		m_grid4->SetCellValue(0, colid, std::to_string(auction.total_items_value));
		m_grid4->SetCellValue(1, colid, std::to_string(auction.total_complements_value));

		m_grid4->SetCellValue(2, colid, std::to_string(winningoffers));
		m_grid4->SetCellValue(3, colid, std::to_string(winningcomplements));
		m_grid4->SetCellValue(4, colid, std::to_string(winningoffers + winningcomplements));
		m_grid4->SetCellValue(5, colid, std::to_string(auction.total_items_value - winningoffers));
		m_grid4->SetCellValue(6, colid, std::to_string(auction.total_complements_value - winningcomplements));
		m_grid4->SetCellValue(7, colid, std::to_string(auction.total_items_value + auction.total_complements_value - winningoffers - winningcomplements));
		m_grid4->SetCellValue(8, colid, std::to_string(auction.allocation[mode].size()));
		m_grid4->SetCellValue(9, colid, std::to_string(auction.allocation_complements[mode].size()));
		
		fout << std::format("Winning offers: {} \n Winning complements: {} \n Winning total: {} \n Delta offers: {} \n Delta complements: {} \n Delta totals: {} \n \
			No of winners: {} \n No of winning complements: {} \n \n",
			winningoffers,
			winningcomplements,
			winningoffers + winningcomplements,
			auction.total_items_value - winningoffers,
			auction.total_complements_value - winningcomplements,
			auction.total_items_value + auction.total_complements_value - winningoffers - winningcomplements,
			auction.allocation[mode].size(),
			auction.allocation_complements[mode].size()
			);
		
		colid++;

		for (int i = 0; i < ItemGrid->GetNumberRows(); i++)
		{
			auto value = ItemGrid->GetCellValue(i, 0);
			if (value.empty())
			{
				ItemGrid->HideRow(i);
			}
		}

		for (int i = 0; i < WinnerGrid->GetNumberRows(); i++)
		{
			auto value = WinnerGrid->GetCellValue(i, 0);
			if (value.empty())
			{
				WinnerGrid->HideRow(i);
			}
		}
	}
}

void MainFrameImpl::m_ResetButtonClick(wxCommandEvent& event)
{
	m_WinnersNotebook->DeleteAllPages();

	for (int i = 0; i < m_PlayerOffers->GetNumberRows(); i++)
	{
		for (int j = 0; j < m_PlayerOffers->GetNumberCols(); j++)
		{
			m_PlayerOffers->SetCellValue(i, j, "");
		}
	}

	m_ItemsNotebook->DeleteAllPages();

	m_Seed->SetValue(0);
}

void MainFrameImpl::m_RandomButtonClick(wxCommandEvent& event)
{
	int seed = m_Seed->GetValue();
	std::random_device rd;
	if (seed == 0)
	{
		seed = rd();
		m_Seed->SetValue(seed);
	}

	const auto& no_items = m_nItems->GetValue();

	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dist_offer_value(1, m_MaxPrice->GetValue());
	std::uniform_int_distribution<> dist_perplayeritem(1, m_MaxItemsPerPlayer->GetValue());

	std::vector<int> items(no_items);
	std::iota(items.begin(),items.end(),0);

	for (int po = 0; po < m_PlayerOffers->GetNumberRows(); po++)
	{
		int nitems = dist_perplayeritem(gen); //number of items this player will bid on
		
		std::vector<int> selected_items(nitems);
		std::string offer;

		std::sample(items.cbegin(), items.cend(), selected_items.begin(), nitems, gen);

		for(const auto item : selected_items)
		{
			offer += std::format("{}:{},",item, dist_offer_value(gen));
		}

		m_PlayerOffers->SetCellValue(po, 0, offer);

		std::unordered_set<std::string> complements;
		std::uniform_int_distribution<> dist_perplayercompl(1, m_MaxComplements->GetValue());
		std::uniform_int_distribution<> dist_complement_value(0, m_MaxPrice->GetValue());
		int ncompl = dist_perplayercompl(gen);

		for (int i = 0; i < ncompl; i++)
		{
			if (nitems > 1)
			{
				std::vector<int> pair(2);
				std::sample(selected_items.cbegin(), selected_items.cend(), pair.begin(), 2, gen);

				std::sort(pair.begin(), pair.end());

				complements.emplace(std::format("{},{}", pair[0], pair[1]));
			}
		}

		std::string str_complements;
		for (const auto& c : complements)
		{
			str_complements += std::format("{}:{};",c, dist_complement_value(gen));
		}
		
		m_PlayerOffers->SetCellValue(po, 1, str_complements);
	}
}

wxGrid* MainFrameImpl::AddNotebookPage(std::string name, wxNotebook* target, std::string column1, std::string column2)
{
	auto Panel = new wxPanel(target, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	auto Grid = new wxGrid(Panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	Grid->CreateGrid(10, 2);
	Grid->EnableEditing(false);
	Grid->EnableGridLines(true);
	Grid->EnableDragGridSize(true);
	Grid->SetMargins(0, 0);

	// Columns
	Grid->EnableDragColMove(false);
	Grid->EnableDragColSize(true);
	Grid->SetColLabelSize(30);
	Grid->SetColLabelValue(0, column1);
	Grid->SetColLabelValue(1, column2);
	Grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	Grid->EnableDragRowSize(true);
	Grid->SetRowLabelSize(80);
	Grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Cell Defaults
	Grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);

	wxFlexGridSizer* Sizer = new wxFlexGridSizer(0, 0, 0, 0);
	Sizer->SetFlexibleDirection(wxBOTH);
	Sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);
	Sizer->Add(Grid, 0, wxALL | wxEXPAND, 5);

	Panel->SetSizer(Sizer);
	Panel->Layout();
	Sizer->Fit(Panel);

	target->AddPage(Panel, name);

	return Grid;
}

void MainFrameImpl::AdjustResultGrids(int newcount)
{
}

void MainFrameImpl::AdjustGridRows(wxGrid* target, int newcount)
{
	int oldvalue = target->GetNumberRows();

	if (oldvalue > newcount)
	{
		target->DeleteRows(0, oldvalue - newcount);
	}
	else if (oldvalue < newcount)
	{
		target->AppendRows(newcount - oldvalue);
	}
}

void MainFrameImpl::Init()
{
	for (int i = 0; i < m_grid4->GetNumberCols(); i++)
	{
		m_grid4->SetCellValue(0, i, "0");
		m_grid4->SetCellValue(1, i, "0");
		m_grid4->SetCellValue(2, i, "0");
		m_grid4->SetCellValue(3, i, "0");
		m_grid4->SetCellValue(4, i, "0");
		m_grid4->SetCellValue(5, i, "0");
		m_grid4->SetCellValue(6, i, "0");
		m_grid4->SetCellValue(7, i, "0");
		m_grid4->SetCellValue(8, i, "0");
		m_grid4->SetCellValue(9, i, "0");
	}

	if (m_WinnersNotebook->GetPageCount()) { m_WinnersNotebook->DeletePage(0); }
	if (m_ItemsNotebook->GetPageCount()) { m_ItemsNotebook->DeletePage(0); }
}

void MainFrameImpl::m_nPlayersOnSpinCtrl(wxSpinEvent& event)
{
	AdjustGridRows(m_PlayerOffers, m_nPlayers->GetValue());
}
