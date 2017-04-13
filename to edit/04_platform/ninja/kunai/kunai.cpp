/**
    kunai.h
    Purpose: class Kunai to contain textures, throw kunai, contains 5 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#include "04_platform/ninja/kunai/kunai.h"
#include "04_platform/ninja/kunai/damage.h"
#include "file/file.h"


Kunai::Kunai()
{
	free();
}

Kunai::~Kunai()
{
	free();
}

void Kunai::free()
{
	vel = 0;
	scale = 0;
	
	if( !damage.empty() )
	{
		damage.clear();
	}
	
	if( !bits.empty() )
	{
		for( auto &it :bits )
		{
			it->free();
		}
		
		bits.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	kunai_effects.free();
}



void Kunai::load()
{
	free();
	
	scale = 0.5;
	vel = 4.0;
	
	MyFile file;
	
	// Set explosive level.
	int explosive_level = 0;
	file.load( "data/txt/skill/level_current.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = 4;
		while( file.get() >> line )
		{
			if( counter == 0 )
			{
				explosive_level = con::stoi( line );
				// printf( "%d\n", explosive_level );
				
				if( explosive_level < 3 )		explosive_level = 31;
				else if( explosive_level < 5 )	explosive_level = 32;
				else							explosive_level = 33;
				break;
			}
			
			counter --;
		}
	}
	file.free();
	
	// Load effects.
	kunai_effects.load( explosive_level );
	
	
	// Load sprites.
	for( unsigned i = 0; i < 5; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "kunai-sprites" );
		if( i == 3 )	sprites[ sprites.size() -1 ]->load( "data/04_platform/hero/kunai/" +con::itos( explosive_level ) +".png", 6 );
		else			sprites[ sprites.size() -1 ]->load( "data/04_platform/hero/kunai/" +con::itos( i ) +".png" );
	}
	
	
	// Max amount of kunai's is 5.
	for( int i = 0; i < 5; i++ )
	{
		bits.push_back( new Kunai_bit() );
	}
	
	
	// Temporary levels.
	vector <int> levels;
	file.load( "data/txt/skill/level_current.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			levels.push_back( con::stof( line.c_str() ) );
		}
	}
	file.free();

	// Then set damage.
	file.load( "data/txt/skill/skill_values.txt" );
	if( file.is_good() )
	{
		string line;
		float value = 0;
		int counter = 0;
		
		Damage DAMAGE;
		while( file.get() >> line )
		{
			if( counter == 0 || counter == 4 || counter == 5 )
			{
				value = con::stof( line.c_str() );
				damage.push_back( con::stof( DAMAGE.multiply( counter, value, levels[ counter ] ).c_str() ) );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			else if( counter == 2 )
			{
				value = con::stof( line.c_str() );
				float newDamage = con::stof( DAMAGE.multiply( counter, value, levels[ counter ] ).c_str() ) *damage[ 0 ] /100;
				damage.push_back( newDamage );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			else if( counter == 3 )
			{
				value = con::stof( line.c_str() );
				float newDamage = con::stof( DAMAGE.multiply( counter, value, levels[ counter ] ).c_str() ) *damage[ 0 ] /100;
				damage.push_back( newDamage +damage[ 0 ] );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			counter ++;
		}
	}
	file.free();
	levels.clear();
}

void Kunai::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( bits[ i ]->isActive() )
		{
			sprites[ bits[ i ]->getWhich() ]->setPosition( bits[ i ]->getX(), bits[ i ]->getY() );
			
			if( bits[ i ]->getVel() < 0 )
			{
				sprites[ bits[ i ]->getWhich() ]->setScale( scale, scale );
			}
			else if( bits[ i ]->getVel() > 0 )
			{
				sprites[ bits[ i ]->getWhich() ]->setScale( -scale, scale );
			}
			
			if( bits[ i ]->getWhich() == 3 )
			{
				sprites[ bits[ i ]->getWhich() ]->setOffset( bits[ i ]->getOffset() );
			}
			window->draw( sprites[ bits[ i ]->getWhich() ]->get() );
		}
	}
	
	
}

void Kunai::drawEffects( sf::RenderWindow* &window  )
{
	kunai_effects.draw( window );
}

void Kunai::mechanics()
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( bits[ i ]->isActive() )
		{
			bits[ i ]->run();
		}
	}
	
	kunai_effects.mechanics();
}



void Kunai::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
	
	kunai_effects.fadein( v, max );
}

void Kunai::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
	
	kunai_effects.fadeout( v, min );
}



unsigned Kunai::getSize()
{
	return bits.size();
}

bool Kunai::isActive( int which )
{
	return bits[ which ]->isActive();
}

int Kunai::getX( int which )
{
	int x = bits[ which ]->getX();
	
	if( bits[ which]->getVel() > 0 )
	{
		x -= getW( which );
	}
	
	return x;
}

int Kunai::getW( int which )
{
	return sprites[ bits[ which ]->getWhich() ]->getWidth();
}

Rect* Kunai::getRect( int which )
{
	Rect* rect = new Rect;
	// Temporary.
	int t_x, t_y;	
	int t_w, t_h;
	
	t_w = sprites[ bits[ which ]->getWhich() ]->getWidth();
	t_h = sprites[ bits[ which ]->getWhich() ]->getHeight();
		
	t_x = bits[ which ]->getX();
	if( bits[ which ]->getVel() > 0 )
	{
		t_x -= sprites[ bits[ which ]->getWhich() ]->getWidth();
	}
	
	t_y = bits[ which ]->getY();
	if( bits[ which ]->getWhich() == 3 )
	{
		t_y -= 30;
		t_w /= 2;
	}
	
	
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}

Rect* Kunai::getEffectRect( int which )
{
	Rect* rect = new Rect;
	// Temporary.
	int t_x, t_y;	
	int t_w, t_h;
	
	t_w = sprites[ bits[ which ]->getWhich() ]->getWidth();
	t_h = sprites[ bits[ which ]->getWhich() ]->getHeight();
		
	t_x = bits[ which ]->getX();
	if( bits[ which ]->getVel() > 0 )
	{
		t_x -= sprites[ bits[ which ]->getWhich() ]->getWidth();
	}
	
	t_y = bits[ which ]->getY();
	
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}

float Kunai::getDamage( int which )
{
	// printf( "%f\n", damage[ bits[ which ]->getWhich() ] );
	return damage[ bits[ which ]->getWhich() ];
}

bool Kunai::isHealKunai( int which )
{
	// printf( "%d\n", bits[ which ]->getWhich() );
	if( bits[ which ]->getWhich() == 4 )
	{
		return true;
	}
	
	return false;
}

bool Kunai::isExplosiveKunai( int which )
{
	// printf( "%d\n", bits[ which ]->getWhich() );
	if( bits[ which ]->getWhich() == 3 )
	{
		return true;
	}
	
	return false;
}

bool Kunai::isStuntKunai( int which )
{
	// printf( "%d\n", bits[ which ]->getWhich() );
	if( bits[ which ]->getWhich() == 1 )
	{
		return true;
	}
	
	return false;
}




void Kunai::destroy( int which )
{
	if( bits[ which ]->getWhich() > 0 && bits[ which ]->getWhich() < 4 )
	{
		kunai_effects.run( bits[ which ]->getWhich() -1, getEffectRect( which ) );
	}
	
	bits[ which ]->free();
}

void Kunai::throwed( int x, int y, bool right, int which )
{
	sf::Uint8 add = 50;
	if( which == 3 )
	{
		add -= 20;
	}
	
	for( auto &it :bits )
	{
		if( !it->isActive() )
		{
			if( which )
			{
				it->setAnimation( 6, 8 );
			}
			
			if( right )	it->setPosition( x +30, y +add, vel, which );
			else		it->setPosition( x -30, y +add, -vel, which );

			break;
		}
	}
}

void Kunai::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :bits )
		{
			it->moveX( vel );
		}
		
		kunai_effects.moveX( vel );
	}
	else if( direction == 2 )
	{
		for( auto &it :bits )
		{
			it->moveX( -vel );
		}
		
		kunai_effects.moveX( -vel );
	}
}

void Kunai::undoFall( sf::Uint8 add )
{
	for( auto &it :bits )
	{
		it->moveX( add );
	}
	
	kunai_effects.moveX( add );
}

void Kunai::setColor( sf::Color color )
{
	for( auto &it :sprites )
	{
		it->setColor( color );
	}
	
	kunai_effects.setColor( color );
}



void Kunai::turn()
{
	kunai_effects.turn();
}

void Kunai::turnOn()
{
	kunai_effects.turnOn();
}

void Kunai::turnOff()
{
	kunai_effects.turnOff();
}

void Kunai::setVolume( int v )
{
	kunai_effects.setVolume( v );
}