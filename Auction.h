#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

struct complement
{
	std::string complementid;
	int item1, item2;
	int value;
};

struct fulloffer
{
	int player;
	std::vector<std::pair<int, int>> items_actual; // item;value
	std::vector<complement> complements; // item;value
};

class Auction
{
public:
	Auction() = default;
	~Auction() = default;

	void AddOffer(int player, std::vector<std::pair<int, int>> items, const std::vector<complement> &value);
	void Solve_RA(std::vector<int> modes);

	//Results
	std::vector<std::unordered_map<int, std::vector<std::pair<int, int>>>> allocation; //key: player, value: items/offers
	std::vector<std::unordered_map<int, std::vector<std::pair<complement, int>>>> allocation_complements; //key: player, value: complements/offers
	int total_items_value = 0;
	int total_complements_value = 0;
	int GetItemsCount() { return items.size(); }

private:
	//per player
	std::unordered_multimap <int, std::pair<int,int>> offers_peritem; //key: player, value: item-offer
	std::unordered_multimap <int, complement> complements_perpair; //key: player, value: complement-value
	
	//Totals of offers
	std::unordered_multimap <int, int> offers_total; //key: value, value: player
	std::unordered_multimap <int, int> offers_norm_total; //key: value, value: player
	std::unordered_multimap <int, int> offers_LOM_total; //key: value, value: player

	//Totals of Value/Complements 
	std::unordered_multimap <int, int> vc_total; //key: value, value: player
	std::unordered_multimap <int, int> vc_norm_total; //key: value, value: player
	std::unordered_multimap <int, int> vc_LOM_total; //key: value, value: player

	//Greedy algo
	std::priority_queue<int> ordered_entries;

	//General
	std::unordered_set<int> items;
	std::unordered_set<int> players;

	void Solve_RA_LP_Simplex();
	void Solve_RA_LP_Simplex_rounddet();
	void Solve_RA_LP_Interior();
	void Solve_RA_G(int mode);
	void Solve_RA_Greedy(std::unordered_multimap <int, int> totals, int mode);
};
