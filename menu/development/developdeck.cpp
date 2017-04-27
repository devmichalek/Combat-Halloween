/**
    development.h
    Purpose: class Development - contains develops.

    @author Adrian Michalek
    @version 2017.02.20
	@email adrmic98@gmail.com
*/

#include "menu/development/developdeck.h"
#include "file/file.h"

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
	y_state = 0;
	bot = 0;
	wallet = 0;
	change = false;
	
	line.free();
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
		}
		
		texts.clear();
	}
	
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
	
	if( !costs.empty() )
	{
		costs.clear();
	}
	
	if( !values.empty() )
	{
		values.clear();
	}
}



void Development::load( int bot, int screen_h )
{
	free();
	
	// Set actual values.
	MyFile file;
	file.load( "data/txt/skill/skill_values.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			values.push_back( con::stof( line.c_str() ) );
		}
	}
	file.free();
	
	// Set costs.
	file.load( "data/txt/skill/skill_costs.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			costs.push_back( con::stof( line.c_str() ) );
		}
	}
	file.free();
	
	int space = 70;
	int max = 6;
	
	for( int i = 0; i < max; i++ )
	{
		develops.push_back( new Develop() );
		develops[ develops.size() -1 ]->load( i, bot +( i*space ) );
	}
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "development-texts nr" +con::itos( i ) );
		
		
		if( i == WALLET )	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
		else if( i == MONEY )	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 27, 0xFF, 0xD8, 0x00 );
		else	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	}
	
	// set other stuff
	y_state = bot -80;
	
	texts[ SKILL ]->setText( "Skill" );
	texts[ LEVEL ]->setText( "Level" );
	texts[ VALUE ]->setText( "Value" );
	texts[ UPGRADE ]->setText( "Upgrade/Cost" );
	texts[ WALLET ]->setText( "Wallet: " );
	texts[ MONEY ]->setText( " " );
	
	// Set line.
	line.setName( "development-line" );
	line.create( 2, screen_h *2 /3 -65 );
	
	// Set bot.
	this->bot = bot;
	
	// Reload.
	reloadTxt();
}

void Development::reloadTxt()
{
	if( !levels.empty() )
	{
		levels.clear();
	}
	
	// Set actual levels.
	MyFile file;
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
	
	
	// Load bank.
	file.load( "data/txt/money/bank.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		if( line.size() > 8 )
		{
			wallet = 99999999;
		}
		else
		{
			wallet = con::stof( line.c_str() );
		}
	}
	file.free();
	
	Damage damage;
	for( unsigned i = 0; i < develops.size(); i++ )
	{
		develops[ i ]->setActual( levels[ i ], damage.multiply( i, values[ i ], levels[ i ] ) );
		develops[ i ]->setCost( multiplyCost( i ) );
	}
	
	texts[ MONEY ]->setText( con::itos( wallet ) );
	texts[ MONEY ]->reloadPosition();
}

void Development::draw( sf::RenderWindow* &window )
{
	window->draw( line.get() );
	
	for( auto &it :texts )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :develops )
	{
		it->draw( window );
	}
}

void Development::handle( sf::Event &event, int r_x, int r_y )
{
	for( unsigned i = 0; i < develops.size(); i++ )
	{
		if( develops[ i ]->ableToUpgrade( wallet ) )
		{
			develops[ i ]->handle( event, r_x, r_y );
			if( develops[ i ]->getLevel() != levels[ i ] )
			{
				levels[ i ] = develops[ i ]->getLevel();
				wallet -= develops[ i ]->getCost();
				develops[ i ]->setCost( multiplyCost( i ) );
				Damage damage;
				develops[ i ]->setActual( levels[ i ], damage.multiply( i, values[ i ], levels[ i ] ) );
				
				texts[ MONEY ]->setText( con::itos( wallet ) );
				texts[ MONEY ]->reloadPosition();
				
				// save file
				MyFile file;
				file.load( "data/txt/money/bank.txt", std::ios::out );
				if( file.is_good() )
				{
					file.get() << con::itos( wallet ) << "\n";
				}
				file.free();
				
				file.load( "data/txt/skill/level_current.txt", std::ios::out );
				if( file.is_good() )
				{
					for( unsigned j = 0; j < levels.size(); j++ )
					{
						file.get() << con::itos( levels[ j ] ) << "\n";
					}
					// printf( "happen\n" );
				}
				file.free();
				change = true;
				
				break;
			}
		}
	}
}



void Development::fadein( int i, int max )
{
	line.fadein( i, max );
	
	for( auto &it :texts )
	{
		it->fadein( i, max );
	}
	
	for( auto &it :develops )
	{
		it->fadein( i, max );
	}
}

void Development::fadeout( int i, int min )
{
	line.fadeout( i, min );
	
	for( auto &it :texts )
	{
		it->fadeout( i, min );
	}
	
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
		value *= 4;
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

void Development::turnOn()
{
	for( auto &it :develops )
	{
		it->turnOn();
	}
}

void Development::turnOff()
{
	for( auto &it :develops )
	{
		it->turnOff();
	}
}



bool Development::isChange()
{
	if( change )
	{
		change = false;
		return true;
	}
	
	return false;
}

void Development::setWallet( int money )
{
	wallet = money;
	texts[ MONEY ]->setText( con::itos( wallet ) );
	texts[ MONEY ]->reloadPosition();
}

int Development::getWallet()
{
	return wallet;
}



void Development::setScale( float s_x, float s_y )
{
	line.setBasicScale( s_x, s_y );
	line.setScale();
	
	for( auto &it :texts )
	{
		it->setBasicScale( s_x, s_y );
		it->setScale();
	}
	
	for( auto &it :develops )
	{
		it->setScale( s_x, s_y );
	}
}

void Development::setView( int w, int h, int r_x, int r_y )
{
	line.setPosition( w /1.436 +r_x, (y_state +50) *line.getYScale() +r_y );
	
	texts[ SKILL ]->setPosition( w /12.5 +r_x, y_state *texts[ SKILL ]->getYScale() +r_y );
	texts[ UPGRADE ]->setPosition( w /1.37 +r_x, y_state *texts[ UPGRADE ]->getYScale() +r_y );
	texts[ LEVEL ]->setPosition( w /3.355 +r_x, y_state *texts[ LEVEL ]->getYScale() +r_y );
	texts[ VALUE ]->setPosition( w /2.178 +r_x, y_state *texts[ VALUE ]->getYScale() +r_y );
	
	
	texts[ WALLET ]->setPosition( 10 *texts[ WALLET ]->getXScale() +r_x, h -45*texts[ WALLET ]->getYScale() +r_y );
	texts[ MONEY ]->setPosition( 140 *texts[ MONEY ]->getXScale() +r_x, h -42 *texts[ MONEY ]->getYScale() +r_y );

	for( auto &it :develops )
	{
		it->setView( w, h, r_x, r_y );
	}
}