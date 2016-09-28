#include "level.h"

Level::Level()
{
	cost = 0;
	name = "";

	state = 0;
	
	// sound states
	focus = false;
	play = true;
}

Level::~Level()
{
	cost = 0;
	name = "";

	state = 0;
	
	focus = false;
	play = true;
	
	one.free();
	two.free();
	click.free();
	unlocking.free();
}

	
void Level::load( string name, int cost )
{
	this->name = name;
	this->cost = cost;
	
	one.setName( "level-" + name );
	one.load( "level select/level.png", 4 );
	one.setScale( 0.6, 0.6 );
	
	two.setName( "level-2" + name );
	two.load( "level select/level.png", 4 );
	two.setScale( 0.6, 0.6 );
	

	if( cost != 0 )
	{
		one.setOffset( 3 );
		state = 0;
	}

	
	click.setID( "level-click" );
	click.load( "menu/click.wav", 50 );
	
	lock.setID( "level-lock" );
	lock.load( "level select/lock.wav", 50 );
	
	unlocking.setID( "level-unlocking" );
	unlocking.load( "level select/unlock.wav", 50 );
}

void Level::setXY( int x, int y )
{
	one.setPosition( x, y );
	two.setPosition( x, y );
}

	
void Level::draw( sf::RenderWindow* &window )
{
	window->draw( two.get() );
	window->draw( one.get() );
	
	if( state == 1 )
	{
		one.fadeout( 3 );
		
		if( one.getAlpha() == 0x00 )
			state = 2;
	}
	
}

sf::Uint8 Level::handle( sf::Event &event, int& money )
{
	int x, y;
	sf::Uint8 result = 0;
	
	if( one.getAlpha() == 0xFF )	// state == 0
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( one.checkCollision( x, y ) )
			{
				if( money >= cost )
				{
					money -= cost;
					cost = 0;
					state = 1;
					result = 3;
					
					if( play )
						unlocking.play();
				}
				else
				{
					if( play )
						lock.play();
				}
			}
		}
		else if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			if( one.checkCollision( x, y ) )
			{
				result = 1;
			}
		}
	}
	else if( state == 2 )
	{
		two.setOffset( 0 );
		
		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( two.checkCollision( x, y ) )
			{
				if( play )
					click.play();
					
				focus = true;
				result = 4;
			}
		}
		
		else if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( two.checkCollision( x, y ) )
			{
				two.setOffset( 1 );
				result = 2;
			}
			else
				focus = false;
		}
		
		else if( event.type == sf::Event::MouseButtonReleased )
			focus = false;
			
		if( focus )
			two.setOffset( 2 );
	}

	return result;
}










void Level::fadein( int i, int max )
{
	if( state == 0 )
	{
		one.fadein( i, max );
		if( one.getAlpha() == max )
			two.setAlpha( max );
	}
}

void Level::fadeout( int i, int min )
{
	one.fadeout( i, min );
	
	if( one.getAlpha() > 0 )
		two.fadeout( i+4, min );
	else
		two.fadeout( i, min );
}






int Level::getCost()
{
	return cost;
}

string Level::getName()
{
	return name;
}

void Level::unlock()
{
	cost = 0;
	state = 2;
	two.setAlpha( 0xFF );
	one.setAlpha( 0x00 );
}

bool Level::isReady()
{
	if( state == 2 )
		return true;
	else if( state == 0 && one.getAlpha() == 0xFF )
		return true;
		
	return false;
}






int Level::getWidth()
{
	return one.getWidth();
}

int Level::getHeight()
{
	return one.getHeight();
}

int Level::getX()
{
	return one.getX();
}

int Level::getY()
{
	return one.getY();
}

void Level::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
	lock.setVolume( volume );
}