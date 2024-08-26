#include "Auction.h"
#include <numeric>
#include <queue>
#include <random>
#include <algorithm>
#include "lemon/lp.h"
#include "glpk.h"

void Auction::AddOffer(int player, std::vector<std::pair<int, int>> items_value, const std::vector<complement>& value)
{
	int total_complement_value = 0;
	int total_offer_value = 0;

	//Add complements
	for (auto it = value.cbegin(); it != value.cend(); it++)
	{
		complements_perpair.emplace(player, *it);
		total_complement_value += it->value;
	}
	//complements_total.emplace(total_complement_value, player);
	total_complements_value += total_complement_value;

	//Add item offers
	for (auto it = items_value.cbegin(); it != items_value.cend(); it++)
	{
		offers_peritem.emplace(player, *it); //key: player, value: item-offer
		total_offer_value += it->second;
		items.emplace(it->first);
	}

	offers_total.emplace(total_offer_value, player);
	offers_norm_total.emplace(total_offer_value / items_value.size(), player);
	offers_LOM_total.emplace(total_offer_value / std::sqrtf(std::abs((int)items_value.size())), player);

	vc_total.emplace(total_offer_value + total_complement_value, player);
	vc_norm_total.emplace((total_offer_value + total_complement_value) / items_value.size(), player);
	vc_LOM_total.emplace((total_offer_value + total_complement_value) / std::sqrtf(std::abs((int)items_value.size())), player);

	total_items_value += total_offer_value;

	players.emplace(player);
}

void Auction::Solve_RA(std::vector<int> modes)
{
	allocation.resize(*std::max_element(modes.cbegin(), modes.cend()) + 1);
	allocation_complements.resize(*std::max_element(modes.cbegin(), modes.cend()) + 1);

	for (auto it = modes.cbegin(); it != modes.cend(); it++)
	{
		if (*it < 6)
		{
			Solve_RA_G(*it);
		}
		else if (*it == 6)
		{
			Solve_RA_LP_Simplex();
		}
		else if (*it == 7)
		{
			Solve_RA_LP_Simplex_rounddet();
		}
		else if (*it == 8)
		{
			Solve_RA_LP_Interior();
		}
		else
		{
		}

		std::unordered_set<std::string> complements_set;
		for (const auto& player : players)
		{
			std::vector<std::pair<complement, int>> complements;
			const auto& [p_first, p_end] = complements_perpair.equal_range(player);

			for (auto p_iter = p_first; p_iter != p_end; p_iter++)
			{
				bool exists = allocation[*it].contains(p_iter->first);

				if (exists)
				{
					const auto& items = allocation[*it].find(p_iter->first)->second;
					const auto& [complementid, item1, item2, value] = p_iter->second;
					bool found1(false), found2(false);

					for (const auto& [item, value] : items)
					{

						if (item == item1)
						{
							found1 = true;
						}
						else if (item == item2)
						{
							found2 = true;
						}
					}
					if (found1 && found2)
					{
						const auto& [iter, inserted] = complements_set.emplace(complementid);
						if (inserted)
						{
							complements.emplace_back(p_iter->second, p_iter->first);
						}
					}
				}
			}
			if (complements.size())
			{
				allocation_complements[*it].emplace(player, complements);
			}
			
		}
	}
}

void Auction::Solve_RA_G(int mode)
{
	if (mode == 0) //Greedy - value-only
	{
		for (auto it = offers_total.cbegin(); it != offers_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(offers_total, 0);
	}
	else if (mode == 1) //Greedy - value and complements
	{
		for (auto it = vc_total.cbegin(); it != vc_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(vc_total, 1);
	}
	else if (mode == 2) //Greedy - Normalized
	{
		for (auto it = offers_norm_total.cbegin(); it != offers_norm_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(offers_norm_total, 2);
	}
	else if (mode == 3) //Greedy - VC normalized
	{
		for (auto it = vc_norm_total.cbegin(); it != vc_norm_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(vc_norm_total, 3);
	}
	else if (mode == 4) //Greedy - LOS
	{
		for (auto it = offers_LOM_total.cbegin(); it != offers_LOM_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(offers_LOM_total, 4);
	}
	else if (mode == 5) //Greedy - VC LOS
	{
		for (auto it = vc_LOM_total.cbegin(); it != vc_LOM_total.cend(); it++)
		{
			ordered_entries.push(it->first);
		}
		Solve_RA_Greedy(vc_LOM_total, 5);
	}
}

void Auction::Solve_RA_Greedy(std::unordered_multimap<int, int> totals, int mode)
{
	std::unordered_set<int> items_actual = items;

	while (ordered_entries.size())
	{
		int entry = ordered_entries.top();
		auto player = totals.find(entry)->second;
		if (allocation[mode].find(player) != allocation[mode].end())
		{
			ordered_entries.pop();
			continue;
		}
		auto player_items = offers_peritem.equal_range(player);

		std::vector<std::pair<int, int>> accepted_offer;
		for (auto it2 = player_items.first; it2 != player_items.second; it2++)
		{
			auto item = items_actual.find(it2->second.first);
			if (item != items_actual.end())
			{
				accepted_offer.emplace_back(it2->second);
			}
		}

		if (accepted_offer.size())
		{
			allocation[mode].emplace(player, accepted_offer);
			for (auto it = accepted_offer.cbegin(); it != accepted_offer.cend(); it++)
			{
				items_actual.erase(it->first);
			}
		}
		ordered_entries.pop();
	}
}

void Auction::Solve_RA_LP_Simplex()
{
	lemon::GlpkLp solver;
	solver.messageLevel(lemon::LpBase::MESSAGE_VERBOSE);

	//std::vector<lemon::LpBase::Col> columns;
	//std::vector<lemon::LpBase::Row> rows;

	std::unordered_multimap<int, lemon::Lp::Col> offer_cols_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> item_col_mapping;
	std::map<lemon::Lp::Col, int> col_item_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> complement_cols_mapping;
	//std::unordered_map<std::string, lemon::Lp::Col> complement_col_mapping;

	lemon::Lp::Expr objfunction;

	//Add columns representing per-item offers
	for (auto it = offers_total.cbegin(); it != offers_total.cend(); it++)
	{
		std::unordered_map<int, lemon::Lp::Col> item_col_perplayer_mapping;

		const auto& player = it->second;
		const auto& [first, end] = offers_peritem.equal_range(player); //get set of player offers

		for (auto offer_iter = first; offer_iter != end; offer_iter++)
		{
			const auto& [item, offer] = offer_iter->second;
			const auto& col_iter = offer_cols_mapping.emplace(player, solver.addCol());
			item_col_mapping.emplace(item, col_iter->second);
			item_col_perplayer_mapping.emplace(item, col_iter->second);
			col_item_mapping.emplace(col_iter->second, item);

			objfunction += col_iter->second * offer;

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}

		const auto& [c_first, c_end] = complements_perpair.equal_range(player);
		for (auto complement_iter = c_first; complement_iter != c_end; complement_iter++)
		{
			const auto& [complementid_unused, item1, item2, value] = complement_iter->second;
			const auto& col_iter = complement_cols_mapping.emplace(player, solver.addCol());
			//complement_col_mapping.emplace(complementid, col_iter->second);

			objfunction += col_iter->second * value;

			const auto& item1_col = item_col_perplayer_mapping.find(item1)->second;
			solver.addRow(item1_col >= col_iter->second);

			const auto& item2_col = item_col_perplayer_mapping.find(item2)->second;
			solver.addRow(item2_col >= col_iter->second);

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}
	}

	for (const auto& item : items)
	{
		lemon::Lp::Expr sumof1;

		const auto [first, last] = item_col_mapping.equal_range(item);
		for (auto iter = first; iter != last; iter++)
		{
			sumof1 += iter->second;
		}
		solver.addRow(sumof1 == 1.0);
	}

	solver.max();
	solver.obj(objfunction);

	solver.write("lp.lp", "LP");

	std::unordered_multimap <int, std::pair<int, float>> result_peritem; //player; item, result

	auto status = solver.solve();
	if (status == lemon::LpBase::SolveExitStatus::SOLVED)
	{
		auto problemtype = solver.primalType();
		if (problemtype == lemon::LpSolver::INFEASIBLE)
		{
			result_peritem.emplace(0, std::make_pair(0, -1));
		}
		else if (problemtype == lemon::LpSolver::FEASIBLE)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					result_peritem.emplace(player, std::make_pair(lemon::LpBase::id(iter->second), -2));
				}
			}
		}
		else if (problemtype == lemon::LpSolver::OPTIMAL)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					const auto& col = iter->second;
					auto result = (float)solver.primal(col);

					if (result < 0.000001f)
					{
						result = 0.0f;
					}
					else
					{
						result_peritem.emplace(player, std::make_pair(col_item_mapping.find(col)->second, result));
					}
				}
			}
		}
		else if (problemtype == lemon::LpSolver::UNBOUNDED)
		{
			for (const auto& [player, item_offer] : offers_peritem)
			{
				result_peritem.emplace(0, std::make_pair(0, -4));
			}
		}
		else //undefined
		{
		}

		//Collect resuilts from model

		std::mt19937 randomgen;
		std::uniform_int_distribution<> dist(0, offers_total.size() - 1);
		std::uniform_real_distribution<> dist2(0, 1);

		std::unordered_set<int> items_copy = items;

		do
		{
			int player = dist(randomgen);
			float margin = dist2(randomgen);

			const auto& [first, last] = result_peritem.equal_range(player);
			std::vector<std::pair<int, int>> items_won;

			for (auto iter = first; iter != last; )
			{
				const auto& [item, value] = iter->second;

				if (items_copy.find(item) != items_copy.end())
				{
					if (value >= margin)
					{
						const auto& [offer_begin, offer_end] = offers_peritem.equal_range(player);
						int price = -1;
						for (auto offer_iter = offer_begin; offer_iter != offer_end; offer_iter++)
						{
							if (offer_iter->second.first == item)
							{
								price = offer_iter->second.second;
							}
						}

						items_won.emplace_back(item, price);
						items_copy.erase(item);
						iter = result_peritem.erase(iter);
					}
					else { iter++; continue; }
				}
				else { iter++; continue; }
			}

			if (items_won.size())
			{
				allocation[6].emplace(player, items_won);
			}
		} while (items_copy.size());
	}
	else
	{
	}
}

void Auction::Solve_RA_LP_Interior()
{
	lemon::GlpkLp solver;
	solver.messageLevel(lemon::LpBase::MESSAGE_VERBOSE);

	//std::vector<lemon::LpBase::Col> columns;
	//std::vector<lemon::LpBase::Row> rows;

	std::unordered_multimap<int, lemon::Lp::Col> offer_cols_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> item_col_mapping;
	std::map<lemon::Lp::Col, int> col_item_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> complement_cols_mapping;
	//std::unordered_map<std::string, lemon::Lp::Col> complement_col_mapping;

	lemon::Lp::Expr objfunction;

	//Add columns representing per-item offers
	for (auto it = offers_total.cbegin(); it != offers_total.cend(); it++)
	{
		std::unordered_map<int, lemon::Lp::Col> item_col_perplayer_mapping;

		const auto& player = it->second;
		const auto& [first, end] = offers_peritem.equal_range(player); //get set of player offers

		for (auto offer_iter = first; offer_iter != end; offer_iter++)
		{
			const auto& [item, offer] = offer_iter->second;
			const auto& col_iter = offer_cols_mapping.emplace(player, solver.addCol());
			item_col_mapping.emplace(item, col_iter->second);
			item_col_perplayer_mapping.emplace(item, col_iter->second);
			col_item_mapping.emplace(col_iter->second, item);

			objfunction += col_iter->second * offer;

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}

		const auto& [c_first, c_end] = complements_perpair.equal_range(player);
		for (auto complement_iter = c_first; complement_iter != c_end; complement_iter++)
		{
			const auto& [complementid_unused, item1, item2, value] = complement_iter->second;
			const auto& col_iter = complement_cols_mapping.emplace(player, solver.addCol());
			//complement_col_mapping.emplace(complementid, col_iter->second);

			objfunction += col_iter->second * value;

			const auto& item1_col = item_col_perplayer_mapping.find(item1)->second;
			solver.addRow(item1_col >= col_iter->second);

			const auto& item2_col = item_col_perplayer_mapping.find(item2)->second;
			solver.addRow(item2_col >= col_iter->second);

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}
	}

	for (const auto& item : items)
	{
		lemon::Lp::Expr sumof1;

		const auto [first, last] = item_col_mapping.equal_range(item);
		for (auto iter = first; iter != last; iter++)
		{
			sumof1 += iter->second;
		}
		solver.addRow(sumof1 == 1.0);
	}

	solver.max();
	solver.obj(objfunction);

	solver.write("lp.lp", "LP");

	std::unordered_multimap <int, std::pair<int, float>> result_peritem; //player; item, result

	//auto status = solver.solve();
	auto glp = (glp_prob*)solver.lpx();
	glp_iptcp glpi;

	glp_init_iptcp(&glpi);
	int glp_status = glp_interior(glp, &glpi);
	lemon::LpBase::SolveExitStatus status = glp_status ? lemon::LpBase::SolveExitStatus::UNSOLVED : lemon::LpBase::SolveExitStatus::SOLVED;

	if (status == lemon::LpBase::SolveExitStatus::SOLVED)
	{
		auto problemtype = lemon::LpSolver::OPTIMAL;//solver.primalType();
		if (problemtype == lemon::LpSolver::INFEASIBLE)
		{
			result_peritem.emplace(0, std::make_pair(0, -1));
		}
		else if (problemtype == lemon::LpSolver::FEASIBLE)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					result_peritem.emplace(player, std::make_pair(lemon::LpBase::id(iter->second), -2));
				}
			}
		}
		else if (problemtype == lemon::LpSolver::OPTIMAL)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					const auto& col = iter->second;
					auto result = (float)glp_ipt_col_prim(glp, solver.lpxCol(col));

					if (result < 0.000001f)
					{
						result = 0.0f;
					}
					else
					{
						result_peritem.emplace(player, std::make_pair(col_item_mapping.find(col)->second, result));
					}
				}
			}
		}
		else if (problemtype == lemon::LpSolver::UNBOUNDED)
		{
			for (const auto& [player, item_offer] : offers_peritem)
			{
				result_peritem.emplace(0, std::make_pair(0, -4));
			}
		}
		else //undefined
		{
		}

		//Collect resuilts from model

		std::mt19937 randomgen;
		std::uniform_int_distribution<> dist(0, offers_total.size() - 1);
		std::uniform_real_distribution<> dist2(0, 1);

		std::unordered_set<int> items_copy = items;

		do
		{
			int player = dist(randomgen);
			float margin = dist2(randomgen);

			const auto& [first, last] = result_peritem.equal_range(player);
			std::vector<std::pair<int, int>> items_won;


			for (auto iter = first; iter != last; )
			{
				const auto& [item, value] = iter->second;

				if (items_copy.find(item) != items_copy.end())
				{
					if (value >= margin)
					{
						const auto& [offer_begin, offer_end] = offers_peritem.equal_range(player);
						int price = -1;
						for (auto offer_iter = offer_begin; offer_iter != offer_end; offer_iter++)
						{
							if (offer_iter->second.first == item)
							{
								price = offer_iter->second.second;
							}
						}

						items_won.emplace_back(item, price);
						items_copy.erase(item);
						iter = result_peritem.erase(iter);
					}
					else { iter++; continue; }
				}
				else { iter++; continue; }
			}

			if (items_won.size())
			{
				allocation[8].emplace(player, items_won);
			}
		} while (items_copy.size());
	}
	else
	{
	}
}

void Auction::Solve_RA_LP_Simplex_rounddet()
{
	lemon::GlpkLp solver;
	solver.messageLevel(lemon::LpBase::MESSAGE_VERBOSE);

	//std::vector<lemon::LpBase::Col> columns;
	//std::vector<lemon::LpBase::Row> rows;

	std::unordered_multimap<int, lemon::Lp::Col> offer_cols_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> item_col_mapping;
	std::map<lemon::Lp::Col, int> col_item_mapping;
	std::unordered_multimap<int, lemon::Lp::Col> complement_cols_mapping;
	//std::unordered_map<std::string, lemon::Lp::Col> complement_col_mapping;

	lemon::Lp::Expr objfunction;

	//Add columns representing per-item offers
	for (auto it = offers_total.cbegin(); it != offers_total.cend(); it++)
	{
		std::unordered_map<int, lemon::Lp::Col> item_col_perplayer_mapping;

		const auto& player = it->second;
		const auto& [first, end] = offers_peritem.equal_range(player); //get set of player offers

		for (auto offer_iter = first; offer_iter != end; offer_iter++)
		{
			const auto& [item, offer] = offer_iter->second;
			const auto& col_iter = offer_cols_mapping.emplace(player, solver.addCol());
			item_col_mapping.emplace(item, col_iter->second);
			item_col_perplayer_mapping.emplace(item, col_iter->second);
			col_item_mapping.emplace(col_iter->second, item);

			objfunction += col_iter->second * offer;

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}

		const auto& [c_first, c_end] = complements_perpair.equal_range(player);
		for (auto complement_iter = c_first; complement_iter != c_end; complement_iter++)
		{
			const auto& [complementid_unused, item1, item2, value] = complement_iter->second;
			const auto& col_iter = complement_cols_mapping.emplace(player, solver.addCol());
			//complement_col_mapping.emplace(complementid, col_iter->second);

			objfunction += col_iter->second * value;

			const auto& item1_col = item_col_perplayer_mapping.find(item1)->second;
			solver.addRow(item1_col >= col_iter->second);

			const auto& item2_col = item_col_perplayer_mapping.find(item2)->second;
			solver.addRow(item2_col >= col_iter->second);

			solver.colLowerBound(col_iter->second, 0.0);
			//solver.colUpperBound(col_iter->second, 1.0);
		}
	}

	for (const auto& item : items)
	{
		lemon::Lp::Expr sumof1;

		const auto [first, last] = item_col_mapping.equal_range(item);
		for (auto iter = first; iter != last; iter++)
		{
			sumof1 += iter->second;
		}
		solver.addRow(sumof1 == 1.0);
	}

	solver.max();
	solver.obj(objfunction);

	solver.write("lp.lp", "LP");

	std::unordered_multimap <int, std::pair<int, float>> result_peritem; //player; item, result

	auto status = solver.solve();
	if (status == lemon::LpBase::SolveExitStatus::SOLVED)
	{
		auto problemtype = solver.primalType();
		if (problemtype == lemon::LpSolver::INFEASIBLE)
		{
			result_peritem.emplace(0, std::make_pair(0, -1));
		}
		else if (problemtype == lemon::LpSolver::FEASIBLE)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					result_peritem.emplace(player, std::make_pair(lemon::LpBase::id(iter->second), -2));
				}
			}
		}
		else if (problemtype == lemon::LpSolver::OPTIMAL)
		{
			for (const auto& [total, player] : offers_total)
			{
				//const auto& item = item_offer.first;
				const auto& [first, last] = offer_cols_mapping.equal_range(player);

				for (auto iter = first; iter != last; iter++)
				{
					const auto& col = iter->second;
					auto result = (float)solver.primal(col);

					if (result < 0.000001f)
					{
						result = 0.0f;
					}
					else
					{
						result_peritem.emplace(player, std::make_pair(col_item_mapping.find(col)->second, result));
					}
				}
			}
		}
		else if (problemtype == lemon::LpSolver::UNBOUNDED)
		{
			for (const auto& [player, item_offer] : offers_peritem)
			{
				result_peritem.emplace(0, std::make_pair(0, -4));
			}
		}
		else //undefined
		{
		}

		//Collect resuilts from model

		std::mt19937 randomgen;
		std::uniform_int_distribution<> dist(0, offers_total.size() - 1);
		std::uniform_real_distribution<> dist2(0, 0.5f);

		std::unordered_set<int> items_copy = items;

		do
		{
			int player = dist(randomgen);

			const auto& [first, last] = result_peritem.equal_range(player);
			std::vector<std::pair<int, int>> items_won;

			for (auto iter = first; iter != last; )
			{
				const auto& [item, value] = iter->second;

				if (items_copy.find(item) != items_copy.end())
				{
					if (value >= 0.5f)
					{
						const auto& [offer_begin, offer_end] = offers_peritem.equal_range(player);
						int price = -1;
						for (auto offer_iter = offer_begin; offer_iter != offer_end; offer_iter++)
						{
							if (offer_iter->second.first == item)
							{
								price = offer_iter->second.second;
							}
						}

						items_won.emplace_back(item, price);
						items_copy.erase(item);
						iter = result_peritem.erase(iter);
					}
					else { iter++; continue; }
				}
				else { iter++; continue; }
			}

			if (items_won.size())
			{
				allocation[7].emplace(player, items_won);
			}

			float maxval = 0.0f;
			for (const auto& [ofer_unused, itemval] : result_peritem)
			{
				const auto& [item_unused, val] = itemval;
				if (maxval < val)
				{
					maxval = val;
				}
			}
			if (maxval < 0.5f) { break; }

		} while (items_copy.size());

		while (items_copy.size())
		{
			int player = dist(randomgen);
			float margin = dist2(randomgen);

			const auto& [first, last] = result_peritem.equal_range(player);
			std::vector<std::pair<int, int>> items_won;

			for (auto iter = first; iter != last; iter++)
			{
				const auto& [item, value] = iter->second;

				if (items_copy.find(item) != items_copy.end())
				{
					if (value >= margin)
					{
						const auto& [offer_begin, offer_end] = offers_peritem.equal_range(player);
						int price = -1;
						for (auto offer_iter = offer_begin; offer_iter != offer_end; offer_iter++)
						{
							if (offer_iter->second.first == item)
							{
								price = offer_iter->second.second;
							}
						}

						items_won.emplace_back(item, price);
						items_copy.erase(item);
					}
				}
			}

			if (items_won.size())
			{
				allocation[7].emplace(player, items_won);
			}
		}
	}
	else
	{
	}
}