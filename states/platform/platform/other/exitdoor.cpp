#include "exitdoor.h"
#include "loading.h"

pla::ExitDoor::ExitDoor()
{
	free();
}

pla::ExitDoor::~ExitDoor()
{
	free();
}

void pla::ExitDoor::free()
{
	screen_w = 0;
	screen_h = 0;

	if (!bg.empty())
	{
		for (auto &it : bg)
		{
			delete it;
			it = nullptr;
		}
		bg.clear();
	}

	reference = sf::Vector2f(0.0f, 0.0f);
}

void pla::ExitDoor::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	for (int i = 0; i < 9; ++i)
		bg.push_back(new cmm::Sprite);

	Loading::add(bg[0]->load("images/platform/tiles/0.png"));
	Loading::add(bg[1]->load("images/platform/tiles/1.png"));
	Loading::add(bg[2]->load("images/platform/tiles/2.png"));
	Loading::add(bg[3]->load("images/platform/tiles/9.png"));
	Loading::add(bg[4]->load("images/platform/tiles/10.png"));
	Loading::add(bg[5]->load("images/platform/tiles/11.png"));
	Loading::add(bg[6]->load("images/platform/tiles/9.png"));
	Loading::add(bg[7]->load("images/platform/tiles/10.png"));
	Loading::add(bg[8]->load("images/platform/tiles/11.png"));
	if (Loading::isError())	return;

	Loading::add(door.load("images/platform/platform/door.png"));
	if (Loading::isError())	return;
}

void pla::ExitDoor::draw(sf::RenderTexture &rt, const float &x, const float &y)
{
	position(x, y);

	for (auto & it : bg)
		rt.draw(*it);
	rt.draw(door);
}

void pla::ExitDoor::read(std::string &str)
{
	int x = boost::lexical_cast<int>(str.substr(str.find("x:") + 2, str.find(" y:") - (str.find("x:") + 2)));
	int y = boost::lexical_cast<int>(str.substr(str.find("y:") + 2, str.find(" id:") - (str.find("y:") + 2)));
	reference = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

void pla::ExitDoor::position(const float &x, const float &y)
{
	bg[0]->setPosition(reference.x, reference.y);

}