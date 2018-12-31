#include "coxing.h"
#include "converter.h"
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

std::vector<int> cmm::Coxing::keys;

cmm::Coxing::Coxing()
{
	//...
}

cmm::Coxing::~Coxing()
{
	//...
}

cmm::Keys::Keys()
{
	//...
}

cmm::Keys::~Keys()
{
	//...
}

void cmm::Keys::setKey(int which, int newKey)
{
	keys[which] = newKey;
}

int cmm::Keys::getKey(int which)
{
	return keys[which];
}

int cmm::Keys::getActiveKeysAmount()
{
	return KEY_ACTION::JUMP_ATTACK;
}

void cmm::Keys::resetKeys()
{
	keys.clear();

	for (int i = 0; i < KEY_ACTION::JUMP_ATTACK; ++i)
		keys.push_back(0);

	// Reset values.
	keys[MOVE_LEFT] = 71;
	keys[MOVE_RIGHT] = 72;
	keys[JUMP] = 73;
	keys[ATTACK] = 23;
	keys[SHIELD] = 25;

	// Overwrite / Save (force) to file.
	saveKeys();
}

void cmm::Keys::saveKeys()
{
	// Create directory if it does not exist
	if (!boost::filesystem::is_directory("local"))
		boost::filesystem::create_directories("local");

	std::ofstream file;
	file.open("local/keys.settings");

	for (auto it : keys)
	{
		file << std::to_string(it);
		if (it != *(keys.end() - 1))
			file << std::endl;
	}

	file.close();	// not needed actually
}

void cmm::Keys::loadKeys()
{
	keys.clear();

	std::fstream file;
	file.open("local/keys.settings");
	if (file.bad())	// file does not exist -> reset keys
	{
		file.close();
		resetKeys();
	}
	else
	{
		std::string line = cmm::SEMPTY;
		while (std::getline(file, line))
		{
			int newKey = boost::lexical_cast<int>(line);
			if (!isPossibleKey(newKey))
			{
				file.close();
				resetKeys();
				break;
			}

			keys.push_back(newKey);
		}

		if (keys.size() < KEY_ACTION::JUMP_ATTACK) // file is broken?
		{
			file.close();
			resetKeys();
		}

	}
	file.close();
}

bool cmm::Keys::isPossibleKey(const int &code)
{
	if (code == 14 || code == 15)	// pause key or chat key
	{
		return false;
	}
	if (code > -1 && code <= 35)	// a .. z and numbers
	{
		return true;
	}
	if (code >= 75 && code <= 84)	// numbers
	{
		return true;
	}
	if (code >= 71 && code <= 74)	// arrows
	{
		return true;
	}
	if (code == 57)					// space
	{
		return true;
	}
	if (code >= 37 && code <= 43 && code != 40)	// lctrl, lshift, lalt, rctrl, rshift, ralt
	{
		return true;
	}

	return false;
}