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
	clear();
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
	if (!items.empty())
		items.clear();

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

	counterID = 0;
	char two = 2;
	char three = 3;
	ee::Item item;
	for (auto &it : content)
	{
		item.type = boost::lexical_cast<int>(it.substr(it.find("t:") + two, it.find(" c:") - (it.find("t:") + two)));
		item.chosen = boost::lexical_cast<int>(it.substr(it.find("c:") + two, it.find(" x:") - (it.find("c:") + two)));
		item.position.x = boost::lexical_cast<int>(it.substr(it.find("x:") + two, it.find(" y:") - (it.find("x:") + two)));
		item.position.y = boost::lexical_cast<int>(it.substr(it.find("y:") + two, it.find(" id:") - (it.find("y:") + two)));
		item.ID = boost::lexical_cast<int>(it.substr(it.find("id:") + three, it.find(" ai:") - (it.find("id:") + three)));
		item.ai = it.substr(it.find("ai:") + three);

		items.push_back(item);
		++counterID;
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

const ee::Item &EAHistory::getItem()
{
	return items[index];
}



void EAHistory::add(const ee::Item &item)
{
	items.push_back(item);

	content.push_back("t:" + std::to_string(item.type) + " "
		+ "c:" + std::to_string(item.chosen) + " "
		+ "x:" + std::to_string(item.position.x) + " "
		+ "y:" + std::to_string(item.position.y) + " "
		+ "id:" + std::to_string(item.ID) + " "
		+ "ai:" + item.ai + "\n");
	saveVersion = 1;
}

bool EAHistory::tryUndo(int &t, int &x, int &y)
{
	if (items.empty())
		return false;

	int n = items.size() - 1;
	x = items[n].position.x;
	y = items[n].position.y;

	t = items[n].type;

	// Revert changes
	items.pop_back();
	content.pop_back();

	saveVersion = 1;
	return true;
}

std::vector<ee::Item>::iterator EAHistory::getIteratorByID(const int &ID)
{
	std::vector<ee::Item>::iterator it = items.end();

	if (ID != cmm::Kind::VOID)
	{
		for (it = items.begin(); it != items.end(); ++it)
		{
			if ((*it).ID == ID)
			{
				return it;
			}
		}
	}

	return it;
}

void EAHistory::remove(const ee::Item &item)
{
	auto it = getIteratorByID(item.ID);
	if (it != items.end())
	{
		content.erase(content.begin() + std::distance(items.begin(), it));
		items.erase(it);
		saveVersion = 1;
		return;
	}
	else //  ID is unknown
	{
		std::vector<int> resultXY;
		for (unsigned i = 0; i < items.size(); ++i)
		{
			if (items[i].type != item.type || items[i].chosen != item.chosen)
				continue;

			if (items[i].position.x == item.position.x && items[i].position.y == item.position.y)
				resultXY.push_back(i);
		}

		if (!resultXY.empty())
		{
			saveVersion = 1;
			for (unsigned i = 0; i < resultXY.size(); ++i)
			{
				items.erase(items.begin() + resultXY[i]);
				content.erase(content.begin() + resultXY[i]);
			}
		}
	}
}

void EAHistory::modify(const ee::Item &item)
{
	auto it = getIteratorByID(item.ID);
	if (it != items.end())
	{
		int index = std::distance(items.begin(), it);

		items[index].ai = item.ai;
		std::string new_one = "t:" + std::to_string(item.type) + " "
			+ "c:" + std::to_string(item.chosen) + " "
			+ "x:" + std::to_string(item.position.x) + " "
			+ "y:" + std::to_string(item.position.y) + " "
			+ "id:" + std::to_string(item.ID) + " "
			+ "ai:" + item.ai + "\n";
		content[index] = new_one;

		saveVersion = 1;
		return;
	}
	else //  ID is unknown
	{
		std::vector<int> result;
		for (unsigned i = 0; i < items.size(); ++i)
		{
			if (items[i].type != item.type || items[i].chosen != item.chosen)
				continue;

			if (items[i].position.x == item.position.x && items[i].position.y == item.position.y)
				result.push_back(i);
		}

		if (!result.empty()) // must not be empty
		{
			if(result.size() != 1)
				assert(false);
			
			int index = result[0];
			items[index].ai = item.ai;

			std::string new_one = "t:" + std::to_string(item.type) + " "
				+ "c:" + std::to_string(item.chosen) + " "
				+ "x:" + std::to_string(item.position.x) + " "
				+ "y:" + std::to_string(item.position.y) + " "
				+ "id:" + std::to_string(item.ID) + " "
				+ "ai:" + item.ai + "\n";
			content[index] = new_one;
			saveVersion = 1;
		}
		else
			assert(false);
	}
}

const int EAHistory::getNewID()
{
	return counterID++;
}
