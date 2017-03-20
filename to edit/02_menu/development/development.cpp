/**
    development.h
    Purpose: class Development - contains develops.

    @author Adrian Michalek
    @version 2017.02.20
	@email adrmic98@gmail.com
*/

#include "02_menu/development/development.h"
#include <fstream>

Development::Development()
{
	free();
}

Development::~Development()
{
	free();
}

void Development::free()
{
	if( !develops.empty() )
	{
		for( auto &it :develops )
		{
			it->free();
		}
		
		develops.clear();
	}
	
	if( !levels.empty() )
	{
		levels.clear();
	}
	
	if( !values.empty() )
	{
		values.clear();
	}
	
	if( !costs.empty() )
	{
		costs.clear();
	}
	
	bank = 0;
	bot = 0;
	
	skill.free();
	level.free();
	value.free();
	upgrade.free();
	
	bank_text.free();
	money.free();
}



void Development::load( int bot, int screen_h )
{
	free();
	
	// Set actual values.
	string path = "data/txt/skill/skill_values.txt";
	fstream file;
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		while( file >> line )
		{
			values.push_back( stof( line ) );
		}
	}
	file.close();
	
	// Set costs.
	path = "data/txt/skill/skill_costs.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		while( file >> line )
		{
			costs.push_back( stof( line ) );
		}
	}
	file.close();
	
	int space = 70;
	int max = 6;
	int main_x = 80;
	
	for( int i = 0; i < max; i++ )
	{
		develops.push_back( new Develop() );
		develops[ develops.size() -1 ]->load( main_x, i, bot +( i*space ) );
	}
	
	
	
	// set other stuff
	int our_bot = bot -80;
	skill.setName( "development-skill" );
	skill.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	skill.setText( "Skill" );
	skill.setPosition( main_x, our_bot );
	
	level.setName( "development-level" );
	level.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	level.setText( "Level" );
	level.setPosition( skill.getRight() +265, our_bot );
	
	value.setName( "development-value" );
	value.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	value.setText( "Value" );
	value.setPosition( level.getRight() +85, our_bot );
	
	upgrade.setName( "development-upgrade" );
	upgrade.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	upgrade.setText( "Upgrade/Cost" );
	upgrade.setPosition( value.getRight() +110, our_bot );
	
	bank_text.setName( "development-bank_text" );
	bank_text.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	bank_text.setText( "Wallet: " );
	bank_text.setPosition( 10, screen_h -40 );
	
	money.setName( "development-money" );
	money.setFont( "data/00_loading/Jaapokki-Regular.otf", 27, 255, 255, 255 );
	money.setText( "0" );
	money.setColor( 0xFF, 0xD8, 0x00 );
	money.setPosition( bank_text.getRight() +20, screen_h -37 );
	
	this->bot = bot;
	reloadTxt();
}

void Development::reloadTxt()
{
	if( !levels.empty() )
	{
		levels.clear();
	}
	
	// Set actual levels.
	fstream file;
	string path = "data/txt/skill/level_current.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
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
	
	
	// Load bank.
	path = "data/txt/money/bank.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		file >> line;
		if( line.size() > 8 )
		{
			bank = 99999999;
		}
		else
			bank = stof( line );
	}
	file.close();
	
	for( unsigned i = 0; i < develops.size(); i++ )
	{
		develops[ i ]->setActual( levels[ i ], damage.multiply( i, values[ i ], levels[ i ] ) );
		develops[ i ]->setCost( multiplyCost( i ) );
	}
	
	money.setText( to_string( bank ) );
	money.reloadPosition();
}

void Development::draw( sf::RenderWindow* &window )
{
	window->draw( skill.get() );
	window->draw( level.get() );
	window->draw( value.get() );
	window->draw( upgrade.get() );
	window->draw( bank_text.get() );
	window->draw( money.get() );
	
	for( auto &it :develops )
	{
		it->draw( window );
	}
}

void Development::handle( sf::Event &event )
{
	for( unsigned i = 0; i < develops.size(); i++ )
	{
		if( develops[ i ]->ableToUpgrade( bank ) )
		{
			develops[ i ]->handle( event );
			if( develops[ i ]->getLevel() != levels[ i ] )
			{
				levels[ i ] = develops[ i ]->getLevel();
				bank -= develops[ i ]->getCost();
				develops[ i ]->setCost( multiplyCost( i ) );
				develops[ i ]->setActual( levels[ i ], damage.multiply( i, values[ i ], levels[ i ] ) );
				
				money.setText( to_string( bank ) );
				money.reloadPosition();
				
				// save file
				fstream file;
				file.open( "data/txt/money/bank.txt", std::ios::out );
				if( file.bad() )
				{
					printf( "Cannot open file\n" );
				}
				else
				{
					file << to_string( bank ) << "\n";
				}
				file.close();
				
				file.open( "data/txt/skill/level_current.txt", std::ios::out );
				if( file.bad() )
				{
					printf( "Cannot open file\n" );
				}
				else
				{
					for( unsigned j = 0; j < levels.size(); j++ )
					{
						file << to_string( levels[ j ] ) << "\n";
					}
					// printf( "happen\n" );
				}
				file.close();
				
				break;
			}
		}
	}
}



void Development::fadein( int i, int max )
{
	skill.fadein( i, max );
	level.fadein( i, max );
	value.fadein( i, max );
	upgrade.fadein( i, max );
	
	bank_text.fadein( i, max );
	money.fadein( i, max );
	
	for( auto &it :develops )
	{
		it->fadein( i, max );
	}
}

void Development::fadeout( int i, int min )
{
	skill.fadeout( i, min );
	level.fadeout( i, min );
	value.fadeout( i, min );
	upgrade.fadeout( i, min );
	
	bank_text.fadeout( i, min );
	money.fadeout( i, min );
	
	for( auto &it :develops )
	{
		it->fadeout( i, min );
	}
}

float Development::multiplyCost( int which )
{
	float value = costs[ which ];
	
	for( int i = 0; i < levels[ which ]; i++ )
	{
		value *= 2.1;
	}
	
	return value;
}

void Development::setVolume( int volume )
{
	for( auto &it :develops )
	{
		it->setVolume( volume );
	}
}

void Development::turn()
{
	for( auto &it :develops )
	{
		it->turn();
	}
}