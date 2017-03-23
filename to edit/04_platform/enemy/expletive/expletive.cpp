#include "04_platform/enemy/expletive/expletive.h"
#include <fstream>

Expletive::Expletive()
{
	
}

Expletive::~Expletive()
{
	free();
}

void Expletive::free()
{
	if( !hits.empty() )
	{
		for( auto &i :hits )
		{
			i->free();
		}
		
		hits.clear();
	}
	
	if( !attacks.empty() )
	{
		for( auto &i :attacks )
		{
			i->free();
		}
		
		attacks.clear();
	}
}

int Expletive::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp +s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}



void Expletive::load( string name )
{
	free();
	
	string txt_chunks = "data/txt/enemy/sounds/" +name +".txt";
	
	fstream file;
	
	file.open( txt_chunks );
	if( file.bad() )
	{
		printf( "Something went wrong... %s [file]\n", txt_chunks.c_str() );
	}
	else
	{
		string line;
		int hit_number = 0;
		int attack_number = 0;
		
		file >> line;
		hit_number = strToInt( line );
		
		file >> line;
		attack_number = strToInt( line );
		
		for( int i = 0; i < hit_number; i++ )
		{
			hits.push_back( new Slab() );
			hits[ hits.size() -1 ]->setName( "expletive-" +name );
			hits[ hits.size() -1 ]->load( "data/04_platform/enemy/" +name +"/sounds/hit/" +to_string( i ) +".wav" );
		}
		
		for( int i = 0; i < attack_number; i++ )
		{
			attacks.push_back( new Slab() );
			attacks[ attacks.size() -1 ]->setName( "expletive-" +name );
			attacks[ attacks.size() -1 ]->load( "data/04_platform/enemy/" +name +"/sounds/attack/" +to_string( i ) +".wav" );
		}
	}
	file.close();
}

void Expletive::playHits()
{
	if( hits.size() > 0 )
	{
		if( hits[ 0 ]->isPlayable() )
		{
			hits[ rand()%hits.size() ]->play();
		}
	}
}

void Expletive::playAttacks()
{
	if( attacks.size() > 0 )
	{
		if( attacks[ 0 ]->isPlayable() )
		{
			attacks[ rand()%attacks.size() ]->play();
		}
	}
}



void Expletive::turnOn()
{
	for( auto &it :hits )
	{
		it->turnOn();
	}
	
	for( auto &it :attacks )
	{
		it->turnOn();
	}
}

void Expletive::turnOff()
{
	for( auto &it :hits )
	{
		it->turnOff();
	}
	
	for( auto &it :attacks )
	{
		it->turnOff();
	}
}

void Expletive::setVolume( int v )
{
	for( auto &it :hits )
	{
		it->setVolume( v );
	}
	
	for( auto &it :attacks )
	{
		it->setVolume( v );
	}
}