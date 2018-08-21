#include "editoraction.h"

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
	grid.setGridStr();
	grid.setChosenStr(factory.getChosenStr());
	grid.setCategoryStr(factory.getTypeStr());
}



void EditorAction::load(const float &screen_w, const float &screen_h)
{
	free();

	int width = 64;

	factory.load(screen_w, screen_h);
	grid.load(screen_w, screen_h, width);

	reset();
}

void EditorAction::handle(const sf::Event &event)
{
	if (factory.handle(event))
		factory.setPosition(grid.getX(), grid.getY());

	grid.handle(event);
}

void EditorAction::draw(sf::RenderWindow* &window)
{
	factory.draw(window);
	grid.draw(window);
}

void EditorAction::mechanics(const double &elapsedTime)
{
	if (factory.isGridChange())
	{
		factory.isGridNeeded() ? grid.turnOn() : grid.turnOff();
		grid.setGridStr();
		grid.setChosenStr(factory.getChosenStr());
		grid.setCategoryStr(factory.getTypeStr());
	}

	factory.setPosition(grid.getX(), grid.getY());
}
