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
		editorFileManager.reset();
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
	editorFileManager.reset();
	factory.reset();
	grid.reset();
	info.reset();
}



void Editor::load(const float &screen_w, const float &screen_h)
{
	free();

	navigation.load(screen_w, screen_h);
	editorFileManager.load(screen_w, screen_h);
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
		editorFileManager.handle(event);

		if (!editorFileManager.isActive())
		{
			if (!grid.handle(event))	// if arrow buttons are in use don't let user to put an entity
			{
				if (factory.handle(event, grid.getAdd()))
					factory.setPosition(grid.getX(), grid.getY());
			}
		}

		navigation.handle(event);
	}
}

void Editor::draw(sf::RenderWindow* &window)
{
	navigation.drawBG(window);
	factory.draw(window, grid.getAdd());
	grid.draw(window);
	info.draw(window);
	navigation.draw(window);
	editorFileManager.draw(window);
}

void Editor::mechanics(const double &elapsedTime)
{
	set();

	if (!isState())
	{
		navigation.disablePlay(editorFileManager.isFileOpen());

		if (editorFileManager.isFileUnsave())
		{
			navigation.disablePlay(false);
		}

		// Back to menu.
		if (navigation.isHome())
		{
			if (editorFileManager.isFileUnsave())
			{
				if (navigation.homeHasChanged())
					editorFileManager.openMessageBoard();

				if (editorFileManager.isYes())
					prev = true;
				else if (editorFileManager.isNo())
					navigation.disableHome(false);
			}
			else
				prev = true;
		}

		// Back to levelmenu.
		else if (navigation.isLevelMenu())
		{
			if (editorFileManager.isFileUnsave())
			{
				if (navigation.levelMenuHasChanged())
					editorFileManager.openMessageBoard();

				if (editorFileManager.isYes())
				{
					prev = true;
					next = true;
				}
				else if (editorFileManager.isNo())
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
		{
			next = true;
		}


		editorFileManager.mechanics(elapsedTime);

		if (!editorFileManager.isActive())
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
		SContent::path = "";
		reset();
		state = cmm::STATES::SIMULATOR;
	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}