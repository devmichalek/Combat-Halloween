#include "movingbg.h"
#include "loading.h"

pla::MovingBG::MovingBG()
{
	free();
}

pla::MovingBG::~MovingBG()
{
	free();
}

void pla::MovingBG::free()
{
	screen_w = 0;
	screen_h = 0;
	velocity = 0;

	if (!types.empty())
	{
		types.clear();
	}

	if (!fs.empty())
	{
		fs.clear();
	}

	if (!sprites.empty())
	{
		for (auto &it : sprites)
		{
			delete it;
			it = nullptr;
		}

		sprites.clear();
	}
}



void pla::MovingBG::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	velocity = 30; // 30 px per sec and 15 px per sec for sec bg

	for (unsigned i = 0; i < 3; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load(("images/platform/background/" + std::to_string(i) + ".png").c_str()));
		if (Loading::isError()) return;
		sprites[i]->setScale(screen_w / 2500, screen_h / 1440);
	}

	sprites[1]->setPosition(0, 0);
	sprites[1]->setPosition(0, screen_h - sprites[1]->getHeight() - 411 * screen_h / 1440);
	sprites[2]->setPosition(0, screen_h - sprites[2]->getHeight());

	fs.push_back(sf::Vector2f(0, 0));
	fs.push_back(sf::Vector2f(screen_w, sprites[1]->getY()));
	fs.push_back(sf::Vector2f(0, sprites[1]->getY()));
	fs.push_back(sf::Vector2f(screen_w, sprites[2]->getY()));
	fs.push_back(sf::Vector2f(0, sprites[2]->getY()));

	types.push_back(0);
	types.push_back(1);
	types.push_back(1);
	types.push_back(2);
	types.push_back(2);
}

void pla::MovingBG::draw(sf::RenderTexture &rt)
{
	for (unsigned i = 0; i < fs.size(); ++i)
	{
		sprites[types[i]]->setPosition(fs[i].x, fs[i].y);
		rt.draw(*sprites[types[i]]);
	}
}

void pla::MovingBG::mechanics(const float &elapsedTime, const char &direction)
{
	for (unsigned i = 1; i < 3; ++i)
	{
		fs[i].x += -velocity * 0.45f * elapsedTime * direction;
		if (fs[i].x < -screen_w)
			fs[i].x = screen_w;
		else if (fs[i].x > screen_w)
			fs[i].x = -screen_w;
	}

	for (unsigned i = 3; i < fs.size(); ++i)
	{
		fs[i].x += velocity * elapsedTime * direction;
		if (fs[i].x > screen_w)
			fs[i].x = -screen_w;
		else if (fs[i].x < -screen_w)
			fs[i].x = screen_w;
	}
}

const float& pla::MovingBG::getAlpha() const
{
	return sprites[0]->getAlpha();
}