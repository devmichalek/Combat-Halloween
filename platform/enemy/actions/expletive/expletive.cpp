#include "expletive.h"
#include "file/file.h"

Expletive::Expletive()
{
	free();
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



void Expletive::load( string name )
{
	free();
	
	MyFile file;
	
	file.load( "data/txt/enemy/sounds/" +name +".txt" );
	if( file.is_good() )
	{
		string line;
		int hit_number = 0;
		int attack_number = 0;
		
		file.get() >> line;
		hit_number = con::stoi( line );
		
		file.get() >> line;
		attack_number = con::stoi( line );
		
		for( int i = 0; i < hit_number; i++ )
		{
			hits.push_back( new Slab() );
			hits[ hits.size() -1 ]->setName( "expletive-" +name );
			hits[ hits.size() -1 ]->load( "data/platform/enemy/" +name +"/sounds/hit/" +con::itos( i ) +".wav" );
		}
		
		for( int i = 0; i < attack_number; i++ )
		{
			attacks.push_back( new Slab() );
			attacks[ attacks.size() -1 ]->setName( "expletive-" +name );
			attacks[ attacks.size() -1 ]->load( "data/platform/enemy/" +name +"/sounds/attack/" +con::itos( i ) +".wav" );
		}
	}
	file.free();
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



void Expletive::turn()
{
	for( auto &it :hits )
	{
		it->turn();
	}
	
	for( auto &it :attacks )
	{
		it->turn();
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