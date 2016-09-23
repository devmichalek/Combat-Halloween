#include "level.h"

Level::Level()
{
	cost = 0;
	name = -1;
	clicked = false;
	locked = false;
	focus = false;
	play = true;
}

Level::~Level()
{
	cost = 0;
	name = -1;
	clicked = false;
	locked = false;
	focus = false;
	play = true;
	
	sprite.free();
	click.free();
}

	
void Level::load( int name, int cost )
{
	this->name = name;
	this->cost = cost;
	
	sprite.setName( "level-" + to_string( name ) );
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

void Level::handle( sf::Event &event, int& money )
{
	if( !locked && sprite.getAlpha() == 0xFF )
	{
		int x, y;
		sprite.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( sprite.checkCollision( x, y ) )
				sprite.setOffset( 1 );
			else
				focus = false;
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( sprite.checkCollision( x, y ) )
			{
				sprite.setOffset( 2 );
					
				if( play )
					click.play();
						
				focus = true;
				clicked = true;
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
			focus = false;
			
		if( focus )
			sprite.setOffset( 2 );
	}
}

	
void Level::buy( int& money )
{
	if( cost != 0 )
	{
		if( money >= cost );
		{
			money -= cost;
			cost = 0;
		}
	}
}

int Level::getName()
{
	if( cost == 0 );
		return name;
		
	return -1;
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
