#include "landscape.h"
#include "loading.h"

pla::LandscapeUnit::LandscapeUnit(char newChosen, float newScale)
	: chosen(newChosen), scale(newScale)
{
	// ...
}

pla::LandscapeUnit::~LandscapeUnit()
{
	chosen = -1;
	scale = 0.0f;
}

pla::Landscape::Landscape()
{
	tree = nullptr;
	free();
}

pla::Landscape::~Landscape()
{
	free();
}

void pla::Landscape::free()
{
	screen_w = screen_h = 0;
	reset();
}

void pla::Landscape::reset()
{
	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void pla::Landscape::init()
{
	reset();
	tree = new LandscapeTree;
}

void pla::Landscape::load(const float &screen_w, const float &screen_h)
{
	free();
	init();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	for (unsigned i = 0; i < 13; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/landscape/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
	}
}


void pla::Landscape::draw(sf::RenderTexture &rt, const float &x, const float &y)
{
	result.clear();
	Box queryBox(Point(x, y), Point(x + screen_w, y + screen_h));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	

	char c = 0;
	float tx = 0, ty = 0;
	BOOST_FOREACH(LandscapeBox const& item, result)
	{
		c = item.second.chosen;
		sprites[c]->setScale(item.second.scale, item.second.scale);
		tx = bg::get<0>(item.first.min_corner());
		ty = (bg::get<1>(item.first.min_corner()) + sprites[c]->getHeight()) * -1 + screen_h;
		sprites[c]->setPosition(tx, ty);
		rt.draw(*sprites[c]);
	}
}

void pla::Landscape::read(std::vector<std::string> &vec)
{
	if (!tree)
		return;

	int x = -1, y = -1, c = -1;
	float scale = 1.0f;
	if (!vec.empty())
	{
		for (auto &it : vec)
		{
			c = boost::lexical_cast<int>(it.substr(it.find("c:") + 2, it.find(" x:") - (it.find("c:") + 2)));
			x = boost::lexical_cast<int>(it.substr(it.find("x:") + 2, it.find(" y:") - (it.find("x:") + 2)));
			y = boost::lexical_cast<int>(it.substr(it.find("y:") + 2, it.find(" id:") - (it.find("y:") + 2)));
			scale = boost::lexical_cast<float>(it.substr(it.find("(scale:") + 7, it.find(")") - (it.find("(scale:") + 7)));

			sprites[c]->setScale(scale, scale);
			Box box(Point(x, y - sprites[c]->getHeight()), Point(x + sprites[c]->getWidth(), y));
			LandscapeUnit lu(c, scale);
			LandscapeBox lbox = std::make_pair(box, lu);
			tree->insert(lbox);
		}
	}
}