#include "core.h"
#include "editor.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
Editor* editor = new Editor;

enum STATES
{
	MENU = 3,
	LEVELMENU,
	PLATFORM,
	TABLE,
	EDITOR,
	DEFAULT
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = EDITOR;
	editor->load(core->getWidth(), core->getHeight());

	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
			{
				core->open = false;
			}

			switch (core->state)
			{
			case EDITOR: editor->handle(core->getEvent()); 	break;
			}
		}

		if (core->state == EDITOR)
		{
			editor->mechanics(core->getElapsedTime());
			editor->draw(core->getWindow());

			if (editor->isPrev() && editor->isNext())
			{
				editor->reset();
				core->state = MENU;
			}
			else if (editor->isPrev())
			{
				editor->reset();
				core->state = LEVELMENU;
			}
			else if (editor->isNext())
			{
				editor->reset();
				core->state = PLATFORM;
			}
			else if (editor->isExit())	core->open = false;
		}

		core->display();
	}

	delete core;
	delete editor;
	return 0;
}