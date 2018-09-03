#include "editor.h"

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

	//editor_buttons.free();
	// editor_information.free();
	//editor_details.free();
	// editor_options.free();
	// tiles_editor.free();
	chat.free();
}

void Editor::set()
{
	if (!loaded)
	{

		// Sound.
		// bool soundPlayable = cmm::Sound::getGlobalPlayable();
		float soundVolume = cmm::Sound::getGlobalVolume();
		navigation.setVolume(soundVolume);

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
	//tiles_editor.reset();
	//editor_details.setGrid(tiles_editor.getGrid());
	// editor_details.setType(tiles_editor.getType());
	// editor_details.setChosen(tiles_editor.getChosen());
	chat.reset();
}



void Editor::load(const float &screen_w, const float &screen_h)
{
	free();

	navigation.load(screen_w, screen_h);
	editorFileManager.load(screen_w, screen_h);
	editorAction.load(screen_w, screen_h);
	// Set editor information.
	// editor_information.load(screen_w, screen_h);

	// Set editor details.
	// editor_details.load(screen_w, screen_h);

	// Set editor options.
	// editor_options.load(screen_w, screen_h);

	// Set tiles editor.
	// tiles_editor.load(screen_w, screen_h);

	// Set chat.
	chat.load(screen_w, screen_h);
	chat.setCommandColor(sf::Color(0xFF, 0xFF, 0xFF));
	chat.setTypicalColor(sf::Color(0xBA, 0xBA, 0xBA));
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
			if (chat.findCommand("@menu"))
			{
				navigation.setHome();
			}
			else if (chat.findCommand("@levelmenu"))
			{
				navigation.setLevelMenu();
			}
			else if (chat.findCommand("@play"))
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

		// ctrl - z
		// editorFileManager.pop();

		// new content
		// editorFileManager.push();

		/*tiles_editor.mechanics(elapsedTime);
		tiles_editor.setRubbish(editor_buttons.isDelete());

		if (!editor_information.isActive())
		{
			if (editor_buttons.isAnything())
			{
				if (editor_buttons.getInfo() != " ")
				{
					editor_information.setInfo(editor_buttons.getInfo());
					editor_information.setWorldname(editor_buttons.getWorldname(editor_details.getName()));
					editor_information.setAsVisible();
				}
			}
		}*/

		//if (editor_buttons.isOptions())	// Show options.
		//{
		//	if (editor_options.getStatus() == 0)
		//	{
		//		editor_options.setStatus(1);
		//	}
		//}
		//else if (editor_buttons.isName())	// Name.
		//{
		//	if (editor_details.getNameStatus() == 0)
		//	{
		//		editor_details.setNameStatus(1);
		//	}
		//}
		//else if (editor_buttons.isDelete())	// Delete mode.
		//{
		//	tiles_editor.reset();
		//}

		//// Reset by action.
		//if (editor_options.getStatus() == 2)
		//{
		//	editor_buttons.reset();
		//	editor_options.setStatus(0);
		//}
		//else if (editor_details.getNameStatus() == 2)
		//{
		//	editor_buttons.reset();
		//	editor_details.setNameStatus(0);
		//}

		//// Answers.
		//if (editor_information.answerYes())
		//{
		//	if (editor_buttons.isHome())	// Back to menu.
		//	{
		//		back = true;
		//		chat.isOpen() = false;
		//	}
		//	else if (editor_buttons.isSave())	// Save.
		//	{
		//		tiles_editor.save(editor_details.getName());
		//	}
		//	else if (editor_buttons.isLoad())	// Load.
		//	{
		//		tiles_editor.load(editor_details.getName());
		//	}
		//	else if (editor_buttons.isPlay())	// Test playing.
		//	{
		//		play = true;
		//		chat.isOpen() = false;
		//	}
		//	else if (editor_buttons.isUpload())	// Upload world.
		//	{

		//	}
		//}
		//else if (editor_information.answerNo())
		//{
		//	editor_buttons.reset();
		//}

		//editor_details.mechanics(elapsedTime);
	}
}