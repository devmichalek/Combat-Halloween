#include "eahistory.h"
#include "boost/lexical_cast.hpp"

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
	clear();
}

void EAHistory::reset()
{
	ctrl_key = false;
	z_key = false;
	undoState = false;
}

void EAHistory::clear()
{
	clear_local();

	if (!content.empty())
		content.clear();

	counterID = 0;
	saveVersion = 0;
	loadVersion = 0;
}

void EAHistory::clear_local()
{
	if (!ids.empty())
		ids.clear();

	if (!xy.empty())
		xy.clear();

	if (!tc.empty())
		tc.clear();

	if (!ai.empty())
		ai.clear();

	index = -1;
}

void EAHistory::fill_local()
{
	// After content is loaded correctly we have to ascribe new ids.
	int id_counter = 0;
	for (size_t i = 0; i < content.size(); ++i)
	{
		size_t pos = content[i].find("id:-1");	// Find id different than -1
		if (pos == std::string::npos)
		{
			pos = content[i].find("id:") + 3;
			size_t length = content[i].find(" ai:") - pos;
			content[i].replace(pos, length, std::to_string(id_counter));
			++id_counter;
		}
	}

	int counter = 0;
	int id, x, y;
	char t, c;
	int s2 = 2, s3 = 3;
	std::string ai;
	for (auto &it : content)
	{
		t = boost::lexical_cast<int>(it.substr(it.find("t:") + s2, it.find(" c:") - (it.find("t:") + s2)));
		c = boost::lexical_cast<int>(it.substr(it.find("c:") + s2, it.find(" x:") - (it.find("c:") + s2)));
		x = boost::lexical_cast<int>(it.substr(it.find("x:") + s2, it.find(" y:") - (it.find("x:") + s2)));
		y = boost::lexical_cast<int>(it.substr(it.find("y:") + s2, it.find(" id:") - (it.find("y:") + s2)));
		id = boost::lexical_cast<int>(it.substr(it.find("id:") + s3, it.find(" ai:") - (it.find("id:") + s3)));
		ai = it.substr(it.find("ai:") + s3);

		tc.push_back(std::make_pair(t, c));
		xy.push_back(std::make_pair(x, y));
		ids.push_back(id);
		this->ai.push_back(ai);
	}
}



void EAHistory::handle(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;

		if (code == sf::Keyboard::LControl)
		{
			ctrl_key = true;
		}

		if (!z_key && ctrl_key)
		{
			if (code == sf::Keyboard::Z)
			{
				z_key = true;
				undoState = true;
			}
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		int code = event.key.code;

		if (code == sf::Keyboard::LControl)
		{
			ctrl_key = false;
		}

		if (code == sf::Keyboard::Z)
		{
			z_key = false;
		}
	}
}

bool EAHistory::next()
{
	if (index < static_cast<int>(content.size()) - 1)
	{
		++index;
		return true;
	}
	
	loadVersion = 0;	// loaded
	return false;
}

void EAHistory::getXY(int &x, int &y)
{
	x = xy[index].first;
	y = xy[index].second;
}

void EAHistory::getTC(char &t, char &c)
{
	t = tc[index].first;
	c = tc[index].second;
}

void EAHistory::getID(int &id)
{
	id = ids[index];
}

void EAHistory::getAI(std::string &ai)
{
	ai = this->ai[index];
}



void EAHistory::add(const int &t, const int &c, const int &x, const int &y, const std::string &ai, int ID)
{
	xy.push_back(std::make_pair(x, y));
	tc.push_back(std::make_pair(t, c));
	this->ai.push_back(ai);
	ids.push_back(ID);

	content.push_back("t:" + std::to_string(t) + " "
		+ "c:" + std::to_string(c) + " "
		+ "x:" + std::to_string(x) + " "
		+ "y:" + std::to_string(y) + " "
		+ "id:" + std::to_string(ID) + " "
		+ "ai:" + ai + "\n");
	saveVersion = 1;
}

bool EAHistory::undo(int &t, int &x, int &y)
{
	if (!undoState)
		return false;

	undoState = false;

	if (xy.empty())
		return false;

	int n = xy.size() - 1;
	x = xy[n].first;
	y = xy[n].second;

	t = tc[n].first;

	// Revert changes
	ids.pop_back();
	xy.pop_back();
	tc.pop_back();
	ai.pop_back();
	content.pop_back();

	saveVersion = 1;
	return true;
}

void EAHistory::remove(int t, const int &c, const int &x, const int &y)	// we promise that the one we remove has no ID (ID = -1)
{
	saveVersion = 1;
	std::vector<int> resultXY;
	for (unsigned i = 0; i < xy.size(); ++i)
	{
		if (xy[i].first == x && xy[i].second == y)
			resultXY.push_back(i);
	}

	if (!resultXY.empty())	// easy task, only one entity with that position
	{
		for (unsigned i = 0; i < resultXY.size(); ++i)
		{
			ids.erase(ids.begin() + resultXY[i]);
			xy.erase(xy.begin() + resultXY[i]);
			tc.erase(tc.begin() + resultXY[i]);
			ai.erase(ai.begin() + resultXY[i]);
			content.erase(content.begin() + resultXY[i]);
		}
	}
}

void EAHistory::removeByID(const int &ID)
{
	saveVersion = 1;
	for (int i = 0; i < ids.size(); ++i)
	{
		if (ids[i] == ID)
		{
			ids.erase(ids.begin() + i);
			xy.erase(xy.begin() + i);
			tc.erase(tc.begin() + i);
			ai.erase(ai.begin() + i);
			content.erase(content.begin() + i);
			break;
		}
	}
}

//void EAHistory::modify(const int &t, const int &c, const int &x, const int &y, const std::string &ai)	// we promise that the one we modify has no ID (ID = -1)
//{
//	saveVersion = 1;
//}
//
//void EAHistory::modifyByID(const int &ID, const std::string &ai)
//{
//	saveVersion = 1;
//}

const int EAHistory::getNewID()
{
	return counterID++;
}
