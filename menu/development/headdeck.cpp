/**
    headdeck.h
    Purpose: class Headdeck - bunch of heads

    @author Adrian Michalek
    @version 2017.04.11
	@email adrmic98@gmail.com
*/

#include "menu/development/headdeck.h"
#include "file/file.h"

Headdeck::Headdeck()
{
	free();
}

Headdeck::~Headdeck()
{
	free();
}

void Headdeck::free()
{
	y_state = 0;
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
	
	if( !heads.empty() )
	{
		for( auto &it :heads )
		{
			it->free();
		}
		
		heads.clear();
	}
}



void Headdeck::load( int y, unsigned w, unsigned h )
{
	free();
	
	// Set y...
	y_state = y;
	
	// Set line.
	line.setName( "headdeck-line" );
	line.create( 2, 420 );
	
	// Set texts.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "headdeck-text nr" +con::itos( i ) );
		if( i == WALLET )	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
		else if( i == MONEY )	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 27, 0xFF, 0xD8, 0x00 );
		else				texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	}
	texts[ TYPE ]->setText( "Type" );
	texts[ SPECS ]->setText( "Specs" );
	texts[ COST ]->setText( "Cost/Status" );
	texts[ WALLET ]->setText( "Wallet: " );
	texts[ MONEY ]->setText( " " );
	
	// Set heads.
	for( int i = 0; i < 4; i++ )
	{
		heads.push_back( new Head() );
		heads[ i ]->load( i, 100*i +y );
	}
	
	// Set view.
	setView( w, h, 0, 0 );
	
	// Reload.
	reloadText();
}

void Headdeck::draw( sf::RenderWindow* &window )
{
	for( auto &it :texts )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :heads )
	{
		it->draw( window );
	}
	
	window->draw( line.get() );
}

void Headdeck::handle( sf::Event &event, int r_x, int r_y )
{
	for( auto &it :heads )
	{
		if( it->getCost() <= wallet && !it->sellOut() )
		{
			it->unlock();
		}
		else
		{
			it->lock();
		}
	}
	
	for( auto &it :heads )
	{
		it->handle( event, r_x, r_y );
		if( it->sellOut() )
		{
			wallet -= it->getCost();
			texts[ MONEY ]->setText( con::itos( wallet ) );
			texts[ MONEY ]->reloadPosition();
			it->makeNought();
			change = true;
			
			// save file
			MyFile file;
			file.load( "data/txt/money/bank.txt", std::ios::out );
			if( file.is_good() )
			{
				file.get() << con::itos( wallet ) << "\n";
			}
			file.free();
		}
	}
}



void Headdeck::fadein( int i, int max )
{
	line.fadein( i, max );
	
	for( auto &it :texts )
	{
		it->fadein( i, max );
	}
	
	for( auto &it :heads )
	{
		it->fadein( i, max );
	}
}

void Headdeck::fadeout( int i, int min )
{
	line.fadeout( i, min );
	
	for( auto &it :texts )
	{
		it->fadeout( i, min );
	}
	
	for( auto &it :heads )
	{
		it->fadeout( i, min );
	}
}



void Headdeck::reloadText()
{
	MyFile file;
	file.load( "data/txt/money/bank.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		wallet = con::stoi( line );
	}
	file.free();

	texts[ MONEY ]->setText( con::itos( wallet ) );
	texts[ MONEY ]->reloadPosition();
	
	for( auto &it :heads )
	{
		it->reloadText();
	}
}

void Headdeck::setVolume( int volume )
{
	for( auto &it :heads )
	{
		it->setVolume( volume );
	}
}

void Headdeck::turn()
{
	for( auto &it :heads )
	{
		it->turn();
	}
}

void Headdeck::turnOn()
{
	for( auto &it :heads )
	{
		it->turnOn();
	}
}

void Headdeck::turnOff()
{
	for( auto &it :heads )
	{
		it->turnOff();
	}
}



bool Headdeck::isChange()
{
	if( change )
	{
		change = false;
		return true;
	}
	
	return false;
}

void Headdeck::setWallet( int money )
{
	wallet = money;
	texts[ MONEY ]->setText( con::itos( wallet ) );
	texts[ MONEY ]->reloadPosition();
}

int Headdeck::getWallet()
{
	return wallet;
}



void Headdeck::setScale( float s_x, float s_y )
{
	line.setBasicScale( s_x, s_y );
	line.setScale( 1, 1 );
	
	for( auto &it :texts )
	{
		it->setBasicScale( s_x, s_y );
		it->setScale( 1, 1 );
	}
	
	for( auto &it :heads )
	{
		it->setScale( s_x, s_y );
	}
}

void Headdeck::setView( int w, int h, int r_x, int r_y )
{
	line.setPosition( w /1.38 +r_x, y_state *line.getYScale() +r_y );

	texts[ TYPE ]->setPosition( static_cast <int> (w) /10 +r_x, (y_state -50)*texts[ TYPE ]->getYScale() +r_y );
	texts[ SPECS ]->setPosition( w /10 *4 +r_x, (y_state -50)*texts[ SPECS ]->getYScale() +r_y );
	texts[ COST ]->setPosition( w /1.315 +r_x, (y_state -50)*texts[ COST ]->getYScale() +r_y );
	texts[ WALLET ]->setPosition( 10 *texts[ WALLET ]->getXScale() +r_x, h -45*texts[ WALLET ]->getYScale() +r_y );
	texts[ MONEY ]->setPosition( 140 *texts[ MONEY ]->getXScale() +r_x, h -42 *texts[ MONEY ]->getYScale() +r_y );
	
	for( auto &it :heads )
	{
		it->setView( w, h, r_x, r_y );
	}
}