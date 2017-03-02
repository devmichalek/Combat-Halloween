#include "04_platform/enemy/coins/coins.h"
#include <fstream>

Coins::Coins()
{
	width = 0;
	screen_w = 0;
	money = 0;
}

Coins::~Coins()
{
	free();
}

void Coins::free()
{
	width = 0;
	screen_w = 0;
	money = 0;
	
	coin.free();
	
	if( !coins.empty() )
	{
		for( auto &i :coins )
		{
			i->free();
		}
		
		coins.clear();
	}
	if( !dropped_coins.empty() )
	{
		for( auto &i :dropped_coins )
		{
			i->free();
		}
		
		dropped_coins.clear();
	}
	if( !jumped_coins.empty() )
	{
		for( auto &i :jumped_coins )
		{
			i->free();
		}
		
		jumped_coins.clear();
	}
}

void Coins::reset()
{
	for( auto &it :coins )
	{
		it->reset();
	}
}



void Coins::load( int width, int screen_w, int type )
{
	this->width = width;
	this->screen_w = screen_w;
	
	fstream file;
	
	file.open( "data/txt/money/cash.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong with data/txt/money/cash.txt\n" );
	}
	else
	{
		string line;
		while( true )
		{
			file >> line;
			
			if( type == 0 )
			{
				money = strToInt( line );
				// printf( "%d\n", money );
				break;
			}
			
			type --;
		}
	}
	file.close();
	
	file.open( "data/txt/money/settings.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong with data/txt/money/settings.txt\n" );
	}
	else
	{
		string line;
		int dropped = 0;
		int jumped = 0;
		
		file >> line;
		dropped = strToInt( line );
		
		file >> line;
		jumped = strToInt( line );
		
		for( int i = 0; i < dropped; i ++ )
		{
			dropped_coins.push_back( new Slab() );
			dropped_coins[ dropped_coins.size() -1 ]->setName( "coins-dropped_coins" );
			dropped_coins[ dropped_coins.size() -1 ]->load( "data/04_platform/panel/coin/sounds/dropped/" +to_string( i ) +".wav" );
		}
		
		for( int i = 0; i < jumped; i ++ )
		{
			jumped_coins.push_back( new Slab() );
			jumped_coins[ jumped_coins.size() -1 ]->setName( "coins-jumped_coins" );
			jumped_coins[ jumped_coins.size() -1 ]->load( "data/04_platform/panel/coin/sounds/jumped/" +to_string( i ) +".wav" );
		}
	}
	file.close();
	
	
	int coin_line = 10;
	coin.setName( "factory-coin" );
	coin.load( "data/04_platform/panel/coin/0.png", coin_line );
	coin.setScale( 0.4, 0.4 );
	
	// max amount of coins is 100
	for( unsigned i = 0; i < 100; i++ )
	{
		coins.push_back( new Coin() );
		coins[ coins.size() -1 ]->setVelocity( static_cast <float> (rand()%4 +5) /10 );
		coins[ coins.size() -1 ]->setLine( coin_line );
		coins[ coins.size() -1 ]->setDelay( 10 );
	}
}

void Coins::setChance( int chance )
{
	money += money *static_cast <float> (chance) /100;
}

void Coins::draw( sf::RenderWindow* &window )
{
	for( auto &i :coins )
	{
		if( i->isActive() )
		{
			if( i->getX() > -width && i->getX() < screen_w + width )
			{
				coin.setOffset( i->getOffset() );
				coin.setPosition( i->getX(), i->getY() );
				window->draw( coin.get() );
			}
			else
			{
				i->reset();
			}
		}
	}
}

void Coins::fadein( int v, int max )
{
	coin.fadein( v, max );
}

void Coins::fadeout( int v, int min )
{
	coin.fadeout( v, min );
}

void Coins::setCoin( Rect* rect )
{
	if( rect != NULL )
	{
		int x = rect->getX();
		int y = rect->getY();
		int l = rect->getWidth();
		int r = rect->getHeight();
		
		int money_amount = rand()%4 +2;
		for( auto &it :coins )
		{
			if( money_amount > 0 )
			{
				if( !it->isActive() )
				{
					money_amount --;
					
					it->setAsActive();
					it->setJump( rand()% (width /5) +width/2 );
					it->setBorders( l, r -coin.getWidth() );
					it->setPosition( x, y -coin.getHeight() );
					it->setDirection( rand()%2 +1 );
				}
			}
			else
			{
				break;
			}
		}
		
		// play dropped_coin.wav.
		if( dropped_coins.size() > 0 )
		{
			if( dropped_coins[ 0 ]->isPlayable() )
			{
				dropped_coins[ rand()%dropped_coins.size() ]->play();
			}
		}
	}
}



void Coins::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :coins )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :coins )
		{
			it->moveX( -vel );
		}
	}
}

void Coins::undoFall( sf::Uint8 add )
{
	for( auto &it :coins )
	{
		it->moveX( add );
	}
}

void Coins::mechanics()
{
	for( auto &i :coins )
	{
		if( i->isActive() )
		{
			if( i->mechanics() )
			{
				// play jumped_coin.wav.
				if( jumped_coins.size() > 0 )
				{
					if( jumped_coins[ 0 ]->isPlayable() )
					{
						// printf( "happen\n" );
						jumped_coins[ rand()%jumped_coins.size() ]->play();
					}
				}
			}
		}
	}
}

void Coins::setColor( sf::Color color )
{
	coin.setColor( color );
}



int Coins::strToInt( string s )
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

int Coins::getMoney()
{
	float multiplier = rand()%10;
	return money +(money *multiplier);
}

bool Coins::upliftMoney( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :coins )
		{
			if( it->isActive() )
			{
				coin.setPosition( it->getX(), it->getY() );
				if( coin.checkRectCollision( *rect ) )
				{
					it->reset();
					
					if( dropped_coins.size() > 0 )
					{
						if( dropped_coins[ 0 ]->isPlayable() )
						{
							dropped_coins[ rand()%dropped_coins.size() ]->play();
						}
					}
					return true;
				}
			}
		}
	}
	
	return false;
}