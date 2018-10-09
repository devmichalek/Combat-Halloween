#include "editor.h"
#include "scontent.h"
#include "core.h" // StaticCore

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
		// ...
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
	editorAction.reset();
}



void Editor::load(const float &screen_w, const float &screen_h)
{
	free();

	navigation.load(screen_w, screen_h);
	editorFileManager.load(screen_w, screen_h);
	editorAction.load(screen_w, screen_h);
}

void Editor::handle(const sf::Event &event)
{
	if (!isState())
	{
		editorFileManager.handle(event);

		if (!editorFileManager.isActive())
		{
			editorAction.handle(event);
		}

		navigation.handle(event);
	}
}

void Editor::draw(sf::RenderWindow* &window)
{
	navigation.drawBG(window);
	editorAction.draw(window);
	navigation.draw(window);
	editorFileManager.draw(window);
}

void Editor::mechanics(const double &elapsedTime)
{
	set();

	// fades(elapsedTime);

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
			editorAction.mechanics(elapsedTime);
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