#include "eainfo.h"
#include "loading.h"
#include "definitions.h"

EAInfo::EAInfo()
{
	free();
}

EAInfo::~EAInfo()
{
	free();
}

void EAInfo::free()
{
	type = VOID;
	chosen = 0;

	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
			it = nullptr;
		}

		texts.clear();
	}
}

void EAInfo::reset()
{
	type = VOID;
	chosen = 0;

	set(type, chosen);
}



void EAInfo::load(const float &screen_w, const float &screen_h)
{
	free();

	for (int i = 0; i < TEXTS::SIZE; ++i)
	{
		texts.push_back(new cmm::Text);
		Loading::add(texts[i]->setFont(cmm::JCANDLE_FONT_PATH));
		if (Loading::isError())	return;
		texts[i]->setSize(screen_w / 60);
		texts[i]->setAlpha(MAX_ALPHA);
		i % 2 == 0 ? texts[i]->setFillColor(cmm::LOCKED_COLOR) : texts[i]->setFillColor(cmm::LOADING_COLOR);
	}
	texts[GRIDFORM]->setText("Grid:");
	texts[CHOSENFORM]->setText("Chosen:");
	texts[CATEGORYFORM]->setText("Category:");
	texts[DESCRIPTIONFORM]->setText("Description:");
	texts[OPTIONSFORM]->setText("Options:");
	texts[GRIDFORM]->setPosition(screen_w / 8, screen_h / 144);
	texts[CHOSENFORM]->setPosition(texts[GRIDFORM]->getX(), texts[GRIDFORM]->getBot() + screen_h / 144);
	texts[CATEGORYFORM]->setPosition(texts[GRIDFORM]->getX(), texts[CHOSENFORM]->getBot() + screen_h / 144);
	texts[OPTIONSFORM]->setPosition(screen_w / 3, screen_h / 144);
	texts[DESCRIPTIONFORM]->setPosition(texts[OPTIONSFORM]->getX(), texts[OPTIONSFORM]->getBot() + screen_h / 72);
	
	set(type, chosen);
}

void EAInfo::draw(sf::RenderWindow* &window)
{
	for (auto &it : texts)
		window->draw(*it);
}



void EAInfo::set(const int &newType, const int &newChosen)
{
	type = newType;
	chosen = newChosen;

	setChosenText(getChosenStr());
	setCategoryText(getTypeStr());
	setDescriptionText(getDescriptionStr());
	setOptionsText(areOptionsGetable());
	setGridText(isGridNeeded());
}



void EAInfo::setChosenText(std::string line)
{
	texts[CHOSEN]->setText(line);
	texts[CHOSEN]->setPosition(texts[CATEGORYFORM]->getRight() + TILE_FULL_WIDTH / 4, texts[CHOSENFORM]->getY());
}

void EAInfo::setCategoryText(std::string line)
{
	texts[CATEGORY]->setText(line);
	texts[CATEGORY]->setPosition(texts[CATEGORYFORM]->getRight() + TILE_FULL_WIDTH / 4, texts[CATEGORYFORM]->getY());
}

void EAInfo::setDescriptionText(std::string line)
{
	texts[DESCRIPTION]->setText(line);
	texts[DESCRIPTION]->setPosition(texts[DESCRIPTIONFORM]->getX(), texts[DESCRIPTIONFORM]->getY());
}

void EAInfo::setOptionsText(bool getable)
{
	getable ? texts[OPTIONS]->setText("Available") : texts[OPTIONS]->setText("Unsupported");
	getable ? texts[OPTIONS]->setFillColor(cmm::GREEN_COLOR) : texts[OPTIONS]->setFillColor(cmm::ERROR_COLOR);
	texts[OPTIONS]->setPosition(texts[OPTIONSFORM]->getRight() + TILE_FULL_WIDTH / 4, texts[OPTIONSFORM]->getY());
}

void EAInfo::setGridText(bool grid)
{
	grid ? texts[GRID]->setText("On") : texts[GRID]->setText("Off");
	grid ? texts[GRID]->setFillColor(cmm::GREEN_COLOR) : texts[GRID]->setFillColor(cmm::ERROR_COLOR);
	texts[GRID]->setPosition(texts[CATEGORYFORM]->getRight() + TILE_FULL_WIDTH / 4, texts[GRIDFORM]->getY());
}




std::string EAInfo::getTypeStr()
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

std::string EAInfo::getChosenStr()
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
		case 0: line += "Left Solid Grass";		break;
		case 1: line += "Middle Solid Grass"; 	break;
		case 2: line += "Right Solid Grass"; 	break;

		case 3: line += "Left Hill Grass"; 	break;
		case 4: line += "Right Hill Grass"; break;

		case 5: line += "Left Hovering Grass"; 		break;
		case 6: line += "Middle Hovering Grass";	break;
		case 7: line += "Right Hovering Grass";		break;
		case 8: line += "Single Hovering Grass";	break;

		case 9: line += "Left Ground Border"; 	break;
		case 10: line += "Soil";				break;
		case 11: line += "Right Ground Border"; break;

		case 12: line += "Left Bot Ground Border"; 		break;
		case 13: line += "Middle Bot Ground Border";	break;
		case 14: line += "Right Bot Ground Border";		break;

		case 15: line += "Left Hill Soil"; 	break;
		case 16: line += "Right Hill Soil";	break;

		case 17: line += "Water Waves";	break;
		case 18: line += "Water";		break;
		case 19: line += "Acid Waves";	break;
		case 20: line += "Acid";		break;
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

std::string EAInfo::getDescriptionStr()
{
	std::string tab = "\t\t\t\t\t";
	std::string line = tab + "None\n";

	if (type == KNIGHT)
		line = tab + "Knight is one and only character.\nGame starts at knight's (x, y) positon.";
	else if (type == TILE)
		line = tab + "Tiles are the linchpin of the game.\nThese blocks interacts with knight.";
	else if (type == UNVISIBLE_TILE)
		line = tab + "Unvisible tiles are getting visible\nafter the knight is standing on them.";
	else if (type == LANDSCAPE)
		line = tab + "Still Life objects do not interact\nwith anything. They just there.";
	else if (type == FOE)
		line = tab + "Foes that trying their best to combat\nknight and not let him finish the game.";
	else if (type == LIGHTPOINT)
		line = tab + "Here the lights come to take\nan action and spotlight the darkness of the halloween.";

	return line;
}

bool EAInfo::areOptionsGetable()
{
	if (type == VOID)			return false;
	else if (type == TILE)		return false;
	//else if (type == LANDSCAPE)	return false;

	return true;
}

bool EAInfo::isGridNeeded()
{
	if (type == TILE)					return true;
	else if (type == UNVISIBLE_TILE)	return true;

	return false;
}