#include "pause.h"
#include "file/file.h"

Pause::Pause()
{
	free();
}

Pause::~Pause()
{
	free();
}

void Pause::free()
{
	text.free();
	sprite.free();
	
	if( !info.empty() )
	{
		for( auto &it :info )
		{
			it->free();
		}
		
		info.clear();
	}
	
	if( !info_a.empty() )
	{
		for( auto &it :info_a )
		{
			it->free();
		}
		
		info_a.clear();
	}
	
	focus = false;
	paused = false;
	allowed = false;
	c = t = 0;
	dead = false;
}

void Pause::reset()
{
	sprite.setAlpha( 225 );
	int alpha = 180;
	text.setAlpha( alpha );
	
	for( auto &it :info )
	{
		it->setAlpha( alpha );
	}
	
	for( auto &it :info_a )
	{
		it->setAlpha( alpha );
	}
	
	focus = false;
	paused = false;
	allowed = false;
	c = 0;
	dead = false;
}


void Pause::load( unsigned screen_w, unsigned screen_h, int FPS )
{
	free();
	
	int alpha = 225;
	text.setName( "pause-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 100, 255, 255, 255 );
	text.setText( "Paused" );
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/5 );
	text.setAlpha( alpha );
	
	sprite.setName( "pause-sprite" );
	sprite.create( screen_w, screen_h );
	sprite.setColor( sf::Color( 0, 0, 0, 180 ) );
	sprite.setAlpha( 180 );
	
	for( unsigned i = 0; i < 18; i++ )
	{
		info.push_back( new MyText() );
		info[ i ]->setName( "keyboard-text nr " + con::itos( i ) );
		info[ i ]->setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}
	
	// Set texts.
	info[ 0 ]->setText( "Move left" );
	info[ 2 ]->setText( "Move right" );
	info[ 4 ]->setText( "Jump" );
	info[ 6 ]->setText( "Slide" );
	info[ 8 ]->setText( "Climb" );
	info[ 10 ]->setText( "Attack" );
	info[ 12 ]->setText( "Jump attack" );
	info[ 14 ]->setText( "Throw" );
	info[ 16 ]->setText( "Jump throw" );
	
	// Load temporary keys.
	MyFile file;
	file.load( "data/txt/keyboard/keyboard_temporary.txt" );
	if( file.is_good() )
	{
		int counter = 1;
		
		string buf;
		while( file.get() >> buf )
		{
			string newName = "";
			
			newName += getName( con::stoi( buf ) );
			
			file.get() >> buf;
			if( con::stoi( buf ) != -1 )
			{
				newName += " + " + getName( con::stoi( buf ) );
			}
			
			info[ counter ]->setText( newName );
			counter += 2;
		}
	}
	file.free();
	
	// Positions.
	int y = screen_h /2.2;
	int y2 = screen_h /1.5;
	info[ 0 ]->setPosition( screen_w /10, y );
	info[ 1 ]->setPosition( screen_w /4, y );
	for( int i = 2; i < 8; i += 2 )
	{
		info[ i ]->setPosition( screen_w /10, info[ i -2 ]->getBot() + 10 );
		info[ i +1 ]->setPosition( screen_w /4, info[ i -2 ]->getBot() + 10 );
	}
	
	info[ 8 ]->setPosition( screen_w /1.754, y -5 );
	info[ 9 ]->setPosition( screen_w /1.25, y -5 );
	for( unsigned i = 10; i < info.size() -1; i += 2 )
	{
		info[ i ]->setPosition( screen_w /1.754, info[ i -2 ]->getBot() + 10 );
		info[ i +1 ]->setPosition( screen_w /1.25, info[ i -2 ]->getBot() + 10 );
	}
	
	for( unsigned i = 0; i < info.size(); i++ )
	{
		info[ i ]->setAlpha( alpha );
	}
	
	
	for( int i = 0; i < 8; i++ )
	{
		info_a.push_back( new MyText() );
		info_a[ i ]->setName( "information-text nr " + con::itos( i ) );
		info_a[ i ]->setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0x98, 0x98, 0x98 );
	}
	
	
	info_a[ 0 ]->setText( "Unpause" );
	info_a[ 1 ]->setText( "p" );
	
	info_a[ 2 ]->setText( "Quit" );
	info_a[ 3 ]->setText( "press q for 4 seconds" );
	
	info_a[ 4 ]->setText( "Back in quit log" );
	info_a[ 5 ]->setText( "b" );
	
	info_a[ 6 ]->setText( "Combo #1 - Jump +Jump attack" );
	info_a[ 7 ]->setText( "Combo #2 - Jump +Jump attack +Jump throw" );
	
	info_a[ 0 ]->setPosition( screen_w /10, y2 );
	info_a[ 1 ]->setPosition( screen_w /4, y2 );
	info_a[ 2 ]->setPosition( screen_w /10, info_a[ 0 ]->getBot() + 10 );
	info_a[ 3 ]->setPosition( screen_w /4, info_a[ 1 ]->getBot() + 10 );
	
	info_a[ 4 ]->setPosition( screen_w /1.754, y2 );
	info_a[ 5 ]->setPosition( screen_w /1.25, y2 );
	info_a[ 6 ]->setPosition( screen_w /1.754, info_a[ 4 ]->getBot() + 10 );
	info_a[ 7 ]->setPosition( screen_w /1.754, info_a[ 6 ]->getBot() + 10 );
	
	
	for( unsigned i = 0; i < info_a.size(); i++ )
	{
		info_a[ i ]->setAlpha( alpha );
	}
	
	t = FPS *2.5;
}

void Pause::draw( sf::RenderWindow* &window )
{
	if( paused )
	{
		window->draw( sprite.get() );
		window->draw( text.get() );
		
		for( auto &it :info )
		{
			window->draw( it->get() );
		}
		
		for( auto &it :info_a )
		{
			window->draw( it->get() );
		}
		
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 16 ) ) )
		{
			c ++;
		}
		else
		{
			c = 0;
		}
		
		if( c > t )
		{
			dead = true;
		}
	}
}

void Pause::handle( sf::Event& event )
{
	if( allowed )
	{
		if( event.type == sf::Event::KeyPressed && !focus )
		{
			if( event.key.code == 15 )
			{
				focus = true;
				paused = !paused;
			}
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			if( event.key.code == 15 )
			{
				focus = false;
			}
		}
	}
	
	if( paused )
	{
		allowed = true;
	}
	else
	{
		allowed = false;
	}
}

void Pause::fadeout( int j, int min )
{
	sprite.fadeout( j, min );
	text.fadeout( j, min );
	
	for( auto &it :info )
	{
		it->fadeout( j, min );
	}
	
	for( auto &it :info_a )
	{
		it->fadeout( j, min );
	}
}


bool Pause::isPaused()
{
	return paused;
}

void Pause::allow()
{
	allowed = true;
}

string Pause::getName( int n )
{
	string name = "";
	
	if( n >= 0 && n <= 25 )	// from A to Z
	{
		// in ASCII 97 means letter 'a'
		name = static_cast <char> ( n + 97 );
	}
	else
	{
		switch( n )
		{
			case 71: name = "left";	 	break;
			case 72: name = "right";	break;
			case 73: name = "up";		break;
			case 74: name = "down";		break;
			
			case 57: name = "space";	break;
			case 58: name = "return";	break;
			
			case 37: name = "l ctrl";	break;
			case 41: name = "r ctrl";	break;
			
			case 38: name = "l shift";	break;
			case 42: name = "r shift";	break;
			
			case 39: name = "l alt";	break;
			case 43: name = "r alt";	break;
		}
	}
	
	return name;
}

bool Pause::isDead()
{
	return dead;
}