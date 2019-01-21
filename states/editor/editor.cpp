#include "editor.h"
#include "scontent.h"
#include "loading.h"

Editor::Editor()
{
	free();
}

Editor::~Editor()
{
	free();
}

void Editor::free()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;
}

void Editor::set()
{
	if (!loaded)
	{
		fileManager.reset();
		loaded = true;
	}
}

bool Editor::isReady() const
{
	return true;
}

void Editor::reset()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;

	navigation.reset();
	options.reset();
	fileManager.reset();
	factory.reset();
	grid.reset();
	info.reset();
}



void Editor::load(const float &screen_w, const float &screen_h)
{
	free();

	navigation.load(screen_w, screen_h);
	options.load(screen_w, screen_h);
	fileManager.load(screen_w, screen_h);
	factory.load(screen_w, screen_h);
	grid.load(screen_w, screen_h);
	info.load(screen_w, screen_h);

	if (Loading::isError())	return;
	reset();
}

void Editor::handle(const sf::Event &event)
{
	if (!isState())
	{
		if (!options.isActive() && !factory.isActive())
			fileManager.handle(event);

		if (!fileManager.isActive() && !factory.isActive())
			options.handle(event);

		bool allowFactory = true;
		if (!fileManager.isActive() && !options.isActive() && !factory.isActive())
		{
			navigation.handle(event);
			allowFactory = !grid.handle(event);
		}

		if (!fileManager.isActive() && !options.isActive() && allowFactory)
		{
			if (factory.handle(event, grid.getAdd()))
				factory.setPosition(grid.getX(), grid.getY());
		}
	}
}

void Editor::draw(sf::RenderWindow* &window)
{
	navigation.drawBG(window);
	factory.draw(window, grid.getAdd(), grid.isActive());
	grid.draw(window);
	info.draw(window);
	navigation.draw(window);
	options.drawButton(window);
	fileManager.draw(window);
	options.draw(window);
	factory.print(window);
}

void Editor::mechanics(const double &elapsedTime)
{
	set();

	if (!isState())
	{
		if (fileManager.isFileOpen())
			navigation.disablePlay(!fileManager.isFileUnsave());

		// Back to menu.
		if (navigation.isHome())
		{
			if (fileManager.isFileUnsave())
			{
				if (navigation.homeHasChanged())
					fileManager.openMessageBoard();

				if (fileManager.isYes())
					prev = true;
				else if (fileManager.isNo())
					navigation.disableHome(false);
			}
			else
				prev = true;
		}

		// Back to levelmenu.
		else if (navigation.isLevelMenu())
		{
			if (fileManager.isFileUnsave())
			{
				if (navigation.levelMenuHasChanged())
					fileManager.openMessageBoard();

				if (fileManager.isYes())
				{
					prev = true;
					next = true;
				}
				else if (fileManager.isNo())
					navigation.disableLevelMenu(false);
			}
			else
			{
				prev = true;
				next = true;
			}
		}

		// Start test game.
		else if (navigation.isPlay())
			next = true;

		if (options.isActive())
			return;

		fileManager.mechanics(elapsedTime);
		if (!fileManager.isActive())
		{
			if (factory.isChange())
			{
				info.set(factory.getType(), factory.getChosen());
				info.isGridNeeded() ? grid.turnOn() : grid.turnOff();
			}

			grid.mechanics(factory.isDeleteMode());
			factory.setPosition(grid.getX(), grid.getY());
			factory.mechanics(elapsedTime);
		}
		factory.circulation();
	}
}

void Editor::setState(int &state)
{
	if (isPrev() && isNext())
	{
		reset();
		state = cmm::STATES::LEVELMENU;
	}
	else if (isPrev())
	{
		reset();
		state = cmm::STATES::MENU;
	}
	else if (isNext())
	{
		SContent::type = SContent::TYPE::EDITOR;
		SContent::path = cmm::SEMPTY;
		reset();
		state = cmm::STATES::SIMULATOR;
	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}