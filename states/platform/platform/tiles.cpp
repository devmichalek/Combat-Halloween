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
	width = 32;
	screen_w = 0;
	screen_h = 0;
	wPad = hPad = 0;

	if (tiles)
	{
		for (int i = 0; i < max; ++i)
		{
			delete[] tiles[i];
			tiles[i] = nullptr;
		}

		delete[] tiles;
	}

	if (untiles)
	{
		for (int i = 0; i < max; ++i)
		{
			delete[] untiles[i];
			untiles[i] = nullptr;
		}

		delete[] untiles;
	}

	max = 0;

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
	collision = false;
}

void pla::Tiles::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
	wPad = static_cast<int>(((screen_w / (width*2)) - 3) / 2);
	hPad = static_cast<int>(((screen_h / (width*2)) - 3) / 2);

	rect.setSize(sf::Vector2f(static_cast<float>(width * 2), static_cast<float>(width * 2)));
	rect.setFillColor(cmm::GREEN_COLOR);

	for (unsigned i = 0; i < 17; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/tiles/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		sprites[i]->setScale	(0.51, 0.51);
	}

	// Init only once!
	if (!tiles && !untiles)
	{
		max = 3000;
		tiles = new char*[max];
		untiles = new char*[max];
		for (int i = 0; i < max; ++i)
		{
			tiles[i] = new char[max];
			untiles[i] = new char[max];
			for (int j = 0; j < max; ++j)
			{
				tiles[i][j] = -1;
				untiles[i][j] = -1;
			}
		}
	}
}

void pla::Tiles::draw(sf::RenderWindow* &window/*, sf::Shader &shader*/, const float &x, const float &y)
{
	int l = static_cast <int> (x / width) - 1;
	int r = static_cast <int> ((x + screen_w) / width) + 1;
	int b = static_cast <int> (y / width);
	int t = static_cast <int> (y + screen_h) / width;

	if (l < 0)
		l = 0;

	if (r >= max / width)
		r = max / width;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				// shader.setUniform("addAlpha", alphas[i][j] / 0xFF);
				window->draw(*sprites[tiles[i][j]]/*, &shader*/);
			}
			else if (untiles[i][j] != -1)
			{
				sprites[untiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				// shader.setUniform("addAlpha", alphas[i][j] / 0xFF);
				window->draw(*sprites[untiles[i][j]]/*, &shader*/);
			}
		}
	}

	// shader.setUniform("addAlpha", 1);

	if (collision)
	{
		window->draw(rect/*, &shader*/);
		rect.setPosition(-rect.getSize().x, -rect.getSize().y);	// put rect outside of window are
	}
}

void pla::Tiles::read(std::vector<std::string> &vec)
{
	int x = -1, y = -1, c = -1;
	if (!vec.empty())
	{
		char** pointer = nullptr;
		if (vec[0].find("t:1") != std::string::npos)
			pointer = tiles;
		else
			pointer = untiles;

		for (auto &it : vec)
		{
			c = boost::lexical_cast<int>(it.substr(it.find("c:") + 2, it.find(" x:") - (it.find("c:") + 2)));
			x = boost::lexical_cast<int>(it.substr(it.find("x:") + 2, it.find(" y:") - (it.find("x:") + 2))) / width;
			y = boost::lexical_cast<int>(it.substr(it.find("y:") + 2, it.find(" id:") - (it.find("y:") + 2))) / width;
			pointer[x][y] = c;
		}
	}
}



void pla::Tiles::switchCollision(bool collision)
{
	this->collision = collision;
}

bool pla::Tiles::checkCollisionV(sf::Rect<int> &rect, const float &x, const float &y, const char add)
{
	int l = static_cast<int> (x / width);
	int r = static_cast<int> ((x + screen_w) / width);
	int b = static_cast<int> (y / width);
	int t = static_cast<int> ((y + screen_h) / width);
	rect.top -= add;

	// Optimisation
	if (l != 0)	l += wPad;
	if (r != max - 1) r -= wPad;
	if (b != 0)	l += hPad;
	if (t != max - 1) r -= hPad;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

					rect.top += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

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
	int l = static_cast<int> (x / width);
	int r = static_cast<int> ((x + screen_w) / width);
	int b = static_cast<int> (y / width);
	int t = static_cast<int> ((y + screen_h) / width);
	rect.left -= add;

	// Optimisation
	if (l != 0)	l += wPad;
	if (r != max - 1) r -= wPad;
	if (b != 0)	l += hPad;
	if (t != max - 1) r -= hPad;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
						
					rect.left += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

					rect.left += add;
					return true;
				}
			}
		}
	}

	rect.left += add;
	return false;
}