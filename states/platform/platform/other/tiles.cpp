#include "tiles.h"
#include "loading.h"
#include <boost/lexical_cast.hpp>

pla::Tiles::Tiles()
{
	free();
}

pla::Tiles::~Tiles()
{
	free();
}

void pla::Tiles::free()
{
	screen_w = 0;
	screen_h = 0;
	wPad = hPad = 0;

	if (tiles)
	{
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
		{
			delete[] tiles[i];
			tiles[i] = nullptr;
		}

		delete[] tiles;
	}

	if (untiles)
	{
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
		{
			delete[] untiles[i];
			untiles[i] = nullptr;
		}

		delete[] untiles;
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

	reset();
}

void pla::Tiles::reset()
{
#ifdef __TEST__
	collision = false;
#endif
}

void pla::Tiles::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
	wPad = static_cast<int>(((screen_w / (TILE_FULL_WIDTH)) - 3) / 2);
	hPad = static_cast<int>(((screen_h / (TILE_FULL_HEIGHT)) - 3) / 2);

#ifdef __TEST__
	rect.setSize(sf::Vector2f(static_cast<float>(TILE_FULL_WIDTH), static_cast<float>(TILE_FULL_HEIGHT)));
	sf::Color rColor = cmm::GREEN_COLOR;
	rColor.a = MAX_ALPHA / 2;
	rect.setFillColor(rColor);
#endif

	for (unsigned i = 0; i < 21; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/tiles/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		sprites[i]->setScale	(0.51, 0.51);
	}

	// Init only once!
	if (!tiles && !untiles)
	{
		tiles = new char*[MAX_TILE_MAP_WIDTH];
		untiles = new char*[MAX_TILE_MAP_WIDTH];
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
		{
			tiles[i] = new char[MAX_TILE_MAP_HEIGHT];
			untiles[i] = new char[MAX_TILE_MAP_HEIGHT];
			for (int j = 0; j < MAX_TILE_MAP_HEIGHT; ++j)
			{
				tiles[i][j] = -1;
				untiles[i][j] = -1;
			}
		}
	}
}

void pla::Tiles::draw(sf::RenderTexture &rt, const float &x, const float &y)
{
	short l = static_cast <int> (x / TILE_WIDTH) - 1;
	short r = static_cast <int> ((x + screen_w) / TILE_WIDTH) + 1;
	short b = static_cast <int> (y / TILE_HEIGHT);
	short t = static_cast <int> (y + screen_h) / TILE_HEIGHT;

	if (l < MIN_TILE_MAP_WIDTH)
		l = MIN_TILE_MAP_WIDTH;

	if (r >= MAX_TILE_MAP_WIDTH)
		r = MAX_TILE_MAP_WIDTH -1;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				rt.draw(*sprites[tiles[i][j]]);
			}
			else if (untiles[i][j] != -1)
			{
				sprites[untiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				rt.draw(*sprites[untiles[i][j]]);
			}
		}
	}

	// shader.setUniform("addAlpha", 1);
#ifdef __TEST__
	if (collision)
	{
		rt.draw(rect);
		rect.setPosition(-rect.getSize().x, -rect.getSize().y);	// put rect outside of window are
	}
#endif
}

void pla::Tiles::read(std::vector<std::string> &vec)
{
	short x = -1, y = -1, c = -1;
	if (!vec.empty())
	{
		char** ptr = vec[0].find("t:1") != std::string::npos ? tiles : untiles;
		for (auto &it : vec)
		{
			c = boost::lexical_cast<int>(it.substr(it.find("c:") + 2, it.find(" x:") - (it.find("c:") + 2)));
			x = boost::lexical_cast<int>(it.substr(it.find("x:") + 2, it.find(" y:") - (it.find("x:") + 2))) / TILE_WIDTH;
			y = boost::lexical_cast<int>(it.substr(it.find("y:") + 2, it.find(" id:") - (it.find("y:") + 2))) / TILE_HEIGHT;
			ptr[x][y] = c;
		}
	}
}


#ifdef __TEST__
void pla::Tiles::switchCollision(bool collision)
{
	this->collision = collision;
}
#endif

bool pla::Tiles::checkCollisionV(sf::Rect<int> &rect, const float &x, const float &y, const char add)
{
	short l = static_cast<int> (x / TILE_WIDTH);
	short r = static_cast<int> ((x + screen_w) / TILE_WIDTH);
	short b = static_cast<int> (y / TILE_HEIGHT);
	short t = static_cast<int> ((y + screen_h) / TILE_HEIGHT);
	rect.top -= add;

	// Optimisation
	if (l != MIN_TILE_MAP_WIDTH)		l += wPad;
	if (r != MAX_TILE_MAP_WIDTH - 1)	r -= wPad;
	if (b != MIN_TILE_MAP_HEIGHT)		l += hPad;
	if (t != MAX_TILE_MAP_HEIGHT - 1)	r -= hPad;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
#ifdef __TEST__
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
#endif
					last = sf::Vector2i(i, j);
					rect.top += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
#ifdef __TEST__
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
#endif
					last = sf::Vector2i(i, j);
					rect.top += add;
					return true;
				}
			}
		}
	}

	rect.top += add;
	return false;
}

bool pla::Tiles::checkCollisionH(sf::Rect<int> &rect, const float &x, const float &y, const char add)
{
	short l = static_cast<int> (x / TILE_WIDTH);
	short r = static_cast<int> ((x + screen_w) / TILE_WIDTH);
	short b = static_cast<int> (y / TILE_HEIGHT);
	short t = static_cast<int> ((y + screen_h) / TILE_HEIGHT);
	rect.left -= add;

	// Optimisation
	if (l != MIN_TILE_MAP_WIDTH)		l += wPad;
	if (r != MAX_TILE_MAP_WIDTH - 1)	r -= wPad;
	if (b != MIN_TILE_MAP_HEIGHT)		l += hPad;
	if (t != MAX_TILE_MAP_HEIGHT - 1)	r -= hPad;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
#ifdef __TEST__
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
#endif
					last = sf::Vector2i(i, j);
					rect.left += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * TILE_WIDTH, -(j * TILE_HEIGHT) + screen_h - TILE_HEIGHT);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
#ifdef __TEST__
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
#endif
					last = sf::Vector2i(i, j);
					rect.left += add;
					return true;
				}
			}
		}
	}

	rect.left += add;
	return false;
}

float pla::Tiles::getTop()
{
	return (-last.y * TILE_HEIGHT) + screen_h;
}

float pla::Tiles::getLeft()
{
	return last.x * TILE_WIDTH;
}