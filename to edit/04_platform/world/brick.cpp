#include "brick.h"
#include "rules.h"
#include <cstdlib>	// rand

Special_ladder::Special_ladder()
{
	x = y = 0;
	used = false;
}

Special_ladder::~Special_ladder()
{
	x = y = 0;
	used = false;
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

void Brick::addLadder( int x, int y )
{
	// add ladder.
	ladders.push_back( new Ladder() );
	
	// set x.
	ladders[ ladders.size()-1 ]->x = x;
	
	// set y.
	ladders[ ladders.size()-1 ]->y = y;
	
	// setColor
	if( world_type == 0 )
	{
		ladders[ ladders.size()-1 ]->red = 0;
		ladders[ ladders.size()-1 ]->green = 0xFF;
		ladders[ ladders.size()-1 ]->blue = rand()%0xAA;
	}
	else if( world_type == 1 )
	{
		ladders[ ladders.size()-1 ]->red = 0xFF;
		ladders[ ladders.size()-1 ]->green = 0x9C;
		ladders[ ladders.size()-1 ]->blue = rand()%0x50;
	}
	else if( world_type == 2 )
	{
		ladders[ ladders.size()-1 ]->red = 0;
		ladders[ ladders.size()-1 ]->green = 0xFF;
		ladders[ ladders.size()-1 ]->blue = rand()%(0xFF -0xAA) + 0xAA;
	}
	else if( world_type == 3 )
	{
		ladders[ ladders.size()-1 ]->red = 0xFF;
		ladders[ ladders.size()-1 ]->green = 0xFF;
		ladders[ ladders.size()-1 ]->blue = rand()%0xAA;
	}
	
	if( rand()%1000 +1 > 985 && !red.used ) // 1.5% - red ladder
	{
		ladders[ ladders.size()-1 ]->red = 0xFF;
		ladders[ ladders.size()-1 ]->green = 0;
		ladders[ ladders.size()-1 ]->blue = 0;
		
		red.used = true;
		red.x = ladders[ ladders.size()-1 ]->x;
		red.y = ladders[ ladders.size()-1 ]->y;
		// printf( "R %d    %d %d\n", world_type, red.x, red.y );
	}
	
	if( rand()%1000 +1 > 990 && !white.used ) // 1% - white ladder
	{
		ladders[ ladders.size()-1 ]->red = 0xFF;
		ladders[ ladders.size()-1 ]->green = 0xFF;
		ladders[ ladders.size()-1 ]->blue = 0xFF;
		
		white.used = true;
		white.x = ladders[ ladders.size()-1 ]->x;
		white.y = ladders[ ladders.size()-1 ]->y;
		// printf( "W %d    %d %d\n", world_type, white.x, white.y );
	}
	
	if( rand()%1000 +1 > 998 && !black.used ) // 0.2% - black ladder
	{
		ladders[ ladders.size()-1 ]->red = 0;
		ladders[ ladders.size()-1 ]->green = 0;
		ladders[ ladders.size()-1 ]->blue = 0;
		
		black.used = true;
		black.x = ladders[ ladders.size()-1 ]->x;
		black.y = ladders[ ladders.size()-1 ]->y;
		// printf( "B %d    %d %d\n", world_type, black.x, black.y );
	}
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
					// printf( "old %d, new %d\n", floor, new_floor );
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

void Brick::islands()
{
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
			// printf( "X: %d  Y: %d  nr: %d\n", blocks[ i ]->x, blocks[ i ]->y, blocks[ i ]->nr );
			
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
		// printf( "X: %d  Y: %d  C: %d\n", posX[ i ], posY[ i ], counters[ i ] );
		if( counters[ i ] >= 4 )
		{
			int myX = posX[ i ] +width;
			int myY = posY[ i ] -(width*2);
			
			addLadder( myX -ladder[ 1 ].getWidth() +10, posY[ i ] -ladder[ 1 ].getHeight() );
			ladders[ ladders.size()-1 ]->nr = 1;
			
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

void Brick::positioning( int size )
{
	// Create rules.
	Rules* rules = new Rules;
	rules->ruleRightSide();
	
	
	
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
		chosen = rules->getRightRules( lastNr )[ rand()%scope ]->nr;
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
				int ladder_x = blocks[ blocks.size()-1 ]->x -ladder[ 0 ].getWidth() +10;
				int ladder_y = blocks[ blocks.size()-1 ]->y +width -ladder[ 0 ].getHeight();
				addLadder( ladder_x, ladder_y );
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
				chosen = rules->getRightRules( lastNr )[ rand()%scope ]->nr;
				addBlock( chosen, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				
				// add ladder
				int ladder_x = blocks[ blocks.size()-1 ]->x -10;
				int ladder_y = blocks[ blocks.size()-1 ]->y -ladder[ 0 ].getHeight();
				addLadder( ladder_x, ladder_y );
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
						if( x == blocks[ j ]->x && blocks[ i ]->y +width == blocks[ j ]->y )
						{
							// new x
							x += width;

							if( blocks[ j ]->nr == 13 )
							{
								put = true;
								// printf( "%d %d\n", x, blocks[ i ]->y +width );
								break;
							}
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
	
	
	// Delete rules
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
	
	islands();
	
	// printf( "type %d, %d\n", world_type, (right -left)/128 );
}





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
					block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
					if( block[ blocks[ i ]->nr ].checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

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
					block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( block[ blocks[ i ]->nr ].checkPixelCollision( j, t ) )		return true;
						else if( block[ blocks[ i ]->nr ].checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( block[ blocks[ i ]->nr ].checkPixelCollision( l, j ) )		return true;
						else if( block[ blocks[ i ]->nr ].checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Brick::checkLadder( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			if( ladders[ i ]->x > -width && ladders[ i ]->x < screen_w )
			{
				ladder[ ladders[ i ]->nr ].setPosition( ladders[ i ]->x, ladders[ i ]->y );
				if( ladder[ ladders[ i ]->nr ].checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
				{
					return true;
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
		
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x += vel;
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
		
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x -= vel;
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
					block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
					if( block[ blocks[ i ]->nr ].checkCollision( rect->getX(), rect->getY() +5, rect->getWidth(), rect->getHeight() ) )
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
	int t = heroX -blocks[ lastGrass ]->x;
	if( t < 0 )	t = -t;
	
	if( heroX < fallenX )
		fallenX -= t;
	else
		fallenX += t;
}

bool Brick::backToGrass()
{
	if( fallenX != 0 )
	{
		int add = 1;
		if( fallenX > blocks[ lastGrass ]->x )
		{
			for( unsigned i = 0; i < blocks.size(); i++ )
			{
				blocks[ i ]->x += add;
			}
			
			for( unsigned i = 0; i < ladders.size(); i++ )
			{
				ladders[ i ]->x += add;
			}
			
			left += add;
			right += add;
			
			if( fallenX < blocks[ lastGrass ]->x )
				fallenX = 0;
		}
		else if( fallenX < blocks[ lastGrass ]->x )
		{
			
			for( unsigned i = 0; i < blocks.size(); i++ )
			{
				blocks[ i ]->x -= add;
			}
			
			for( unsigned i = 0; i < ladders.size(); i++ )
			{
				ladders[ i ]->x -= add;
			}
			
			left -= add;
			right -= add;
			
			if( fallenX > blocks[ lastGrass ]->x )
				fallenX = 0;
		}
		else
		{
			fallenX = 0;
		}
	}
	
	if( fallenX != 0 )
	{
		return true;
	}
	
	return false;
}




Brick::Brick()
{
	nr = 0;
	block = NULL;
	
	ladder_nr = 0;
	ladder = NULL;
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
	world_type = -1;
	lastGrass = -1;
	fallenX = 0;
}

Brick::~Brick()
{
	free();
}

void Brick::free()
{
	if( block != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			block[ i ].free();
		}
		
		delete [] block;
		block = NULL;
		nr = 0;
	}
	
	if( ladder != NULL )
	{
		for( int i = 0; i < ladder_nr; i++ )
		{
			ladder[ i ].free();
		}
		
		delete [] ladder;
		ladder = NULL;
		ladder_nr = 0;
	}
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	blocks.clear();
	ladders.clear();
	
	left = 0;
	right = 0;
	
	world_type = -1;
	lastGrass = -1;
	fallenX = 0;
}




void Brick::load( int screen_w, int screen_h, int nr, int type )
{
	free();
	
	world_type = type;
	// printf("type: %d\n", world_type );
	
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;

	this->nr = nr;
	block = new MySprite[ nr ];
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "brick-block[" +to_string( i ) +"]" );
		block[ i ].loadByImage( "data/sprites/play/" +to_string( type ) +"/" +to_string( i ) +".png" );
	}
	
	this->ladder_nr = 2;
	ladder = new MySprite[ ladder_nr ];
	for( int i = 0; i < ladder_nr; i++ )
	{
		ladder[ i ].setName( "brick-ladder[" +to_string( i ) +"]" );
		ladder[ i ].loadByImage( "data/sprites/play/ladder/" +to_string( i ) +".png" );
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
				block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
				window->draw( block[ blocks[ i ]->nr ].get() );
			}
		}
	}
}

void Brick::drawLadders( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		if( ladders[ i ]->x > -width && ladders[ i ]->x < screen_w )
		{
			ladder[ ladders[ i ]->nr ].setPosition( ladders[ i ]->x, ladders[ i ]->y );
			ladder[ ladders[ i ]->nr ].setColor( sf::Color( ladders[ i ]->red, ladders[ i ]->green, ladders[ i ]->blue ) );
			window->draw( ladder[ ladders[ i ]->nr ].get() );
		}
	}
}





int Brick::getScreenWidth()
{
	return screen_w;
}

int Brick::getScreenHeight()
{
	return screen_h;
}

void Brick::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].fadein( v, max );
	}
	
	for( int i = 0; i < ladder_nr; i++ )
	{
		ladder[ i ].fadein( v, max );
	}
}

void Brick::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].fadeout( v, min );
	}
	
	for( int i = 0; i < ladder_nr; i++ )
	{
		ladder[ i ].fadeout( v, min );
	}
}