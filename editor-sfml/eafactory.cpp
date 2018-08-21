#include "eafactory.h"

EAFactory::EAFactory()
{
	free();
}

EAFactory::~EAFactory()
{
	free();
}

void EAFactory::free()
{
	reset();

	if (!amounts.empty())
		amounts.clear();

	if (!factory.empty())
	{
		for(auto &it : factory)
		{
			if (!it.empty())
			{
				for (auto &jt : it)
				{
					delete jt;
					jt = nullptr;
				}

				it.clear();
			}
		}

		factory.clear();
		factory.shrink_to_fit();
	}
}

void EAFactory::reset()
{
	type = VOID;
	chosen = 0;
}

void EAFactory::load(const float& screen_w, const float& screen_h)
{
	free();

	float scale = 0.51;

	// Knight
	amounts.push_back(1);
	factory.push_back(std::vector<cmm::Sprite*>());
	factory[KNIGHT].push_back(new cmm::Sprite());
	factory[KNIGHT][0]->load("images/platform/knight/0.png", 10);
	factory[KNIGHT][0]->setScale(scale, scale);

	// Tile
	amounts.push_back(21);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[TILE]; ++i)
	{
		factory[TILE].push_back(new cmm::Sprite());
		factory[TILE][i]->load("images/platform/tiles/" + std::to_string(i) + ".png");
		factory[TILE][i]->setScale(scale, scale);
	}

	// Unvisible Tile
	amounts.push_back(21);
	factory.push_back(std::vector<cmm::Sprite*>());

	// Landscape
	amounts.push_back(14);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[LANDSCAPE]; ++i)
	{
		factory[LANDSCAPE].push_back(new cmm::Sprite());
		factory[LANDSCAPE][i]->load("images/platform/landscape/" + std::to_string(i) + ".png");
		factory[LANDSCAPE][i]->setScale(scale, scale);
	}
}

bool EAFactory::handle(const sf::Event &event)
{
	if (type != VOID)
	{
		if (event.type == sf::Event::MouseWheelMoved)
		{
			float m = event.mouseWheel.delta;
			if (m > 0)
			{
				if (chosen < amounts[type] - 1)
				{
					++chosen;
					change = true;
				}
			}
			else
			{
				if (chosen > 0)
				{
					--chosen;
					change = true;
				}
			}
	}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;

		if (code == sf::Keyboard::Escape)
			reset();

		change = true;

		// CHANGING CHOSEN
		if (code == sf::Keyboard::Z && chosen > 0)
			--chosen;
		else if (code == sf::Keyboard::X && chosen != 0)
			chosen /= 2;
		else if (code == sf::Keyboard::C && type != VOID && chosen < amounts[type] - 1)
			++chosen;

		// CHANGING TYPE
		else if (code == sf::Keyboard::A)
		{
			--type;
			chosen = 0;
		}
		else if (code == sf::Keyboard::S)
		{
			type = -1;
			chosen = 0;
		}
		else if (code == sf::Keyboard::D && type < AMOUNT)
		{
			++type;
			chosen = 0;
		}
		else
			change = false;
	}

	return change;
}

void EAFactory::draw(sf::RenderWindow* &window)
{
	if (type == VOID)
		return;

	int t = type != UNVISIBLE_TILE ? type : TILE;
	type == UNVISIBLE_TILE ? factory[t][chosen]->setAlpha(0xFF / 2) : factory[t][chosen]->setAlpha(0xFF);
	
	window->draw(factory[t][chosen]->get());
}



void EAFactory::setPosition(float x, float y)
{
	if (type == VOID)
		return;

	int t = type != UNVISIBLE_TILE ? type : TILE;
	factory[t][chosen]->setPosition(x, y);
}

bool EAFactory::isGridChange()
{
	if (change)
	{
		change = false;
		return true;
	}

	return false;
}

bool EAFactory::isGridNeeded()
{
	bool grid = false;

	if (type == KNIGHT)									grid = false;
	else if (type == TILE || type == UNVISIBLE_TILE)	grid = true;
	else if (type == LANDSCAPE)							grid = true;
	else if (type == FOE)								grid = false;
	else if (type == LIGHTPOINT)						grid = false;

	return grid;
}

std::string EAFactory::getTypeStr()
{
	std::string line = "None";

	if (type == KNIGHT)					line = "Character";
	else if (type == TILE)				line = "Tiles";
	else if (type == UNVISIBLE_TILE)	line = "Unvisible Tiles";
	else if (type == LANDSCAPE)			line = "Landscape";
	else if (type == FOE)				line = "Foes";
	else if (type == LIGHTPOINT)		line = "Light points";

	return line;
}

std::string EAFactory::getChosenStr()
{
	std::string line = "";

	if (type == KNIGHT)
	{
		line = "Knight";
	}
	else if (type == TILE || type == UNVISIBLE_TILE)
	{
		switch (chosen)
		{
		case 0: line += "Left Solid Grass"; 			break;
		case 1: line += "Middle Solid Grass"; 			break;
		case 2: line += "Right Solid Grass"; 			break;

		case 3: line += "Left Hill Grass"; 				break;
		case 4: line += "Right Hill Grass"; 			break;

		case 5: line += "Left Hovering Grass"; 			break;
		case 6: line += "Middle Hovering Grass"; 		break;
		case 7: line += "Right Hovering Grass";			break;
		case 8: line += "Single Hovering Grass"; 		break;

		case 9: line += "Left Ground Border"; 			break;
		case 10: line += "Soil";						break;
		case 11: line += "Right Ground Border"; 		break;

		case 12: line += "Left Bottom Ground Border"; 	break;
		case 13: line += "Middle Bottom Ground Border";	break;
		case 14: line += "Right Bottom Ground Border"; 	break;

		case 15: line += "Left Hill Soil"; 				break;
		case 16: line += "Right Hill Soil";				break;
		}
	}
	else if (type == LANDSCAPE)
	{
		switch (chosen)
		{
		case 0: line += "Skull With Bone"; 		break;
		case 1: line += "Skull"; 				break;
		case 2: line += "Three Bones"; 			break;
		case 3: line += "Two Bones"; 			break;

		case 4: line += "Wooden Arrow"; 		break;
		case 5: line += "Wooden Sign"; 			break;

		case 6: line += "Round Bush"; 			break;
		case 7: line += "Spiky Bush"; 			break;

		case 8: line += "Wooden Chest"; 		break;
		case 9: line += "Bush Without Leaves"; 	break;
		case 10: line += "Tree Without Leaves";	break;

		case 11: line += "Remains"; 			break;
		case 12: line += "Tombstone"; 			break;
		case 13: line += "Cross"; 				break;
		}
	}
	else if (type == FOE)
	{
		switch (chosen)
		{
		case 0: line += "Skeleton";	 break;
		case 1: line += "Vampire";	 break;
		case 2: line += "Zombie";	 break;
		}
	}
	else if (type == LIGHTPOINT)
	{
		line = "Light bulb";
	}
	else
		line = "None";

	return line;
}