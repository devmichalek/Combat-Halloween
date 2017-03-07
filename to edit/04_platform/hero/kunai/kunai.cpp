/**
    kunai.h
    Purpose: class Kunai to contain textures, throw kunai, contains 5 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#include "04_platform/hero/kunai/kunai.h"
#include "04_platform/hero/kunai/damage.h"
#include <fstream>


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
}



void Kunai::load()
{
	free();
	
	scale = 0.5;
	vel = 4.0;
	
	fstream file;
	
	// Set explosive level.
	int explosive_level = 0;
	string path = "data/txt/skill/level_current.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Something went wrong with %s\n", path.c_str() );
	}
	else
	{
		string line;
		int counter = 4;
		while( file >> line )
		{
			if( counter == 0 )
			{
				explosive_level = stoi( line );
				// printf( "%d\n", explosive_level );
				
				if( explosive_level < 3 )		explosive_level = 31;
				else if( explosive_level < 5 )	explosive_level = 32;
				else							explosive_level = 33;
				break;
			}
			
			counter --;
		}
	}
	file.close();
	
	
	// Load sprites.
	for( unsigned i = 0; i < 5; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "kunai-sprites" );
		if( i == 3 )	sprites[ sprites.size() -1 ]->load( "data/04_platform/hero/shuriken/" +to_string( explosive_level ) +".png", 6 );
		else			sprites[ sprites.size() -1 ]->load( "data/04_platform/hero/shuriken/" +to_string( i ) +".png" );
	}
	
	
	// Max amount of kunai's is 5.
	for( int i = 0; i < 5; i++ )
	{
		bits.push_back( new Kunai_bit() );
	}
	
	
	// Temporary levels.
	vector <int> levels;
	path = "data/txt/skill/level_current.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Something went wrong with %s\n", path.c_str() );
	}
	else
	{
		string line;
		while( file >> line )
		{
			levels.push_back( stof( line ) );
		}
	}
	file.close();

	// Then set damage.
	path = "data/txt/skill/skill_values.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Something went wrong with %s\n", path.c_str() );
	}
	else
	{
		string line;
		float value = 0;
		int counter = 0;
		
		Damage DAMAGE;
		while( file >> line )
		{
			if( counter == 0 || counter == 4 || counter == 5 )
			{
				value = stof( line );
				damage.push_back( stof( DAMAGE.multiply( counter, value, levels[ counter ] ) ) );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			else if( counter == 2 )
			{
				value = stof( line );
				float newDamage = stof( DAMAGE.multiply( counter, value, levels[ counter ] ) ) *damage[ 0 ] /100;
				damage.push_back( newDamage );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			else if( counter == 3 )
			{
				value = stof( line );
				float newDamage = stof( DAMAGE.multiply( counter, value, levels[ counter ] ) ) *damage[ 0 ] /100;
				damage.push_back( newDamage +damage[ 0 ] );
				// printf( "%f\n", damage[ damage.size() -1 ] );
			}
			
			counter ++;
		}
	}
	file.close();
	levels.clear();
}

void Kunai::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( bits[ i ]->isActive() )
		{
			bits[ i ]->run();
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



void Kunai::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Kunai::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



unsigned Kunai::getSize()
{
	return bits.size();
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
		
	t_x = bits[ which ]->getX();
	if( bits[ which ]->getVel() > 0 )
	{
		t_x -= sprites[ bits[ which ]->getWhich() ]->getWidth();
	}
	
	t_y = bits[ which ]->getY();
	if( bits[ which ]->getWhich() == 3 )
	{
		t_y -= 30;
	}
	
	t_w = sprites[ bits[ which ]->getWhich() ]->getWidth();
	t_h = sprites[ bits[ which ]->getWhich() ]->getHeight();
	
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}

float Kunai::getDamage( int which )
{
	return damage[ bits[ which ]->getWhich() ];
}



void Kunai::destroy( int which )
{
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