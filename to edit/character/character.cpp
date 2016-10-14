#include "character/character.h"

Character::Character()
{
	result = -1;
	ready = false;
	focus = false;
	focus2 = false;
}

Character::~Character()
{
	free();
}

void Character::free()
{
	result = -1;
	ready = false;
	
	one.free();
	two.free();
	
	one_t.free();
	one_t.free();
	
	click.free();
	focus2 = false;
}


void Character::load( int screen_w, int screen_h )
{
	one.setName( "character-one" );
	one.load( "data/sprites/character/boy.png" );
	one.center( 0, 100, screen_w/2, screen_h );
	
	two.setName( "character-two" );
	two.load( "data/sprites/character/girl.png" );
	two.center( screen_w/2, 100, screen_w/2, screen_h ); //RUDA <3
	
	click.setID( "music_button-click" );
	click.load( "data/sounds/click.wav", 50 );
	
	
	one_t.setID( "character-one_t" );
	one_t.setFont( "data/fonts/Jaapokki-Regular.otf", 37, 255, 255, 255 );
	one_t.setText( "NINJA ADVENTURE" );
	one_t.center( screen_w/2, 400 );
	
	two_t.setID( "character-two_t" );
	two_t.setFont( "data/fonts/Jaapokki-Regular.otf", 37, 255, 255, 255 );
	two_t.setText( "NINJA GIRL" );
	two_t.center( screen_w/2, 400, screen_w/2 );
}

void Character::draw( sf::RenderWindow* &window )
{
	window->draw( one.get() );
	window->draw( two.get() );
	
	window->draw( one_t.get() );
	window->draw( two_t.get() );
	
	if( !ready )
	{
		if( focus )
			one.setAlpha( 170 );
		if( focus2 )
			two.setAlpha( 170 );
	}
	
	
}

void Character::handle( sf::Event &event )
{
	int x = -1, y = -1;
	
	if( event.type == sf::Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		
		if( one.checkCollision( x, y ) )
		{
			focus = true;
		}
		else
		{
			focus = false;
		}
		
		if( two.checkCollision( x, y ) )
		{
			focus2 = true;
		}
		else
		{
			focus2 = false;
		}
	}
	
	else if( event.type == sf::Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
		
		if( one.checkCollision( x, y ) )
		{
			result = 0;
			ready = true;
			
			if( play )
				click.play();
		}
		else if( two.checkCollision( x, y ) )
		{
			result = 1;
			ready = true;
			
			if( play )
				click.play();
		}
	}
}

bool Character::nextState()
{
	return ready;
}
	
int Character::getResult()
{
	if( result != -1 )
	{
		int save = result;
		
		result = -1;
		ready = false;
		return save;
	}
	
	return -1;
}

void Character::fadein( int j, int max )
{
	one.fadein( j, max );
	two.fadein( j, max );
	one_t.fadein( j, max );
	two_t.fadein( j, max );
}

void Character::fadeout( int j, int min )
{
	one.fadeout( j, min );
	two.fadeout( j, min );
	one_t.fadeout( j, min );
	two_t.fadeout( j, min );
}

int Character::getAlpha()
{
	return one.getAlpha();
}