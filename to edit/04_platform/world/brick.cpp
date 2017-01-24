#include "brick.h"
#include "rules.h"
#include <cstdlib>	// rand

Brick::Brick()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
	lastGrass = -1;
	fallenX = 0;
}

Brick::~Brick()
{
	free();
}

void Brick::free()
{
	for( unsigned i = 0; i < block.size(); i++ )
	{
		block[ i ]->free();
	}
	
	block.clear();
	blocks.clear();
	bg_blocks.clear();

	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;

	lastGrass = -1;
	fallenX = 0;
}



void Brick::load( int screen_w, int screen_h, int nr, int type )
{
	free();
	
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;

	for( int i = 0; i < 16; i++ )
	{
		block.push_back( new MySprite() );
		block[ i ]->setName( "brick-block[" +to_string( i ) +"]" );
		block[ i ]->loadByImage( "data/sprites/play/" +to_string( type ) +"/" +to_string( i ) +".png" );
	}
	
	
	// Set first block.
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 4;
	blocks[ blocks.size()-1 ]->x = 0;
	blocks[ blocks.size()-1 ]->y = screen_h -width;
}

void Brick::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr != -1 )
		{
			if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
			{
				block[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				window->draw( block[ blocks[ i ]->nr ]->get() );
			}
		}
	}
	
	// printf( "%d\n", left );
}



void Brick::fadein( int v, int max )
{
	for( unsigned i = 0; i < block.size(); i++ )
	{
		block[ i ]->fadein( v, max );
	}
}

void Brick::fadeout( int v, int min )
{
	for( unsigned i = 0; i < block.size(); i++ )
	{
		block[ i ]->fadeout( v, min );
	}
}




void Brick::addBlock( int chosen, int x_width, int floor )
{
	// add block.
	blocks.push_back( new Block() );
	
	// set chosen.
	blocks[ blocks.size()-1 ]->nr = chosen;
	
	// set x.
	blocks[ blocks.size()-1 ]->x = x_width;
	
	// set y.
	blocks[ blocks.size()-1 ]->y = floor;
}

bool Brick::randFloor( bool &top, sf::Uint8 floor, sf::Uint8 &new_floor )
{
	bool flag = false;
	sf::Uint8 max = 4;
	sf::Uint8 min = 1;
	
	// Draw lots for true / false to change floor.
	if( rand()%2 == 1 )	// 50%
	{
		// Getting new floor.
		for(;;)
		{
			new_floor = rand()%max + min;
			
			if( new_floor != floor )
			{
				if( new_floor >= floor-1 && new_floor <= floor+1 )
				{
					break;
				}
			}
		}
		
		if( floor < new_floor )	// means new floor is higher
		{
			flag = true;
			top = true;
		}
		else
		{
			flag = true;
			top = false;
		}
	}
	
	return flag;
}

void Brick::fill( int a, int n )	// fill pending n
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == a || blocks[ i ]->nr == n )
		{
			// we check if we have free place
			bool free_place = true;
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ i ]->y == blocks[ j ]->y && blocks[ i ]->x +width == blocks[ j ]->x  )
				{
					free_place = false;
				}
			}
			
			if( free_place &&  blocks[ i ]->x + width <= right )
			{
				addBlock( n, blocks[ i ]->x + width, blocks[ i ]->y );
			}
		}
	}
}

vector <Plank*> Brick::bot_islands( int w2, int h2, unsigned size )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Create planks
	vector < Plank* > planks;
	
	// Searcher
	for( unsigned i = 0; i < size; i++ )
	{
		// blocks with grass, apriopriate y
		if( blocks[ i ]->y < screen_h -width*2 )
		{
			if( blocks[ i ]->nr >= 5 && blocks[ i ]->nr <= 7 )
			{
				posX.push_back( blocks[ i ]->x );
				posY.push_back( blocks[ i ]->y );
				counters.push_back( 1 );
				
				for( unsigned j = i+1; j < size; j++ )
				{
					if( blocks[ j ]->y == blocks[ i ]->y ) // check y
					{
						if( (blocks[ j ]->nr >= 5 && blocks[ j ]->nr <= 7) || blocks[ j ]->nr == -1 )
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
	
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		printf( "%d %d %d\n", posX[ i ], posY[ i ], counters[ i ] );
	}

	
	// Rubbish
	bool rubbish = true;
	while( rubbish )
	{
		rubbish = false;
		for( unsigned i = 0; i < posX.size(); i++ )
		{
			if( counters[ i ] < 4 )
			{
				rubbish = true;
				posX.erase( posX.begin() +i );
				posY.erase( posY.begin() +i );
				counters.erase( counters.begin() +i );
			}
		}
	}
	
	
	// Creator// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		// x and y for ladder
		int myX, myY;
		
		// searching for free space
		bool success = false;
		
		// check left
		for( unsigned j = 0; j < size; j++ )
		{
			if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
			{
				if( blocks[ j ]->x == posX[ i ] -width )
				{
					success = true;
					myX = blocks[ j ]->x +width -w2 +10;
					printf( "1 %d %d %d\n", posX[ i ], posY[ i ], counters[ i ] );
					break;
				}
			}
		}
		
		// check right
		if( !success )
		{
			for( unsigned j = 0; j < size; j++ )
			{
				if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
				{
					if( blocks[ j ]->x == posX[ i ] + ( width *counters[ i ] ) )
					{
						success = true;
						myX = blocks[ j ]->x -10;
						printf( "2 %d %d %d\n", posX[ i ], posY[ i ], counters[ i ] );
						break;
					}
				}
			}
		}
		
		// other option
		if( !success )
		{
			for( unsigned k = 1; k < counters[ i ]; k++ )
			{
				for( unsigned j = 0; j < size; j++ )
				{
					if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
					{
						if( blocks[ j ]->x == posX[ i ] + ( width *k ) )
						{
							success = true;
							myX = blocks[ j ]->x -10;
							printf( "3 %d %d %d\n", posX[ i ], posY[ i ], counters[ i ] );
							k = counters[ i ] -1;
							break;
						}
					}
				}
			}
		}
		
		if( success )
		{
			planks.push_back( new Plank() );
			planks[ planks.size() -1 ]->x = myX;
			planks[ planks.size() -1 ]->y = posY[ i ] -h2 +width*2;
			planks[ planks.size() -1 ]->nr = 1;
			
			if( posY[ i ] == screen_h -width*4 ) // 0, 1, 2.
			{
				myY = screen_h -width;
				
				addBlock( 10, myX, myY );
				myX += width;
				
				for( int j = 0; j < counters[ i ]-2; j++ )
				{
					addBlock( 11, myX, myY );
					myX += width;
				}
				
				addBlock( 12, myX, myY );
				
				myY = screen_h -width*2;
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
			
			printf( "added %d %d\n", myX, myY );
		}
	}
	
	return planks;
}

vector <Plank*> Brick::top_islands( int w2, int h2 )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Create planks
	vector < Plank* > planks;
	
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
			planks.push_back( new Plank() );
			planks[ planks.size() -1 ]->x = myX -w2 +10;
			planks[ planks.size() -1 ]->y = posY[ i ] -h2;
			planks[ planks.size() -1 ]->nr = 1;
			
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
	
	return planks;
}

vector <Plank*> Brick::positioning( int size, int w1, int h1, int w2, int h2 )
{
	// Create rules.
	Rules* rules = new Rules;
	rules->ruleRightSide();
	
	// Create planks
	vector < Plank* > planks;
	
	// Random stuff
	sf::Uint8 scope;
	int8_t lastNr, chosen;
	
	
	
	// Floor stuff.
	sf::Uint8 floor = 1;
	sf::Uint8 new_floor = 1;
	
	// Floor flags
	bool top = false;
	bool flag = false;
	
	while( size-- )
	{
		// add block to the right
		lastNr = blocks[ blocks.size()-1 ]->nr;
		scope = rules->getRightRules( lastNr ).size();
		chosen = rules->getRightRules( lastNr )[ rand()%scope ];
		addBlock( chosen, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
		
		// RAND FLOOR
		top = false;
		flag = randFloor( top, floor, new_floor );
		
		// add top block
		if( flag )
		{
			if( top )
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
				}
				
				
				floor = new_floor;
				lastNr = blocks[ blocks.size()-1 ]->nr;
				addBlock( rules->getTopBlockFor( lastNr ), blocks[ blocks.size()-1 ]->x, screen_h -width*floor );
					
				
				// add ladder
				planks.push_back( new Plank() );
				planks[ planks.size() -1 ]->x = blocks[ blocks.size()-1 ]->x -w1 +10;
				planks[ planks.size() -1 ]->y = blocks[ blocks.size()-1 ]->y +width -h1;
			}
			else
			{
				int need;
				if( rand()%2 == 1 )	need = 2;
				else				need = 7;
				
				while( true )
				{
					lastNr = blocks[ blocks.size()-1 ]->nr;
					addBlock( rules->fillForBot( lastNr ), blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
					
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
				lastNr = blocks[ blocks.size()-1 ]->nr;
				scope = rules->getRightRules( lastNr ).size();
				chosen = rules->getRightRules( lastNr )[ rand()%scope ];
				addBlock( chosen, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				
				// add ladder
				planks.push_back( new Plank() );
				planks[ planks.size() -1 ]->x = blocks[ blocks.size()-1 ]->x -10;
				planks[ planks.size() -1 ]->y = blocks[ blocks.size()-1 ]->y -h1;
			}
		}
	}
	

	
	// fill left bottom
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 10 || blocks[ i ]->nr == 0 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ i ]->y +width == blocks[ j ]->y && blocks[ i ]->x == blocks[ j ]->x )
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
							for( unsigned k = 0; k < blocks.size(); k++ )
							{
								if( x == blocks[ k ]->x && blocks[ i ]->y +width == blocks[ k ]->y )
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
							for( unsigned k = 0; k < blocks.size(); k++ )
							{
								if( blocks[ k ]->x > further )
								{
									further = blocks[ k ]->x;
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
	
	// fill right bottom
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 12 || blocks[ i ]->nr == 2 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ i ]->y +width == blocks[ j ]->y && blocks[ i ]->x == blocks[ j ]->x )
				{
					free_place = false;
				}
			}
			
			if( free_place )
			{
				// we have to check what kind of block is on the left 'further'
				int type = -1;
				int distance = -1;
				
				for( unsigned j = 0; j < blocks.size(); j++ )
				{
					if( blocks[ j ]->y == blocks[ i ]->y +width && blocks[ i ]->x -blocks[ j ]->x > 0 )
					{
						if( blocks[ j ]->nr == 8 || blocks[ j ]->nr == 10 ||
							blocks[ j ]->nr == 0 || blocks[ j ]->nr == 14 )
						{
							if( distance >= blocks[ i ]->x - blocks[ j ]->x || distance == -1 )
							{
								distance = blocks[ i ]->x - blocks[ j ]->x;

								// we found block
								type = blocks[ j ]->nr;
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
	
	delete rules;
	
	// printf( "\n\n\n\n" );
	
	// Searching for left
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->x < left )
		{
			left = blocks[ i ]->x;
		}
	}
	
	// Searching right
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->x > right )
		{
			right = blocks[ i ]->x;
		}
	}
	
	
	fill( 10, 11 );
	fill( 14, 11 );
	fill( 8, 15 );
	
	unsigned s = blocks.size();
	
	vector <Plank*> additional = top_islands( w2, h2 );
	for( unsigned i = 0; i < additional.size(); i++ )
	{
		planks.push_back( new Plank() );
		planks[ planks.size() -1 ]->x = additional[ i ]->x;
		planks[ planks.size() -1 ]->y = additional[ i ]->y;
		planks[ planks.size() -1 ]->nr = additional[ i ]->nr;
	}
	
	additional = bot_islands( w2, h2, s );
	for( unsigned i = 0; i < additional.size(); i++ )
	{
		planks.push_back( new Plank() );
		planks[ planks.size() -1 ]->x = additional[ i ]->x;
		planks[ planks.size() -1 ]->y = additional[ i ]->y;
		planks[ planks.size() -1 ]->nr = additional[ i ]->nr;
	}
	
	return planks;
}


/*
bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					block[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
					if( block[ blocks[ i ]->nr ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}
*/

bool Brick::checkBlockByPixel( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 		// bot
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					block[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( block[ blocks[ i ]->nr ]->checkPixelCollision( j, t ) )		return true;
						else if( block[ blocks[ i ]->nr ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( block[ blocks[ i ]->nr ]->checkPixelCollision( l, j ) )		return true;
						else if( block[ blocks[ i ]->nr ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}




sf::Uint8 Brick::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		if( left > -10 )
		{
			return 1;
		}
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x += vel;
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
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x -= vel;
		}
		
		left -= vel;
		right -= vel;
	}
	
	return 0;
}

sf::Uint8 Brick::getWidth()
{
	return width;
}

vector < Block* > Brick::getBlocks()
{
	return blocks;
}





void Brick::findLastGrass( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr >= 0 && blocks[ i ]->nr <= 7 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					block[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
					if( block[ blocks[ i ]->nr ]->checkCollision( rect->getX(), rect->getY() +5, rect->getWidth(), rect->getHeight() ) )
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

int Brick::getLastGrassY()
{
	return blocks[ lastGrass ]->y;
}

int Brick::getLastGrassX()
{
	return blocks[ lastGrass ]->x;
}

void Brick::setNewX( int heroX )
{
	//printf("lll %d\n", lastGrass );
	fallenX = blocks[ lastGrass ]->x;
	
	int value = heroX -blocks[ lastGrass ]->x;
	
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

int Brick::backToGrass()
{
	int add = 0;
	
	if( fallenX != 0 )
	{
		if( fallenX > blocks[ lastGrass ]->x )
		{
			add = 1;
			
			for( unsigned i = 0; i < blocks.size(); i++ )
			{
				blocks[ i ]->x += add;
			}
			
			left += add;
			right += add;
			
			if( fallenX < blocks[ lastGrass ]->x )
			{
				fallenX = 0;
			}
		}
		else if( fallenX < blocks[ lastGrass ]->x )
		{
			add = -1;
			
			for( unsigned i = 0; i < blocks.size(); i++ )
			{
				blocks[ i ]->x += add;
			}
			
			left += add;
			right += add;
			
			if( fallenX > blocks[ lastGrass ]->x )
			{
				fallenX = 0;
			}
		}
		else
		{
			fallenX = 0;
		}
	}
	
	return add;
}