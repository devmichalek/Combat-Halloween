#include "eahistory.h"
#include "converter.h"

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
			if (pos != std::string::npos)
			{
				size_t length = content[i].find(" ai:") - pos;
				content[i].replace(pos, length, std::to_string(id_counter));
				++id_counter;
			}
		}
	}

	counterID = 0;
	ee::Item item;
	for (auto &it : content)
	{
		item.type =			boost::lexical_cast<int>(cmm::extractFromString(it, "t:", cmm::CSPACE));
		item.chosen =		boost::lexical_cast<int>(cmm::extractFromString(it, "c:", cmm::CSPACE));
		item.position.x =	boost::lexical_cast<int>(cmm::extractFromString(it, "x:", cmm::CSPACE));
		item.position.y =	boost::lexical_cast<int>(cmm::extractFromString(it, "y:", cmm::CSPACE));
		item.ID =			boost::lexical_cast<int>(cmm::extractFromString(it, "id:", cmm::CSPACE));
		item.ai = cmm::extractFromString(it, "ai:", cmm::CNEWLINE);
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

	content.push_back("t:" + std::to_string(item.type) + cmm::SSPACE
		+ "c:" + std::to_string(item.chosen) + cmm::SSPACE
		+ "x:" + std::to_string(item.position.x) + cmm::SSPACE
		+ "y:" + std::to_string(item.position.y) + cmm::SSPACE
		+ "id:" + std::to_string(item.ID) + cmm::SSPACE
		+ "ai:" + item.ai + cmm::SNEWLINE);
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

			if (resultXY.size() != 1)
			{
				// Rewrite, this process is slow but the most safety...
				std::vector<ee::Item> buffer;
				std::vector<std::string> strs;
				for (unsigned i = 0; i < items.size(); ++i)
				{
					std::vector<int>::iterator pos = std::find(resultXY.begin(), resultXY.end(), i);
					if (pos != resultXY.end())
						continue;

					buffer.push_back(items[i]);
					strs.push_back(content[i]);
				}
				items = buffer;
				content = strs;
			}
			else
			{
				for (unsigned i = 0; i < resultXY.size(); ++i)
				{
					items.erase(items.begin() + resultXY[i]);
					content.erase(content.begin() + resultXY[i]);
				}
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
		std::string new_one = "t:" + std::to_string(item.type) + cmm::SSPACE
			+ "c:" + std::to_string(item.chosen) + cmm::SSPACE
			+ "x:" + std::to_string(item.position.x) + cmm::SSPACE
			+ "y:" + std::to_string(item.position.y) + cmm::SSPACE
			+ "id:" + std::to_string(item.ID) + cmm::SSPACE
			+ "ai:" + item.ai + cmm::SNEWLINE;
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

			std::string new_one = "t:" + std::to_string(item.type) + cmm::SSPACE
				+ "c:" + std::to_string(item.chosen) + cmm::SSPACE
				+ "x:" + std::to_string(item.position.x) + cmm::SSPACE
				+ "y:" + std::to_string(item.position.y) + cmm::SSPACE
				+ "id:" + std::to_string(item.ID) + cmm::SSPACE
				+ "ai:" + item.ai + cmm::SNEWLINE;
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
