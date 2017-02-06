#include "brick.h"
#include "rules.h"
#include <cstdlib>
#include <fstream>

void Brick::reserve( unsigned size )
{
	// Reserve.
	blocks.reserve( size*(3.85) );
	this->size = blocks.capacity();
	// cout << "size (start): " << this->size << endl;
}

void Brick::shrink()
{
	// Shrink.
	blocks.shrink_to_fit();
	this->size = blocks.capacity();
	// cout << "size (end): " << this->size << endl;
}



Brick::Brick()
{
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
	fallenX = 0;
	grass_value = 0;
	water_line = 0;
	islands_line = 0;
}

Brick::~Brick()
{
	free();
}

void Brick::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
	if( !planks.empty() )
	{
		for( auto &it :planks )
		{
			it->free();
		}
		
		planks.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	if( !blocks.empty() )
	{
		for( auto &it :blocks )
		{
			it->free();
		}
		
		blocks.clear();
	}
	
	if( !moving_blocks.empty() )
	{
		for( auto &it :moving_blocks )
		{
			it->free();
		}
		
		moving_blocks.clear();
	}
	
	fallenX = 0;
	grass_value = 0;
	water_line = 0;
	islands_line = 0;
}

int Brick::reset()
{
	int distance = 0;
	
	while( true )
	{
		if( left < -10 )
		{
			for( auto &it :blocks )
			{
				it->x ++;
			}
			
			for( auto &it :moving_blocks )
			{
				it->moveX( 1 );
			}
			
			left ++;
			right ++;
			distance ++;
		}
		else
		{
			break;
		}
	}
	
	return distance;
}



void Brick::load( int screen_w, int screen_h, int type )
{
	free();
	
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load data with amount of blocks.
	fstream file;
	file.open( "data/txt/brick/" +to_string( type ) +".map" );
	if( file.bad() )
	{
		printf( "Cannot open %s\n", ("data/txt/brick/" +to_string( type ) +".map").c_str() );
	}
	else
	{
		int nr;
		file >> nr;
		
		for( int i = 0; i < nr; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ i ]->setName( "brick-block[" +to_string( i ) +"]" );
			sprites[ i ]->load( "data/sprites/play/" +to_string( type ) +"/" +to_string( i ) +".png" );
		}
	}
}

void Brick::draw( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		if( it->nr != -1 )
		{
			if( it->x > -width && it->x < screen_w )
			{
				sprites[ it->nr ]->setPosition( it->x, it->y );
				window->draw( sprites[ it->nr ]->get() );
			}
		}
	}
	
	for( auto &it :moving_blocks )
	{
		it->moving();
		
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX(i) > -width && it->getX(i) < screen_w )
			{
				sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
				window->draw( sprites[ it->getNr(i) ]->get() );
			}
		}
	}
}



void Brick::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Brick::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



int Brick::to_int( string s )
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

void Brick::addPlank( int n, int x, int y )
{
	planks.push_back( new Plank() ); 	// add block.
	planks[ planks.size()-1 ]->nr = n; 	// set chosen.
	planks[ planks.size()-1 ]->x = x; 	// set x.
	planks[ planks.size()-1 ]->y = y; 	// set y.
}

void Brick::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

sf::Uint8 Brick::getNewFloor( sf::Uint8 floor, int chance )
{
	sf::Uint8 min = 1;
	sf::Uint8 max = 4;
	
	// Draw lots for true / false to change floor.
	if( rand()%100 > chance )	// 50% is base
	{
		if( floor == min )
		{
			return min +1;
		}
		else if( floor == max )
		{
			return max -1;
		}
		else
		{
			return rand()%(max-2) + (min+1);
		}
	}
	
	return floor;
}




void Brick::createTopBorders( int size, int chance, int w, int h )
{
	// Set first block.
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 4;
	blocks[ blocks.size()-1 ]->x = 0;
	blocks[ blocks.size()-1 ]->y = screen_h -width;
	
	// Create rules.
	Rules* rules = new Rules;
	rules->rule();
	
	sf::Uint8 floor = 1;
	size --;
	while( size-- )
	{
		// add block to the right
		int8_t lastNr = blocks[ blocks.size()-1 ]->nr;
		if( lastNr == -1 )
		{
			if( rand()%2 == 1 )
			{
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
			}
			else
			{
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
			}
		}
		addBlock( rules->getBlock( lastNr ) , blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
		
		sf::Uint8 new_floor = getNewFloor( floor, chance );
		if( new_floor > floor )
		{
			int need;
			if( rand()%2 == 1 )	need = -1;
			else				need = 14;
				
			while( true )
			{
				lastNr = blocks[ blocks.size()-1 ]->nr;
				if( lastNr == need )
				{
					break;
				}
				
				lastNr = blocks[ blocks.size()-1 ]->nr;
				addBlock( rules->fillForTop( lastNr, need ), blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				if( size > 0 )	size --;
			}
			
			
			floor = new_floor;
			lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getTopBlockFor( lastNr ), blocks[ blocks.size()-1 ]->x, screen_h -width*floor );
				
			
			// add ladder
			addPlank( 0, blocks[ blocks.size()-1 ]->x -w +10, blocks[ blocks.size()-1 ]->y +width -h );
		}
		else if( new_floor < floor )
		{
			int need;
			if( rand()%2 == 1 )	need = 2;
			else				need = 7;
			
			while( true )
			{
				lastNr = blocks[ blocks.size()-1 ]->nr;
				addBlock( rules->fillForBot( lastNr ), blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				if( size > 0 )	size --;
				
				lastNr = blocks[ blocks.size()-1 ]->nr;
				if( lastNr == need )
				{
					break;
				}
			}
			
			floor = new_floor;
			lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getBotBlockFor( lastNr ), blocks[ blocks.size()-1 ]->x, screen_h -width*floor );
			
			// add block to the right
			int8_t lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getBlock( lastNr ) , blocks[ blocks.size()-1 ]->x +width, screen_h -width*floor );
			if( size > 0 )	size --;
			
			// add ladder
			addPlank( 0, blocks[ blocks.size()-1 ]->x -10, blocks[ blocks.size()-1 ]->y -h );
		}
	}
	
	delete rules;
}

void Brick::createMovingIslands()
{
	for( unsigned i = 0; i < blocks.size()-2; i++ )
	{
		if( blocks[ i ]->nr == 2 || blocks[ i ]->nr == 7 )
		{
			if( blocks[ i ]->y == blocks[ i +2 ]->y )
			{
				if( rand()%100 < 30 )
				{
					int distance = rand()%2 +4;
				
					int startX = blocks[ i ]->x +width;
					int endX = blocks[ i ]->x + (distance +2)*width;
					int y = blocks[ i ]->y;
					
					int vel = 0;
					
					if( rand()%6 < 2 )
					{
						vel = 2;
					}
					else
					{
						vel = 1;
					}
					int vel = rand()%2 +1;
					
					moving_blocks.push_back( new Moving_block() );
					moving_blocks[ moving_blocks.size()-1 ]->positioning();
					moving_blocks[ moving_blocks.size()-1 ]->setPosition( startX, endX, y, vel );
					
					int num = 0;
					for( unsigned j = 0; j < planks.size(); j++ )
					{
						if( planks[ j ]->x > blocks[ i +2 ]->x )
						{
							num = j;
							break;
						}
					}
					for( unsigned j = num; j < planks.size(); j++ )
					{
						planks[ j ]->x += distance*width;
					}
					
					for( unsigned j = i +1; j < blocks.size(); j++ )
					{
						blocks[ j ]->x += distance*width;
					}
				}
			}
		}
	}
}

void Brick::createLeftBorders()
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 10 || blocks[ i ]->nr == 0 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( blocks[ i ]->y +width == j->y && blocks[ i ]->x == j->x )
				{
					free_place = false;
				}
			}
			
			if( free_place )
			{
				if( blocks[ i ]->nr == 0 )
				{
					// we are looking for block nr 13
					
					bool put = false;
					int x = blocks[ i ]->x +width;
					
					for( unsigned j = i +1; j < blocks.size(); j++ )
					{
						bool success = false;
						
						while( !success )
						{
							for( auto &k :blocks )
							{
								if( x == k->x && blocks[ i ]->y +width == k->y )
								{
									success = true;
								}
							}
							
							if( !success )
							{
								// new x
								x += width;
							}
							
							int further = 0;
							for( auto &k :blocks)
							{
								if( k->x > further )
								{
									further = k->x;
								}
							}
							
							if( x > further )
							{
								break;
							}
						}
						
						if( x == blocks[ j ]->x && blocks[ i ]->y +width == blocks[ j ]->y )
						{
							if( blocks[ j ]->nr == 13 )
							{
								put = true;
								// printf( "%d %d\n", x, blocks[ i ]->y +width );
							}
							
							break;
						}
					}
					
					if( rand()%2 == 1 || put )
					{
						addBlock( 10, blocks[ i ]->x, blocks[ i ]->y +width );
					}
					else
					{
						addBlock( 8, blocks[ i ]->x, blocks[ i ]->y +width );
					}
				}
				else if( blocks[ i ]->nr == 10 )
				{
					addBlock( 10, blocks[ i ]->x, blocks[ i ]->y +width );
				}
			}
		}
	}
}

void Brick::createRightBorders()
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 12 || blocks[ i ]->nr == 2 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( blocks[ i ]->y +width == j->y && blocks[ i ]->x == j->x )
				{
					free_place = false;
				}
			}
			
			if( free_place )
			{
				// we have to check what kind of block is on the left 'further'
				int type = -1;
				int distance = -1;
				
				for( auto &j :blocks )
				{
					if( j->y == blocks[ i ]->y +width && blocks[ i ]->x -j->x > 0 )
					{
						if( j->nr == 8 || j->nr == 10 ||
							j->nr == 0 || j->nr == 14 )
						{
							if( distance >= blocks[ i ]->x - j->x || distance == -1 )
							{
								distance = blocks[ i ]->x - j->x;

								// we found block
								type = j->nr;
							}
						}
					}
				}
				
				// printf( "type = %d\n", type );
				
				if( type == 8 )			type = 9;
				else 					type = 12;
				
				addBlock( type, blocks[ i ]->x, blocks[ i ]->y +width );
			}
		}
	}
}

void Brick::createStuffing( int a, int n )
{
	for( vector <Block*>::iterator i = blocks.begin(); i != blocks.end(); i++ )
	{
		if( (*i)->nr == a || (*i)->nr == n )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( (*i)->y == j->y && (*i)->x +width == j->x  )
				{
					free_place = false;
					break;
				}
			}
			
			if( free_place &&  (*i)->x + width <= right )
			{
				addBlock( n, (*i)->x + width, (*i)->y );
			}
		}
	}
}

void Brick::createBotIslands( int w, int h )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Searcher
	for( auto i = blocks.begin(); i != blocks.end(); i++ )
	{
		// blocks with grass, apriopriate y
		if( (*i)->y < screen_h -width*2 )
		{
			if( (*i)->nr >= 5 && (*i)->nr <= 7 )
			{
				posX.push_back( (*i)->x );
				posY.push_back( (*i)->y );
				counters.push_back( 1 );
				
				for( auto j = i +1; j != blocks.end(); j++ )
				{
					if( (*j)->y == (*i)->y ) // check y
					{
						if( ((*j)->nr >= 5 && (*j)->nr <= 7) || (*j)->nr == -1 )
						{
							counters[ counters.size()-1 ] ++;
						}
						else
						{
							i = j +1;
							break;
						}
					}
					else
					{
						i = j +1;
						break;
					}
				}
			}
			
		}
	}

	
	// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		// x and y for ladder
		int myX, myY;
		
		// searching for free space
		sf::Uint8 success = 0;
		
		// check left
		for( unsigned j = 0; j < islands_line; j++ )
		{
			if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
			{
				if( blocks[ j ]->x == posX[ i ] -width )
				{
					success = 1;
					myX = blocks[ j ]->x +width -w +10;
					break;
				}
			}
		}
		
		int surplus = 0;
		// check right
		if( success == 0 )
		{
			for( unsigned j = 0; j < islands_line -1; j++ )
			{
				if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 && blocks[j -1]->nr != -1 )
				{
					if( blocks[ j ]->x == posX[ i ] + width *(counters[ i ]-1)
					&& blocks[ j ]->x != blocks[ j +1 ]->x )	// check if we can climb (change of floor)
					{
						success = 2;
						myX = blocks[ j ]->x -10;
						surplus = 0 *width;
						// printf( "2 %d\n", myX );
						break;
					}
				}
			}
		}
		
		if( success != 0 )
		{
			// add ladder
			addPlank( 1, myX, posY[ i ] -h +width*2 );
			
			if( success == 2 )
			{
				myX -= width*(counters[ i ] -1) -w -surplus;
				counters[ i ] -= 1;
			}
			
			if( posY[ i ] == screen_h -width*4 ) // 0, 1, 2.
			{
				myY = screen_h -width;
				int saveX = myX;
				
				addBlock( 10, myX, myY );
				myX += width;
				
				for( int j = 0; j < counters[ i ]-2; j++ )
				{
					addBlock( 11, myX, myY );
					myX += width;
				}
				
				addBlock( 12, myX, myY );
				
				myY = screen_h -width*2;
				myX = saveX;
			}
			else
			{
				myY = screen_h -width;
			}
			
			addBlock( 0, myX, myY );
			myX += width;
			
			for( int j = 0; j < counters[ i ]-2; j++ )
			{
				addBlock( 1, myX, myY );
				myX += width;
			}
			
			addBlock( 2, myX, myY );
		}
	}
}

void Brick::createTopIslands( int w, int h )
{
	islands_line = blocks.size();
	
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Searcher
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		// blocks with grass, apriopriate y
		if( blocks[ i ]->y >= screen_h -width*2 &&
		  ( blocks[ i ]->nr == 0 ||
			blocks[ i ]->nr == 4 ||
			blocks[ i ]->nr == 5 ) )
		{
			posX.push_back( blocks[ i ]->x );
			posY.push_back( blocks[ i ]->y );
			counters.push_back( 1 );
			
			for( unsigned j = i+1; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->y == blocks[ i ]->y )
				{
					if( blocks[ j ]->nr == 2 || blocks[ j ]->nr == 3 || blocks[ j ]->nr == 7 )
					{
						counters[ counters.size()-1 ] ++;
						i = j +1;
						break;
					}
					
					if( blocks[ j ]->nr == 1 || blocks[ j ]->nr == 6 )
					{
						counters[ counters.size()-1 ] ++;
					}
				}
			}
		}
	}
	
	// Merger
	bool merger = true;
	while( merger )
	{
		merger = false;
		for( unsigned i = 0; i < posX.size() -1; i++ )
		{
			if( posY[ i ] == posY[ i +1 ] )
			{
				if( posX[ i ] +(width *(counters[ i ] +1) ) == posX[ i +1 ] )
				{
					merger = true;
					counters[ i ] += counters[ i +1 ] +1;
					posX.erase( posX.begin() +i +1 );
					posY.erase( posY.begin() +i +1 );
					counters.erase( counters.begin() +i +1 );
				}
			}
		}
	}
	
	// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		if( counters[ i ] >= 4 )
		{
			int myX = posX[ i ] +width;
			int myY = posY[ i ] -(width*2);
			
			// add ladder
			addPlank( 1, myX -w +10, posY[ i ] -h );
			
			while( counters[ i ] >= 4 )
			{
				int result = 0;
				while( result < 2 )
				{
					result = rand()%(counters[ i ]/2) +1;
				}
				
				//---------------------------
				// 5
				addBlock( 5, myX, myY );
				result -= 1;
				myX += width;
				
				// 6
				for( int j = 0; j < result-1; j++ )
				{
					addBlock( 6, myX, myY );
					myX += width;
				}
				
				// 7
				addBlock( 7, myX, myY );
				myX += width*2;
				//---------------------------
				
				counters[ i ] -= ( result +3 );
			}
		}
	}
	
}

void Brick::createWater()
{
	vector <Block*> water_blocks;
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 2 ) // right border
		{
			bool success = false;
			
			// what kind of block is at the bottom
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->x == blocks[ i ]->x )
				{
					if( blocks[ j ]->y == screen_h -width )
					{
						if( blocks[ j ]->nr == 12 )
						{
							// printf( "%d\n", blocks[ i ]->x );
							success = true;
						}
					}
				}
			}
			
			if( success )
			{
				int myX = blocks[ i ]->x +width;
				int good_nr = -1;
				
				// what kind of block is on the right
				for( unsigned j = i+1; j < blocks.size(); j++ )
				{
					if( blocks[ j ]->nr < 8 ) // grass blocks
					{
						if( blocks[ j ]->x == myX )
						{
							if( blocks[ j ]->y == blocks[ i ]->y )
							{
								myX += width;
								
								if( blocks[ j ]->nr == 0 )
								{
									good_nr = j;
									// printf( "%d\n", blocks[ j ]->x );
								}
							}
							else
							{
								break;
							}
						}
					}
				}
				
				if( good_nr != -1 )
				{
					bool ready = false;
					
					// what kind of block is at the bottom again
					for( unsigned j = 0; j < blocks.size(); j++ )
					{
						if( blocks[ j ]->x == blocks[ good_nr ]->x )
						{
							if( blocks[ j ]->y == screen_h -width )
							{
								if( blocks[ j ]->nr == 10 )
								{
									ready = true;
								}
							}
						}
					}
					
					if( ready )
					{
						// check that there is no bottom islands
						for( unsigned j = 0; j < blocks.size(); j++ )
						{
							if( blocks[ j ]->y > blocks[ i ]->y )
							{
								if( blocks[ j ]->x > blocks[ i ]->x && blocks[ j ]->x < blocks[ good_nr ]->x )
								{
									if( blocks[ j ]->nr >= 0 && blocks[ j ]->nr <= 7 )
									{
										ready = false;
										break;
									}
								}
							}
						}
							
					}
					
					if( ready )
					{
						// printf( "im ready  %d %d\n",  blocks[ i ]->x, blocks[ good_nr ]->x );
						
						// 16
						for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
						{
							// add block.
							water_blocks.push_back( new Block() );
							water_blocks[ water_blocks.size()-1 ]->nr = 16;
							water_blocks[ water_blocks.size()-1 ]->x = j;
							water_blocks[ water_blocks.size()-1 ]->y = blocks[ i ]->y;
						}
						
						// 17
						for( int k = blocks[ i ]->y +width; k <= screen_h -width; k += width )
						{
							for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
							{
								// add block.
								water_blocks.push_back( new Block() );
								water_blocks[ water_blocks.size()-1 ]->nr = 17;
								water_blocks[ water_blocks.size()-1 ]->x = j;
								water_blocks[ water_blocks.size()-1 ]->y = k;
							}
						}
					}
				}
			}
		}
		
		if( blocks[ i ]->y == screen_h -width )
		{
			if( blocks[ i ]->nr == 2 || blocks[ i ]->nr == 12 )
			{
				int good_nr = -1;
				
				if( blocks[ i ]->x %width == 0 )
				{
					for( int k = blocks[ i ]->x +width; k < right; k += width )
					{
						// check block on the right
						for( unsigned j = 0; j < blocks.size(); j++ )
						{
							if( blocks[ j ]->x == k && blocks[ j ]->y == blocks[ i ]->y )
							{
								if( blocks[ j ]->nr == 10 || blocks[ j ]->nr == 0 )
								{
									good_nr = j;
									k = right;
									break;
								}
							}
						}
					}
				}
				

				if( good_nr != -1 )
				{
					// 16
					for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
					{
						// add block.
						water_blocks.push_back( new Block() );
						water_blocks[ water_blocks.size()-1 ]->nr = 16;
						water_blocks[ water_blocks.size()-1 ]->x = j;
						water_blocks[ water_blocks.size()-1 ]->y = blocks[ i ]->y;
					}
				}
			}
		}
	}
	
	water_line = water_blocks.size();	// for pixel collision
	
	auto it = blocks.begin();
	for( unsigned i = 0; i < water_line; i++ )
	{
		it = blocks.insert( it, water_blocks[ i ] );
	}
}

void Brick::setLeft()
{
	// Searching for left
	for( auto &i :blocks )
	{
		if( i->x < left )
		{
			left = i->x;
		}
	}
}

void Brick::setRight()
{
	// Searching right
	for( auto &i :blocks )
	{
		if( i->x > right )
		{
			right = i->x;
		}
	}
}




sf::Uint8 Brick::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		if( left > -10 )
		{
			return 1;
		}
		
		for( auto &i :blocks )
		{
			i->x += vel;
		}
		
		for( auto &i :moving_blocks )
		{
			i->moveX( vel );
		}
		
		left += vel;
		right += vel;
	}
	else if( direction == 2 )
	{
		if( right < screen_w -width +10 )
		{
			return 2;
		}
		
		for( auto &i :blocks )
		{
			i->x -= vel;
		}
		
		for( auto &i :moving_blocks )
		{
			i->moveX( -vel );
		}
		
		left -= vel;
		right -= vel;
	}
	
	return 0;
}

void Brick::findLastGrass( Rect* rect )
{
	if( rect != NULL )
	{
		for( vector <Block*>::iterator i = blocks.begin(); i != blocks.end(); i++ )
		{
			if( (*i)->nr >= 0 && (*i)->nr <= 7 )
			{
				if( (*i)->x > -width && (*i)->x < screen_w )
				{
					sprites[ (*i)->nr ]->setPosition( (*i)->x, (*i)->y );
					if( sprites[ (*i)->nr ]->checkCollision( rect->getX(), rect->getY() +5, rect->getWidth(), rect->getHeight() ) )
					{
						lastGrass = i;
						//printf("%d\n", lastGrass );
						break;
					}
				}
			}
		}
	}
}

void Brick::setNewX( int heroX )
{
	//printf("lll %d\n", lastGrass );
	fallenX = (*lastGrass)->x;
	
	int value = heroX -(*lastGrass)->x;
	
	if( value < 0 )
	{
		value = -value;
	}
		
	if( heroX < fallenX )
	{
		fallenX -= value;
	}
	else
	{
		fallenX += value;
	}
}

bool Brick::backToGrass()
{
	grass_value = 0;
	if( fallenX != 0 )
	{
		if( fallenX > (*lastGrass)->x )
		{
			grass_value = 1;
			
			for( auto &i :blocks )
			{
				i->x += grass_value;
			}
			
			for( auto &i :moving_blocks )
			{
				i->moveX( grass_value );
			}
			
			left += grass_value;
			right += grass_value;
			
			if( fallenX < (*lastGrass)->x )
			{
				fallenX = 0;
			}
		}
		else if( fallenX < (*lastGrass)->x )
		{
			grass_value = -1;
			
			for( auto &i :blocks )
			{
				i->x += grass_value;
			}
			
			for( auto &i :moving_blocks )
			{
				i->moveX( grass_value );
			}
			
			left += grass_value;
			right += grass_value;
			
			if( fallenX > (*lastGrass)->x )
			{
				fallenX = 0;
			}
		}
		else
		{
			fallenX = 0;
		}
	}
	
	if( grass_value == 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}





int Brick::getLastGrassX()
{
	return (*lastGrass)->x;
}

int Brick::getLastGrassY()
{
	return (*lastGrass)->y;
}

int Brick::getGrassValue()
{
	return grass_value;
}

sf::Uint8 Brick::getWidth()
{
	return width;
}

vector <Block*> Brick::getBlocks()
{
	return blocks;
}

vector <Plank*> Brick::getPlanks()
{
	return planks;
}

int Brick::getLeft()
{
	return left;
}

int Brick::getRight()
{
	return right;
}




bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :blocks )
		{
			if( i->nr != -1 )
			{
				if( i->x > -width && i->x < screen_w )
				{
					sprites[ i->nr ]->setPosition( i->x, i->y );
					if( sprites[ i->nr ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
		
		for( auto &it :moving_blocks )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width && it->getX(i) < screen_w )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					if( sprites[ it->getNr(i) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Brick::checkPixelCollision( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
		for( unsigned i = water_line; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					sprites[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
		
		for( auto &it :moving_blocks )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width && it->getX(i) < screen_w )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Brick::isInTheWater( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < water_line; i++ )
		{
			if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
			{
				sprites[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				if( sprites[ blocks[ i ]->nr ]->checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight() ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}