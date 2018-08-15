#include "rectbutton.h"

Rectbutton::Rectbutton()
{
	free();
}

Rectbutton::~Rectbutton()
{
	free();
}

void Rectbutton::free()
{
	alpha = 0;
	alphaBorders = 0;

	focus = false;
	clicked = false;
	state = 0;

	if (!rects.empty())
	{
		rects.clear();
	}
}



void Rectbutton::setFont(const char* path)
{
	text_one.setFont(path);
	text_two.setFont(path);
}

void Rectbutton::create(std::string line, int size, float ply)
{
	// Set text.
	text_one.setText(line);
	text_two.setText(line);
	text_one.setSize(size);
	text_two.setSize(size);

	// Set lines.
	float w = text_one.getWidth() + text_one.getWidth() / 5;
	float h = text_one.getHeight() * 2 + text_one.getHeight() / 5;

	if (w < 1)	w = 1;
	if (h < 1)	h = 1;
	if (ply < 1)	ply = 1;

	for (unsigned i = 0; i < 5; i++)
	{
		sf::RectangleShape shape;
		rects.push_back(shape);
	}

	rects[0].setSize(sf::Vector2f(w + ply * 2, ply));
	rects[1].setSize(sf::Vector2f(ply, h));
	rects[2].setSize(sf::Vector2f(w + ply * 2, ply));
	rects[3].setSize(sf::Vector2f(ply, h));
	rects[4].setSize(sf::Vector2f(w, h));

	setPosition(0, 0);
	sf::Color newColor(rects[rects.size() - 1].getFillColor());
	newColor.a = 0;
	for (auto &it : rects)
	{
		it.setFillColor(newColor);
	}
}

void Rectbutton::handle(const sf::Event &event)
{
	if (state == 1 && !clicked)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			checkCollision((float)event.mouseMove.x, (float)event.mouseMove.y) ? focus = true : focus = false;
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (checkCollision((float)event.mouseButton.x, (float)event.mouseButton.y))
				{
					// printf("%f %f\n", alpha, alphaBorders);
					if (alpha > 0xFF / 2 && alphaBorders > 0xFF / 2)
					{
						focus = true;
						clicked = true;
					}
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			focus = false;
		}
	}
}

void Rectbutton::draw(sf::RenderWindow* &window)
{
	// Background.
	window->draw(text_two.get());

	// Frame.
	for (auto &it : rects)
	{
		window->draw(it);
	}

	// Front.
	window->draw(text_one.get());
}

void Rectbutton::mechanics(const double &elapsedTime)
{
	if (state == 1)
	{
		float value = (float)elapsedTime * 0xFF * 6;

		if (focus)
		{
			int max = 0xFF;
			fadein(value, max);
			text_one.fadein(value, max);
			text_two.fadeout(value, max);
		}
		else
		{
			int min = 0;
			fadeout(value, min);
			text_one.fadeout(value, min);
			text_two.fadein(value, min);
		}
	}
}




void Rectbutton::fadein(const float &v, const int &max)
{
	if (alpha < max)
	{
		alpha += v;

		if (alpha > max)
		{
			alpha = static_cast<float>(max);
		}

		sf::Color newColor(rects[rects.size() - 1].getFillColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		rects[rects.size() - 1].setFillColor(newColor);
	}
}

void Rectbutton::fadeinBorders(const float &v, const int &max)
{
	if (alphaBorders < max)
	{
		alphaBorders += v;

		if (alphaBorders > max)
		{
			alphaBorders = static_cast<float>(max);
		}

		sf::Color newColor(rects[0].getFillColor());
		newColor.a = static_cast<sf::Uint8>(alphaBorders);
		for (unsigned i = 0; i < rects.size() - 1; i++)
		{
			rects[i].setFillColor(newColor);
		}
	}
}

void Rectbutton::fadeinGlobal(const float &v, const int &max)
{
	if (state == 0)
	{
		fadeinBorders(v, max);
		text_two.fadein(v, max);
		if (alphaBorders == max)
		{
			state = 1;
		}
	}
}

void Rectbutton::fadeout(const float &v, const int &min)
{
	if (alpha > min)
	{
		alpha -= v;

		if (alpha < min)
		{
			alpha = static_cast<float>(min);
		}

		sf::Color newColor(rects[rects.size() - 1].getFillColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		rects[rects.size() - 1].setFillColor(newColor);
	}
}

void Rectbutton::fadeoutBorders(const float &v, const int &min)
{
	if (alphaBorders > min)
	{
		alphaBorders -= v;

		if (alphaBorders < min)
		{
			alphaBorders = static_cast<float>(min);
		}

		sf::Color newColor(rects[0].getFillColor());
		newColor.a = static_cast<sf::Uint8>(alphaBorders);
		for (unsigned i = 0; i < rects.size() - 1; i++)
		{
			rects[i].setFillColor(newColor);
		}
	}
}

void Rectbutton::fadeoutGlobal(const float &v, const int &min)
{
	if (state == 1)
	{
		fadeout(v, min);
		fadeoutBorders(v, min);
		text_one.fadeout(v, min);
		text_two.fadeout(v, min);
		if (alphaBorders == min)
		{
			state = 2;
		}
	}
}




void Rectbutton::move(float x, float y)
{
	text_one.move(x, y);
	text_two.move(x, y);
	for (auto &it : rects)
	{
		it.move(x, y);
	}
}

void Rectbutton::setPosition(float x, float y)
{
	rects[0].setPosition(x, y);
	rects[1].setPosition(x + rects[0].getSize().x - rects[0].getSize().y, y + rects[0].getSize().y);
	rects[2].setPosition(x, y + rects[0].getSize().y + rects[3].getSize().y);
	rects[3].setPosition(x, y + rects[0].getSize().y);
	rects[4].setPosition(x + rects[0].getSize().y, y + rects[0].getSize().y);
	text_one.center(rects[4].getPosition().x + rects[4].getSize().x / 2, rects[4].getPosition().y + rects[4].getSize().y / 3);
	text_two.center(rects[4].getPosition().x + rects[4].getSize().x / 2, rects[4].getPosition().y + rects[4].getSize().y / 3);
}

void Rectbutton::center(float x, float y, int w, int h)
{
	// Two times x.
	setPosition(x + w / 2 - rects[0].getSize().x / 2, y + h / 2 - rects[0].getSize().x / 2);
}

void Rectbutton::setColor(sf::Color color)
{
	sf::Color newColor(rects[0].getFillColor());
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;
	for (unsigned i = 0; i < rects.size() - 1; i++)
	{
		rects[i].setFillColor(newColor);
	}
	text_two.setFillColor(newColor);

	newColor.a = rects[rects.size() - 1].getFillColor().a;
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;
	rects[rects.size() - 1].setFillColor(newColor);
}

void Rectbutton::setColorText(sf::Color color)
{
	text_one.setFillColor(color);
}

void Rectbutton::setAlpha(float alpha)
{
	if (this->alpha != alpha)
	{
		this->alpha = alpha;
		sf::Color newColor(rects[rects.size() - 1].getFillColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		rects[rects.size() - 1].setFillColor(newColor);
	}
}

void Rectbutton::setAlphaBorders(float alpha)
{
	if (this->alphaBorders != alpha)
	{
		this->alphaBorders = alpha;
		sf::Color newColor(rects[0].getFillColor());
		newColor.a = static_cast<sf::Uint8>(this->alphaBorders);
		for (unsigned i = 0; i < rects.size() - 1; i++)
		{
			rects[i].setFillColor(newColor);
		}
	}
}




float Rectbutton::getAlpha()
{
	return alpha;
}

float Rectbutton::getAlphaBorders()
{
	return alphaBorders;
}

sf::Uint8& Rectbutton::getState()
{
	return state;
}

bool& Rectbutton::getFocus()
{
	return focus;
}

bool& Rectbutton::getClicked()
{
	return clicked;
}




const float& Rectbutton::getX() const
{
	return rects[0].getPosition().x;
}

const float& Rectbutton::getY() const
{
	return rects[0].getPosition().y;
}

const float& Rectbutton::getWidth() const
{
	return rects[0].getSize().x;
}

float Rectbutton::getHeight() const
{
	return rects[0].getSize().y * 2 + rects[rects.size() - 1].getSize().y;
}

const float& Rectbutton::getLeft() const
{
	return rects[0].getPosition().x;
}

float Rectbutton::getRight() const
{
	return rects[0].getPosition().x + rects[0].getSize().x;
}

const float& Rectbutton::getTop() const
{
	return rects[0].getPosition().y;
}

float Rectbutton::getBot() const
{
	return rects[0].getPosition().y + rects[rects.size() - 1].getSize().y + (rects[0].getSize().y * 2);
}




bool Rectbutton::checkCollision(float x, float y, float w, float h) const
{
	if (y + h <= getTop())
		return false;

	if (y >= getBot())
		return false;

	if (x + w <= getLeft())
		return false;

	if (x >= getRight())
		return false;

	return true;
}