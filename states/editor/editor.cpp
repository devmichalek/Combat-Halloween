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

	chat.free();
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
	chat.setStyleWhitish();
	chat.reset();
}



void Editor::load(const float &screen_w, const float &screen_h)
{
	free();

	navigation.load(screen_w, screen_h);
	editorFileManager.load(screen_w, screen_h);
	editorAction.load(screen_w, screen_h);

	// Set chat.
	chat.load(screen_w, screen_h);
	chat.setStyleWhitish();
}

void Editor::handle(const sf::Event &event)
{
	if (!isState())
	{
		if (!chat.isActive())
		{
			editorFileManager.handle(event);

			if (!editorFileManager.isActive())
			{
				editorAction.handle(event);
			}

			navigation.handle(event);
		}

		if (!editorFileManager.isActive())
			chat.handle(event);
	}
}

void Editor::draw(sf::RenderWindow* &window)
{
	navigation.drawBG(window);
	editorAction.draw(window);
	navigation.draw(window);
	editorFileManager.draw(window);
	chat.draw(window);
}

void Editor::mechanics(const double &elapsedTime)
{
	set();

	// fades(elapsedTime);

	if (!isState())
	{
		chat.mechanics(elapsedTime);
		if (chat.isCommand())
		{
			if (chat.compCommand("@close") || chat.compCommand("@exit"))
			{
				exit = true;
			}
			else if (chat.compCommand("@menu") || chat.compCommand("@home"))
			{
				navigation.setHome();
			}
			else if (chat.compCommand("@levelmenu"))
			{
				navigation.setLevelMenu();
			}
			else if (chat.compCommand("@play"))
			{
				navigation.setPlay();
			}
		}
		

		// Back to menu.
		if (navigation.isHome())
		{
			chat.isActive() = false;
			prev = true;
		}

		// Back to levelmenu.
		else if (navigation.isLevelMenu())
		{
			chat.isActive() = false;
			prev = true;
			next = true;
		}

		// Start test game.
		else if (navigation.isPlay())
		{
			chat.isActive() = false;
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
		state = cmm::STATES::PLATFORM;
	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}