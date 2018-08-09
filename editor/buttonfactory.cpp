#include "buttonfactory.h"
#include <stdio.h>

ButtonFactory::ButtonFactory()
{
	free();
}

ButtonFactory::~ButtonFactory()
{
	free();
}

void ButtonFactory::free()
{
	for (auto &it : tiles)
	{
		it->free();
	}
	tiles.clear();
}



void ButtonFactory::load(QSize size)
{
	int width = size.width() * 0.032;
	for (int i = 0; i < 21; ++i)
	{
		tiles.push_back(new Button);
		tiles[i]->button = new QPushButton;
		// printf("%s\n", ("images/platform/tiles" + std::to_string(i) + ".png").c_str());
		tiles[i]->button->setIcon(QIcon(("images/platform/tiles/" + std::to_string(i) +".png").c_str()));
		tiles[i]->button->setIconSize(QSize(width * 0.85, width * 0.85));
		tiles[i]->button->setGeometry(QRect(i*width, 0, width, width));
	}
}

void ButtonFactory::setParent(QWidget* widget)
{
	for (auto &it : tiles)
	{
		it->button->setParent(widget);
	}
}

void ButtonFactory::setEnabledAll(bool unlocked)
{
	for (auto &it : tiles)
	{
		it->button->setEnabled(unlocked);
	}
}