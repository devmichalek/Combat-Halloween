#include "block.h"

Block::Block( sf::Uint8 w, sf::Uint8 n, float x, float y )
{
	this->w = w;
	this->n = n;
	this->x = x;
	this->y = y;
}

Block::~Block()
{
	w = 0;
	n = 0;
	x = 0;
	y = 0;
}