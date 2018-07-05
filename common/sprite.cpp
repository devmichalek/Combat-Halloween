#include "sprite.h"
#include <math.h>

const sf::Sprite& cmm::Sprite::get() const
{
	return *sprite;
}

void cmm::Sprite::load(const char* path, int numOfOffsets)
{
	texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(path))
	{
		texture->setSmooth(true);
		numOfOffsets = numOfOffsets < 1 ? 1 : numOfOffsets;

		float width = texture->getSize().x;
		float height = texture->getSize().y;

		for (int i = 0; i < numOfOffsets; ++i)
		{
			sf::IntRect intRect(width * i / numOfOffsets, 0, width / numOfOffsets, height);
			rects.push_back(intRect);
		}

		sprite = std::make_unique<sf::Sprite>();
		if (sprite)
		{
			sprite->setTexture(*texture);
			setOffset(0);
		}
	}
}

void cmm::Sprite::create(int w, int h)
{
	texture = std::make_unique<sf::Texture>();
	if (texture->create(w, h))
	{
		texture->setSmooth(true);

		sf::IntRect intRect(0, 0, (float)texture->getSize().x, (float)texture->getSize().y);
		rects.push_back(intRect);
		sprite = std::make_unique<sf::Sprite>();

		if (sprite)
		{
			sf::Uint8* pixels;
			pixels = new sf::Uint8[w * h * 4];

			for (int i = 0; i < w * h * 4; ++i)
			{
				pixels[i] = 0xFF;
			}

			texture->update(pixels);
			delete[] pixels;
			pixels = nullptr;

			sprite->setTexture(*texture);
			setOffset(0);
			alpha = 0xFF;
			setAlpha(0);
		}
	}
}



void cmm::Sprite::setColor(sf::Color color)
{
	sprite->setColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));
}

sf::Color cmm::Sprite::getColor() const
{
	return sprite->getColor();
}

void cmm::Sprite::setAlpha(float alpha)
{
	if (this->alpha != alpha)
	{
		this->alpha = alpha;
		sf::Color newColor(sprite->getColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		sprite->setColor(newColor);
	}
}

float cmm::Sprite::getAlpha() const
{
	return alpha;
}



void cmm::Sprite::fadein(float v, int max)
{
	if (alpha < max)
	{
		alpha += v;

		if (alpha > max)
		{
			alpha = static_cast<float>(max);
		}

		sf::Color newColor(sprite->getColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		sprite->setColor(newColor);
	}
}

void cmm::Sprite::fadeout(float v, int min)
{
	if (alpha > min)
	{
		alpha -= v;

		if (alpha < min)
		{
			alpha = static_cast<float>(min);
		}

		sf::Color newColor(sprite->getColor());
		newColor.a = static_cast<sf::Uint8>(alpha);
		sprite->setColor(newColor);
	}
}



void cmm::Sprite::flipHorizontally()
{
	sprite->setScale(sprite->getScale().x * -1, sprite->getScale().y);
}

void cmm::Sprite::flipVertically()
{
	sprite->setScale(sprite->getScale().x, sprite->getScale().y * -1);
}




void cmm::Sprite::center(float x, float y)
{
	float left = x - (float)texture->getSize().x * sprite->getScale().x / rects.size() / 2;
	float top = y - (float)texture->getSize().y * sprite->getScale().y / 2;
	sprite->setPosition(left, top);
}




float cmm::Sprite::getRotation() const
{
	return sprite->getRotation();
}

void cmm::Sprite::setOffset(int n)
{
	if (n > -1 && n < static_cast <int> (rects.size()))
	{
		sprite->setTextureRect(rects[n]);
	}
}

unsigned cmm::Sprite::getNumOfOffsets() const
{
	return rects.size();
}




const float& cmm::Sprite::getX() const
{
	return sprite->getPosition().x;
}

const float& cmm::Sprite::getY() const
{
	return sprite->getPosition().y;
}

float cmm::Sprite::getWidth() const
{
	float scale = sprite->getScale().x;
	if (scale < 0)	scale = -scale;
	return (float)texture->getSize().x * scale / rects.size();
}

float cmm::Sprite::getHeight() const
{
	float scale = sprite->getScale().y;
	if (scale < 0)	scale = -scale;
	return (float)texture->getSize().y * scale;
}

const float& cmm::Sprite::getLeft() const
{
	return sprite->getPosition().x;
}

float cmm::Sprite::getRight() const
{
	return sprite->getPosition().x + getWidth();
}

const float& cmm::Sprite::getTop() const
{
	return sprite->getPosition().y;
}

const float cmm::Sprite::getBot() const
{
	return sprite->getPosition().y + getHeight();
}

bool cmm::Sprite::checkCollision(float x, float y, float w, float h) const
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

bool cmm::Sprite::checkCollisionRect(sf::Rect <float> rect) const
{
	if (rect.top + rect.height <= getTop())
		return false;

	if (rect.top >= getBot())
		return false;

	if (rect.left + rect.width <= getLeft())
		return false;

	if (rect.left >= getRight())
		return false;

	return true;
}

bool cmm::Sprite::checkCollisionCircle(float x, float y) const
{
	float r = getWidth() > getHeight() ? getWidth() : getHeight();
	r /= 2;
	float xCenter = getX() + getWidth() / 2;
	float yCenter = getY() + getHeight() / 2;

	float a = x - xCenter;
	float b = y - yCenter;

	if (sqrt((a * a) + (b * b)) <= r)
	{
		return true;
	}

	return false;
}