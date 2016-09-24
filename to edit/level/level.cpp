#include "level.h"

Level::Level()
{
	cost = 0;
	name = -1;
	clicked = false;
	focus = false;
	play = true;
	locked = true;
}

Level::~Level()
{
	cost = 0;
	name = -1;
	clicked = false;
	focus = false;
	play = true;
	locked = true;
	
	sprite.free();
	click.free();
}

	
void Level::load( string name, int cost )
{
	this->name = name;
	this->cost = cost;
	
	sprite.setName( "level-" + name );
	sprite.load( "level select/level.png", 4 );
	sprite.setScale( 0.6, 0.6 );
	
	//text.setID( "level-text" );
	//text.setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	//text.setText( "cost" );
	
	//coin.setName( "level-coin" );
	//coin.load( "level select/coin.png" );
	
	if( cost != 0 )
	{
		sprite.setOffset( 3 );
		locked = true;
	}
	
	click.setID( "level-click" );
	click.load( "menu/click.wav", 50 );
}

void Level::setXY( int x, int y )
{
	sprite.setPosition( x, y );
	//text.setPosition( sprite.getLeft(), sprite.getTop() -5 -text.getHeight() );
	//coin.setPosition( sprite.getRight() -coin.getWidth(), sprite.getTop() -5 -coin.getHeight() );
}

	
void Level::draw( sf::RenderWindow* &window )
{
	window->draw( sprite.get() );
	//window->draw( text.get() );
	//window->draw( coin.get() );
}

sf::Uint8 Level::handle( sf::Event &event, int& money )
{
	bool correct = false;
	if( sprite.getAlpha() == 0xFF )
	{
		int x, y;
		
		if( !locked )
			sprite.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( sprite.checkCollision( x, y ) )
			{
				correct = true;
				if( !locked )
				{
					sprite.setOffset( 1 );
				}
			}
			else
				focus = false;
		}
		
		clicked = false;
		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( sprite.checkCollision( x, y ) )
			{
				if( money >= cost )
				{
					money -= cost;
					cost = 0;
					locked = false;
				}
				
				if( !locked )
				{
					sprite.setOffset( 2 );
					focus = true;
				}
					
				if( play )
					click.play();
					
				clicked = true;
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
			
			
		if( focus )
			sprite.setOffset( 2 );
	}
	
	
	if( clicked )
		return 2;
	if( correct )
		return 1;
		
	return 0;
}


string Level::getName()
{
	return name;
}

void Level::fadein( int i, int max )
{
	sprite.fadein( i, max );
	//text.fadein( i, max );
	//coin.fadein( i, max );
}

void Level::fadeout( int i, int min )
{
	sprite.fadeout( i, min );
	//text.fadeout( i, min );
	//coin.fadeout( i, min );
}



void Level::turn()
{
	play = !play;
}

void Level::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}

int Level::getWidth()
{
	return sprite.getWidth();
}

int Level::getHeight()
{
	return sprite.getHeight();
}

int Level::getX()
{
	return sprite.getX();
}

int Level::getY()
{
	return sprite.getY();
}

sf::Uint8 Level::getAlpha()
{
	return sprite.getAlpha();
}

int Level::getCost()
{
	return cost;
}

void Level::unlock()
{
	locked = false;
	cost = 0;
}

bool Level::islocked()
{
	return locked;
}