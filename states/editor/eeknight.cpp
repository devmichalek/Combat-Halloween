#include "eeknight.h"
#include "loading.h"

ee::Knight::Knight()
{
	free();
}

ee::Knight::~Knight()
{
	free();
}

void ee::Knight::free()
{
	reset();
	screen.x = screen.y = 0;
}

void ee::Knight::reset()
{
	item.reset();
}

bool ee::Knight::isModified()
{
	return false; // change if knight board is ready
}

void ee::Knight::setActive(bool active)
{
	this->active = active; // change if knight board is ready
}

ee::Item ee::Knight::getItem()
{
	// add ai changes here later..
	return item;
}

bool ee::Knight::checkCollision(sf::Vector2i &mouse)
{
	oblong.left = mouse.x;
	oblong.top = mouse.y + (!wholeCollision ? rect.height : 0);
	oblong.width = wholeCollision ? rect.width : 1;
	oblong.height = wholeCollision ? rect.height : 1;
	rect.left = item.position.x;
	rect.top = item.position.y;

	return rect.intersects(oblong);
}

void ee::Knight::load(sf::Vector2f &screen, int amount)
{
	free();
	this->screen = screen;

	// Load sprites. (1)
	for (int i = 0; i < amount; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/knight/" + std::to_string(i) + ".png", 10));
		if (Loading::isError())	return;
		sprites[i]->setScale(0.45f, 0.45f);
		sprites[i]->setAlpha(MAX_ALPHA);
	}

	rect.width = static_cast<int>(sprites[0]->getWidth());
	rect.height = static_cast<int>(sprites[0]->getHeight());
}

void ee::Knight::handle(const sf::Event &event)
{
	// ...
}

void ee::Knight::draw(sf::RenderWindow* &window, sf::Vector2i &add)
{
	if (item.position.x != -1 && item.position.y != -1)
	{
		sprites[0]->setPosition(item.position.x + add.x, -(item.position.y + add.y) + screen.y);
		window->draw(*sprites[0]);
	}
}

void ee::Knight::mechanics(const double &elapsedTime)
{

}

bool ee::Knight::add(Item &data)
{
	if (!data.ai.empty())
	{

	}
	else
		item.ai = "";

	item.ID = data.ID;
	item.position = data.position;
	item.type = cmm::Kind::KNIGHT;
	item.chosen = data.chosen;

	return true;
}

bool ee::Knight::remove(sf::Vector2i &mouse)
{
	if (checkCollision(mouse))
	{
		item.ai = "";
		item.position = sf::Vector2i(-1, -1);
		return true;
	}

	return false;
}

bool ee::Knight::unfold(sf::Vector2i &mouse)
{
	return false; // change later
}