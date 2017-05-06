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



void Headdeck::load( unsigned screen_w, unsigned screen_h, float y )
{
	free();
	
	// Set line.
	line.setName( "headdeck-line" );
	line.create( 2, screen_h /1.9 );
	line.setPosition( screen_w /1.5, y -18 );
	
	// Set texts.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "headdeck-text nr" +con::itos( i ) );
		
		if( i == WALLET )		texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
		else if( i == MONEY )	texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 22, 0xFF, 0xD8, 0x00 );
		else					texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 31, 0xFF, 0xFF, 0xFF );
	}
	
	texts[ TYPE ]->setText( "Type" );
	texts[ SPECS ]->setText( "Specs" );
	texts[ COST ]->setText( "Cost/Status" );
	texts[ WALLET ]->setText( "Wallet: " );
	texts[ MONEY ]->setText( " " );
	
	// Positions.
	texts[ TYPE ]->setPosition( screen_w /10, y -50 );
	texts[ SPECS ]->setPosition( screen_w /10 *4, y -50 );
	texts[ COST ]->setPosition( screen_w /1.315, y -50 );
	texts[ WALLET ]->setPosition( 10, screen_h -35 );
	texts[ MONEY ]->setPosition( 110, screen_h -32 );
	
	// Set heads.
	for( int i = 0; i < 4; i++ )
	{
		heads.push_back( new Head() );
		heads[ i ]->load( i, screen_w, (screen_h /8)*i +y );
	}
	
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

void Headdeck::handle( sf::Event &event )
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
		it->handle( event );
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