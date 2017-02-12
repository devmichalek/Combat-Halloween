#include "pug.h"

Pug::Pug()
{
	vel = 0;
	hit = false;
	state = 0;
	startY = 0;
	surplus = 0;
}

Pug::~Pug()
{
	free();
}

void Pug::free()
{
	vel = 0;
	hit = false;
	state = 0;
	startY = 0;
	surplus = 0;
	
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}
}



void Pug::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

void Pug::positioning( int width, int type )
{
	int length = 2;
	
	if( type == 1 )
	{
		addBlock( 3, 0, -( width *(length +1) ) );
		
		for( int i = 1; i < length; i++ )
		{
			addBlock( 3, 0, blocks[ blocks.size()-1 ]->y +width );
		}
		
		addBlock( 5, 0, -width );
	}
	else
	{
		// First line of blocks.
		addBlock( 2, 0, -( width *(length +1) ) );

		for( int i = 1; i < length; i++ )
		{
			addBlock( 2, 0, blocks[ blocks.size()-1 ]->y +width );
		}
		
		addBlock( 0, 0, -width );
		
		
		// Second line of blocks.
		addBlock( 4, width, -( width *( length +1 ) ) );

		for( int i = 1; i < length; i++ )
		{
			addBlock( 4, width, blocks[ blocks.size()-1 ]->y +width );
		}
		
		addBlock( 1, width, -width );
	}
}

void Pug::setPosition( int x, int y, int vel, int surplus )
{
	for( auto &i :blocks )
	{
		i->x += x;
		i->y += y;
	}
	
	startY = y;
	this->vel = vel;
	this->surplus = surplus;
}

void Pug::moveX( float vel )
{
	for( auto &it :blocks )
	{
		it->x += vel;
	}
}

void Pug::moving( int width )
{
	if( state == 0 )
	{
		if( blocks[ blocks.size()-1 ]->y <= startY -(width*2) -surplus )
		{
			state = 1;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->y -= vel;
			}
		}
	}
	else
	{
		if( blocks[ blocks.size()-1 ]->y >= startY )
		{
			state = 0;
			hit = false;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->y += vel*2;
			}
		}
	}
}
	
	
	
unsigned Pug::getSize()
{
	return blocks.size();
}

int Pug::getX( unsigned which )
{
	return blocks[ which ]->x;
}

int Pug::getY( unsigned which )
{
	return blocks[ which ]->y;
}

int Pug::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}

bool Pug::harm( int width )
{
	if( blocks[ blocks.size()-1 ]->y >= startY -width/3 && !hit && state == 0 )
	{
		hit = true;
		return true;
	}
	
	return false;
}