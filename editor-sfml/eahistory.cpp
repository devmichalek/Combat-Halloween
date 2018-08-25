#include "eahistory.h"

EAHistory::EAHistory()
{
	free();
}

EAHistory::~EAHistory()
{
	free();
}

void EAHistory::free()
{
	reset();


}

void EAHistory::reset()
{
	if (!xy.empty())
		xy.clear();

	if (!tc.empty())
		tc.clear();

	if (!ai.empty())
		ai.clear();

	if (!history.empty())
		history.clear();
}



const std::vector<std::string>& EAHistory::get()
{
	history.clear();

	// action

	return history;
}

void EAHistory::set(const std::vector<std::string> &newHistory)
{

}



void EAHistory::add(const int &x, const int &y, const int &t, const int &c, const std::string &ai)
{
	this->xy.push_back(std::make_pair(x, y));
	this->tc.push_back(std::make_pair(t, c));
	this->ai.push_back(ai);
}

void EAHistory::undo()
{
	/*
	if (!historyXY.empty())
	{
		int n = historyXY.size() - 1;
		int x = historyXY[n].first;
		int y = historyXY[n].second;

		int t = historyTC[n].first;
		int c = historyTC[n].second;

		// Revert changes
		historyXY.pop_back();
		historyTC.pop_back();
		historyAI.pop_back();

		// Decide where to remove changes
		if (t == KNIGHT)				entityKnight.remove(x, y);
		else if (t == TILE)				entityTiles.remove(x, y);
		else if (t == UNVISIBLE_TILE)	entityUnTiles.remove(x, y);
		else if (t == LANDSCAPE)		entityLandscape.remove(x, y);
	}
	*/
}

void EAHistory::remove(const int &t, const int &c, const int &x, const int &y)
{

}

void EAHistory::modify(const int &t, const int &c, const int &x, const int &y, const std::string &ai)
{

}