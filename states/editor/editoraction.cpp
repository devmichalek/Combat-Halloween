#include "editoraction.h"
#include "loading.h"

EditorAction::EditorAction()
{
	free();
}

EditorAction::~EditorAction()
{
	free();
}

void EditorAction::free()
{

}

void EditorAction::reset()
{
	factory.reset();
	grid.reset();
	info.reset();
}



void EditorAction::load(const float &screen_w, const float &screen_h)
{
	free();

	factory.load(screen_w, screen_h);
	grid.load(screen_w, screen_h);
	info.load(screen_w, screen_h);
	if (Loading::isError())	return;
	reset();
}

void EditorAction::handle(const sf::Event &event)
{
	if (!grid.handle(event))	// if arrows are in use don't let user to put an entity
	{
		if (factory.handle(event, grid.getAddX(), grid.getAddY()))
			factory.setPosition(grid.getX(), grid.getY());
	}
}

void EditorAction::draw(sf::RenderWindow* &window)
{
	factory.draw(window, grid.getAddX(), grid.getAddY());
	grid.draw(window);
	info.draw(window);
}

void EditorAction::mechanics(const double &elapsedTime)
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
