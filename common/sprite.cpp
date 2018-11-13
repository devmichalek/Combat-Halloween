#include "sprite.h"
#include "colors.h"
#include <math.h>

cmm::Sprite::TextureMap::TextureMap()
{
	// ...
}

cmm::Sprite::TextureMap::~TextureMap()
{
	if (!paths.empty())
		paths.clear();

	if (!textures.empty())
	{
		for (auto &it : textures)
		{
			delete it;
			it = nullptr;
		}
		textures.clear();
	}

	if (!unique_textures.empty())
	{
		for (auto &it : unique_textures)
		{
			delete it;
			it = nullptr;
		}
		unique_textures.clear();
	}
}

sf::Texture* cmm::Sprite::TextureMap::get(std::string &path)
{
	auto it = std::find(paths.begin(), paths.end(), path);
	if (it != std::end(paths))
	{
		size_t pos = paths.size() - (paths.end() - it);
		return textures[pos];
	}

	return nullptr;
}

cmm::Sprite::Sprite()
{
	w = h = 0.0f;
}

cmm::Sprite::~Sprite()
{
	w = h = 0.0f;
}

std::string cmm::Sprite::load(std::string path, int numOfOffsets)
{
	std::string out = "Error: Cannot properly create texture from \"" + path + "\".";

	sf::Texture* texture = nullptr;
	sf::Texture* ptr = texture_map.get(path);
	if (!ptr) // new one
		texture = new sf::Texture();
	else
		texture = ptr;

	if (!ptr && texture->loadFromFile(path))
	{
		out = "Success: Correctly loaded \"" + path + "\".";
		texture->setSmooth(true);
		texture_map.paths.push_back(path);
		texture_map.textures.push_back(texture);
	}
	else if(ptr)
		out = "Success: Correctly ascribed existing texture.";

	if(texture)
	{
		numOfOffsets = numOfOffsets < 1 ? 1 : numOfOffsets;

		if (numOfOffsets == 1)
			out = "Warning: The number of offsets of the sprite \"" + path + "\" is 1.";

		int width = texture->getSize().x;
		int height = texture->getSize().y;

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
			w = static_cast<float>(width);
			h = static_cast<float>(height);
		}
		else
			out = "Error: Cannot create sprite from \"" + path + "\".";
	}

	return out;
}

std::string cmm::Sprite::loadRepeated(std::string path, float w, float h, bool borders)
{
	std::string out = "Error: Cannot create image from \"" + path + "\"";

	sf::Image image;
	if (image.loadFromFile(path))
	{
		out = "Success: Correctly loaded \"" + path + "\".";

		int width = image.getSize().x;
		int height = image.getSize().y;
		int realWidth = borders ? static_cast<int>(w) : width;
		int realHeight = borders ? static_cast<int>(h) : height;
		if (!borders)
		{
			while (realWidth < w)	realWidth += width;
			while (realHeight < h)	realHeight += height;
		}
		
		sf::Image output;
		output.create(realWidth, realHeight);
		for (int i = 0; i < realWidth; ++i)
		{
			for (int j = 0; j < realHeight; ++j)
			{
				output.setPixel(i, j, image.getPixel(i % width, j % height));
			}
		}

		sf::Texture* texture = new sf::Texture();
		if (texture->loadFromImage(output))
		{
			texture->setSmooth(true);
			texture_map.unique_textures.push_back(texture);
			// texture->setRepeated(true);

			sf::IntRect intRect(0, 0, realWidth, realHeight);
			rects.push_back(intRect);

			sprite = std::make_unique<sf::Sprite>();
			if (sprite)
			{
				sprite->setTexture(*texture);
				setOffset(0);
				w = static_cast<float>(width);
				h = static_cast<float>(height);
			}
			else
				out = "Error: Cannot create sprite from \"" + path + "\".";
		}
		else
			out = "Error: Cannot properly create texture from \"" + path + "\".";
	}

	return out;
}

std::string cmm::Sprite::create(int w, int h)
{
	std::string out = "Error: Cannot create texture with width: " + std::to_string(w) + " height: " + std::to_string(h);

	sf::Texture* texture = new sf::Texture();
	if (texture->create(w, h))
	{
		texture->setSmooth(true);
		texture_map.unique_textures.push_back(texture);

		sf::IntRect intRect(0, 0, texture->getSize().x, texture->getSize().y);
		rects.push_back(intRect);
		sprite = std::make_unique<sf::Sprite>();

		if (sprite)
		{
			sf::Uint8* pixels = new sf::Uint8[w * h * 4];
			for (int i = 0; i < w * h * 4; ++i)
			{
				pixels[i] = (int)MAX_ALPHA;
			}

			texture->update(pixels);
			delete[] pixels;
			pixels = nullptr;

			sprite->setTexture(*texture);
			setOffset(0);
			alpha = MAX_ALPHA;
			setAlpha(0);
			this->w = static_cast<float>(texture->getSize().x);
			this->h = static_cast<float>(texture->getSize().y);
			out = "Success: Correctly created sprite with width: " + std::to_string(w) + " height: " + std::to_string(h);
		}
		else
			out = "Error: Cannot create sprite with width: " + std::to_string(w) + " height: " + std::to_string(h);
	}

	return out;
}

void cmm::Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
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

const float& cmm::Sprite::getAlpha() const
{
	return alpha;
}



void cmm::Sprite::fadein(const float &v, const int &max)
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

void cmm::Sprite::fadeout(const float &v, const int &min)
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
	float left = x - (w * sprite->getScale().x / rects.size()) / 2;
	float top = y - (h * sprite->getScale().y) / 2;
	sprite->setPosition(left, top);
}




float cmm::Sprite::getRotation() const
{
	return sprite->getRotation();
}

void cmm::Sprite::setOffset(int n)
{
	//if (n > -1 && n < static_cast <int> (rects.size()))
	//{
		sprite->setTextureRect(rects[n]);
	//}
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
	return w * scale / rects.size();
}

float cmm::Sprite::getHeight() const
{
	float scale = sprite->getScale().y;
	if (scale < 0)	scale = -scale;
	return h * scale;
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

const float& cmm::Sprite::getScaleX() const
{
	return sprite->getScale().x;
}

const float& cmm::Sprite::getScaleY() const
{
	return sprite->getScale().y;
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

template<typename Type>
bool cmm::Sprite::checkCollisionRect(sf::Rect<Type>& rect)
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

template bool cmm::Sprite::checkCollisionRect(sf::Rect<int>& rect);
template bool cmm::Sprite::checkCollisionRect(sf::Rect<float>& rect);
template bool cmm::Sprite::checkCollisionRect(sf::Rect<double>& rect);