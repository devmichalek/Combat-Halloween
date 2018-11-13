#include "text.h"

cmm::Text::FontMap::FontMap()
{
	// ...
}

cmm::Text::FontMap::~FontMap()
{
	if (!paths.empty())
		paths.clear();

	if (!fonts.empty())
	{
		for (auto &it : fonts)
		{
			delete it;
			it = nullptr;
		}
		fonts.clear();
	}
}

sf::Font* cmm::Text::FontMap::get(std::string &path)
{
	auto it = std::find(paths.begin(), paths.end(), path);
	if (it != std::end(paths))
	{
		size_t pos = paths.size() - (paths.end() - it);
		return fonts[pos];
	}

	return nullptr;
}

cmm::Text::Text()
{
	// ...
}

cmm::Text::~Text()
{
	// ...
}

const std::string cmm::Text::getString() const
{
	return text->getString();
}

std::string cmm::Text::setFont(std::string path)
{
	sf::Font* font = nullptr;
	sf::Font* ptr = font_map.get(path);

	if (!ptr) // new one
		font = new sf::Font();
	else
		font = ptr;

	if (!ptr && font->loadFromFile(path))
	{
		text = std::make_unique<sf::Text>();
		text->setFont(*font);
		font_map.paths.push_back(path);
		font_map.fonts.push_back(font);
		return "Success: Font \"" + std::string(path) + "\" loaded correctly.";
	}
	else if(ptr)
	{
		text = std::make_unique<sf::Text>();
		text->setFont(*font);
		return "Success: Font set correctly.";
	}
	
	return "Error: Cannot create font face from \"" + std::string(path) + "\".";
}

void cmm::Text::setText(std::string line)
{
	if(text)
    {
		text->setString(line);
		setRawAlpha();
	}
}

void cmm::Text::setTextW(std::wstring line)
{
	if (text)
	{
		text->setString(line);
		setRawAlpha();
	}
}

void cmm::Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*text, states);
}




void cmm::Text::fadein(const float &v, const int &max)
{
	if(alpha < max)
	{
		alpha += v;
		
		if(alpha > max)
		{
			alpha = static_cast<float>(max);
		}
		
		setRawAlpha();
	}
}

void cmm::Text::fadeout(const float &v, const int &min)
{
	if (alpha > min)
	{
		alpha -= v;

		if (alpha < min)
		{
			alpha = static_cast<float>(min);
		}

		setRawAlpha();
	}
}



void cmm::Text::flipHorizontally()
{
	text->setScale(text->getScale().x * -1, text->getScale().y);
}

void cmm::Text::flipVertically()
{
	text->setScale(text->getScale().x, text->getScale().y * -1);
}

int cmm::Text::getSize() const
{
	return text->getCharacterSize();
}



void cmm::Text::setAlpha(float alpha)
{
	if(this->alpha != alpha)
	{
		this->alpha = alpha;
		setRawAlpha();
	}
}

inline void cmm::Text::setRawAlpha()
{
	sf::Color fColor(text->getFillColor());
	sf::Color oColor(text->getOutlineColor());
	text->setFillColor(sf::Color(fColor.r, fColor.g, fColor.b, static_cast<sf::Uint8>(alpha)));
	text->setOutlineColor(sf::Color(oColor.r, oColor.g, oColor.b, static_cast<sf::Uint8>(alpha)));
}

const float& cmm::Text::getAlpha() const
{
	return alpha;
}

void cmm::Text::setFillColor(sf::Color color)
{
	text->setFillColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));
}

void cmm::Text::setOutlineColor(sf::Color color)
{
	text->setOutlineColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha)));
}

sf::Color cmm::Text::getFillColor() const
{
	return text->getFillColor();
}

sf::Color cmm::Text::getOutlineColor() const
{
	return text->getOutlineColor();
}



const float& cmm::Text::getX() const
{
	return text->getPosition().x;
}

const float& cmm::Text::getY() const
{
	return text->getPosition().y;
}

float cmm::Text::getWidth() const
{
	return text->getLocalBounds().width * text->getScale().x;
}

float cmm::Text::getHeight() const
{
	return text->getLocalBounds().height * text->getScale().y;
}

const float& cmm::Text::getLeft() const
{
	return text->getPosition().x;
}

float cmm::Text::getRight() const
{
	return text->getPosition().x + getWidth();
}

const float& cmm::Text::getTop() const
{
	return text->getPosition().y;
}

float cmm::Text::getBot() const
{
	return text->getPosition().y + getHeight();
}


float cmm::Text::getFixedWidth() const
{
	float scale = text->getScale().x;
	if (scale < 0)
		scale = -scale;
	return text->getLocalBounds().width * scale;
}

float cmm::Text::getFixedHeight() const
{
	float scale = text->getScale().y;
	if (scale < 0)
		scale = -scale;
	return text->getLocalBounds().height * scale;
}